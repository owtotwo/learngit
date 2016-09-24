#include <assert.h> // for assert
#include <stdio.h> // for printf, getchar
#include <string.h> // for strcmp, strlen, strerror
#include <stdlib.h> // for strtol, malloc, free
#include <errno.h> // for errno
#include "TodolistConsole.h"
#include "TodolistService.h"
#include "TodolistModel.h"
#include "TodolistErrorCode.h"

/* it will free the memory */
extern void safe_abort(const char* file, int line, const char* err);

static cmd_t get_command(const char* cmd);

static void print_error(const char* err);
static void print_info(const char* info);
static void print_usage(todolist_t* tdl, int argc, char* argv[]);

static int console_run_todolist(todolist_t* tdl, int argc, char* argv[]);
static void console_print_list_by_default(todolist_t* tdl);
static void console_print_list(todolist_t* tdl, int argc, char* argv[]);
static void console_add_item(todolist_t* tdl, int argc, char* argv[]);
static void console_finish_item(todolist_t* tdl, int argc, char* argv[]);
static void console_find_item(todolist_t* tdl, int argc, char* argv[]);

static void get_buffer_from_console(char** buffer, size_t* len);
static void output_list(todolist_t* tdl, int line_max);
static void output_item(const item_t* item);


// Done
int todolist_console(int argc, char* argv[]) {
    todolist_t* tdl = NULL;

    create_todolist(&tdl);
    int result = console_run_todolist(tdl, argc, argv);
    destroy_todolist(&tdl);

    return result;
}

// Done
static int console_run_todolist(todolist_t* tdl, int argc, char* argv[]) { 
    assert(argc > 0);

    cmd_t cmd = UNKNOWN_CMD;

    if (argc == 1) {
        cmd = NONE;
    } else {
        cmd = get_command(argv[1]);
    }
    
    switch (cmd) {
        case UNKNOWN_CMD: 
            print_usage(tdl, argc, argv); 
            break;
        case NONE: 
            console_print_list_by_default(tdl);
            break;
        case LIST: 
            console_print_list(tdl, argc, argv);
            break;
        case ADD: 
            console_add_item(tdl, argc, argv);
            break;
        case FINISH: 
            console_finish_item(tdl, argc, argv);
            break;
        case FIND: 
            console_find_item(tdl, argc, argv);
            break;
        default: 
            assert(0);
    }

    return -1; // should not be here
}


static cmd_t get_command(const char* cmd) {
    /* None, list, add, finish, find [, update, commit, rollback ] */
    if (strcmp(cmd, "list") == 0)
        return LIST;
    else if (strcmp(cmd, "add") == 0)
        return ADD;
    else if (strcmp(cmd, "finish") == 0)
        return FINISH;
    else if (strcmp(cmd, "find") == 0)
        return FIND;
    else
        return UNKNOWN_CMD;
}


static void print_usage(todolist_t* tdl, int argc, char* argv[]) {
    printf("Usage: todolist <command> [flag].\n");
}


static void console_print_list(todolist_t* tdl, int argc, char* argv[]) {
    assert(argc > 1);

    // config value
    int line_max = DEFAULT_PRINT_LINE_SIZE;

    for (int i = 2; i < argc; i++) {
        // line size
        if (strcmp(argv[i], PRINT_LINE_SIZE_FLAG_ABBR) == 0 ||
            strcmp(argv[i], PRINT_LINE_SIZE_FLAG) == 0) {

                if (i + 1 == argc) {
                    print_error("Expect a number of line.");
                    return;
                }

                char* end_ptr = NULL;
                int line_tmp = strtol(argv[i + 1], &end_ptr, 10);

                if (strlen(argv[i + 1]) == (end_ptr - argv[i + 1])) {
                    line_max = (line_max > line_tmp ? line_max : line_tmp);
                } else {
                    print_error("Expect a number of line.");
                    return;
                }
                i++;

        // unknown flags
        } else {
            print_error("unknown flags.");
            return;
        }
    }

    output_list(tdl, line_max);
}


static void console_print_list_by_default(todolist_t* tdl) {
    output_list(tdl, DEFAULT_PRINT_LINE_SIZE);
}


static void console_add_item(todolist_t* tdl, int argc, char* argv[]) {
    assert(argc > 1);

    char* content = NULL;

    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], ADD_ITEM_FLAG_ABBR) == 0 ||
            strcmp(argv[i], ADD_ITEM_FLAG) == 0) {

                if (i + 1 == argc) {
                    print_error("Expect a short sentence \"<str>\".");
                    return;
                }

                content = argv[i + 1];
                i++;

        // unknown flags
        } else {
            print_error("unknown flags.");
            return;
        }
    }

    int result = -1; // failed by default

    if (content == NULL) {
        size_t buffer_size = 512; // default
        content = (char*)malloc(buffer_size * sizeof(char));
        get_buffer_from_console(&content, &buffer_size); // it will call realloc
        result = service_add_item(tdl, content);
        free(content);
        content = NULL;
    } else {
        result = service_add_item(tdl, content);
    }

#if 0
    if (result == FATAL_ERROR)
        safe_abort(__FILE__, __LINE__, "Service Adding Error");
#endif // TODO

    if (result == SUCCESS) {
        print_info("Adding...Done!");
    } else {
        print_error("Adding...Failed!");
    }
}


static void console_finish_item(todolist_t* tdl, int argc, char* argv[]) {
    // 可以考虑增加扩展功能 通过关键词定位唯一的item直接finish.
    assert(argc > 1);

    char* end_ptr = NULL;
    int item_id = strtol(argv[3], &end_ptr, 10);
    
    if (strlen(argv[3]) != (end_ptr - argv[3])) {
        print_error("Expect a valid number of ID.");
    }

    if (service_finish_item(tdl, item_id) == SUCCESS) {
        print_info("ID %d Item...Finished!");
    } else {
        print_error("Finish...Failed!");
    }
}


static void console_find_item(todolist_t* tdl, int argc, char* argv[]) {
    assert(argc > 1);

    const item_t* item;
    int item_id = -1;
    int is_find_by_id = 0;
    const char* item_keyword = NULL;
    int is_find_by_keyword = 0;

    for (int i = 2; i < argc; i++) {
        if ((strcmp(argv[i], FIND_ITEM_BY_ID_FLAG_ABBR) == 0 ||
            strcmp(argv[i], FIND_ITEM_BY_ID_FLAG) == 0) &&
            !is_find_by_keyword) {
                char* end_ptr = NULL;
                item_id = strtol(argv[i + 1], &end_ptr, 10);
                
                if (strlen(argv[i + 1]) != (end_ptr - argv[i + 1])) {
                    print_error("Expect a valid number of ID.");
                    return;
                }
                is_find_by_id = 1;
                i++;

        // find by keyword
        } else if ((strcmp(argv[i], FIND_ITEM_BY_KEYWORD_FLAG_ABBR) == 0 ||
                   strcmp(argv[i], FIND_ITEM_BY_KEYWORD_FLAG) == 0) &&
                   !is_find_by_id) {
            item_keyword = argv[i + 1];
            is_find_by_keyword = 1;
            i++;

        // unknown flags
        } else {
            print_error("unknown flags.");
            return;
        }
    }

    int result = -1;

    if (is_find_by_id)
        result = service_find_item_by_id(tdl, item_id, &item);
    else if (is_find_by_keyword)
        result = service_find_item_by_keyword(tdl, item_keyword, &item);
    else
        assert(0);

    if (result == SUCCESS)
        output_item(item);
    else
        print_error("Service Find Failed");
}


static void output_list(todolist_t* tdl, int line_max) {
    const item_t** item_list = 
        (const item_t**)malloc((line_max + 1) * sizeof(const item_t*));
    size_t line_size = 0;

    service_get_list(tdl, line_max, &item_list, &line_size);

    for (size_t i = 0; i < line_size; i++) {
        if (i != 0) puts("---");
        output_item(item_list[i]);
    }

    free(item_list);
}

static void output_item(const item_t* item) {
    const char* state_str = NULL;
    if (item->state == FINISHED)
        state_str = "Done";
    else if (item->state == UNFINISHED)
        state_str = "TODO";
    else
        state_str = "Unknown";
    fprintf(stdout, "[%s][%d] %s\n", state_str, item->id, item->content);
}

static void get_buffer_from_console(char** buffer, size_t* len) {
    // When its size is not enough, it should realloc a double size memory
    // to store the string.
    assert(*len > 0);
    size_t k = 0;
    int c = EOF;
    while ((c = getchar()) != EOF) {
        (*buffer)[k++] = c;
        if (k - 1 == *len) {
            (*len) *= 2;
            (*buffer) = (char*)realloc(*buffer, (*len) * sizeof(char));
        }
    }
    (*buffer)[k] = '\0';
}

static void print_error(const char* err) {
    fprintf(stderr, "[Error] %s\n", err);
}
static void print_info(const char* info) {
    fprintf(stdout, "[Info] %s\n", info);
}

static void safe_abort(const char* file, int line, const char* err) {
    fprintf(stderr, "[Fatal]%s:%d: %s (%d:%s)\n",
            file, line, err, errno, strerror(errno));
}