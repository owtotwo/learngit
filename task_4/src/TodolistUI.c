#include <assert.h> // for assert
#include <string.h> // for strcmp, strlen
#include <stdlib.h> // for strtol
#include "TodolistUI.h"

typedef enum {
    UNKNOWN, NONE, LIST, ADD, FINISH, FIND, UPDATE, COMMIT, ROLLBACK
} cmd_t;

const int DEFAULT_PRINT_LINE_SIZE = 10;
const char* PRINT_LINE_SIZE_FLAG = "--list";
const char* PRINT_LINE_SIZE_FLAG_ABBR = "-l";
const char* ADD_ITEM_FLAG = "--short";
const char* ADD_ITEM_FLAG_ABBR = "-s";
const char* FIND_ITEM_BY_ID_FLAG = "--id";
const char* FIND_ITEM_BY_ID_FLAG_ABBR = "-i"
const char* FIND_ITEM_BY_KEYWORD_FLAG = "--keyword";
const char* FIND_ITEM_BY_KEYWORD_FLAG_ABBR = "-k"


void abort(const char* err);


static cmd_t get_command(const char* cmd);
static void print_error(const char* err);
static void print_usage(todolist_t* tdl, int argc, char* argv[]);
static void console_print_list_by_default(todolist_t* tdl);
static void console_print_list(todolist_t* tdl, int argc, char* argv[]);
static void console_add_item(todolist_t* tdl, int argc, char* argv[]);
static void console_finish_item(todolist_t* tdl, int argc, char* argv[]);
static void console_find_item(todolist_t* tdl, int argc, char* argv[]);

static void get_buffer_from_console(const char* buffer);
static void output_list(todolist_t* tdl, int line_max);
static void output_item(item_t* itm);

// Done
int todolist_ui(int argc, char* argv[]) {
    todolist_t* tdl = NULL;

    create_todolist(&tdl);
    int result = run_todolist(tdl, argc, argv);
    destroy_todolist(&tdl);

    return result;
}

// Done
int run_todolist(todolist_t* tdl, int argc, char* argv[]) { 
    assert(argc > 0);

    cmd_t cmd = UNKNOWN;

    if (argc == 1) {
        cmd = NONE;
    } else {
        cmd = get_command(argv[1]);
    }
    
    switch (cmd) {
        case UNKNOWN: 
            print_usage(argc, argv); 
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
        return UNKNOWN;
}


static void print_usage(int argc, char* argv[]) {
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

                int* end_ptr = NULL;
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

    const char* content = NULL;

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
        get_buffer_from_console(&content); // it will call malloc
        result = service_add_item(tdl, content);
        free(content); // so make sure to free it
        content = NULL;
    } else {
        result = service_add_item(tdl, content);
    }

    if (result == 0) {
        print_info("Adding...Done!");
    } else {
        print_error("Adding...Failed!");
    }
}


static void console_finish_item(todolist_t* tdl, int argc, char* argv[]) {
    // 可以考虑增加扩展功能 通过关键词定位唯一的item直接finish.
    assert(argc > 1);

    int* end_ptr = NULL;
    int item_id = strtol(argv[3], &end_ptr, 10);
    
    if (strlen(argv[3]) != (end_ptr - argv[3])) {
        print_error("Expect a valid number of ID.");
    }

    if (service_finish_item(tdl, item_id) == 0) {
        print_info("ID %d Item...Finished!");
    } else {
        print_error("Finish...Failed!");
    }
}


static void console_find_item(todolist_t* tdl, int argc, char* argv[]) {
    assert(argc > 1);

    const item_t* itm;
    int item_id = -1;
    int is_find_by_id = 0;
    const char* item_keyword = NULL;
    int is_find_by_keyword = 0;

    for (int i = 2; i < argc; i++) {
        if ((strcmp(argv[i], FIND_ITEM_BY_ID_FLAG_ABBR) == 0 ||
            strcmp(argv[i], FIND_ITEM_BY_ID_FLAG) == 0) &&
            !is_find_by_keyword) {
                int* end_ptr = NULL;
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

    if (is_find_by_id)
        result = service_find_item_by_id(tdl, item_id, &itm);
    else if (is_find_by_keyword)
        result = service_find_item_by_keyword(tdl, item_keyword, &itm);
    else
        assert(0);

    if (result == 0)
        output_item(itm);
    else
        print_error("Service Find Failed")
}


static void output_list(todolist_t* tdl, int line_max) {
    const item_t* itm_list[];
    int line_size = 0;

    service_get_list(tdl, line_max, &itm_list, &line_size);

    for (int i = 0; i < line_size; i++) {
        output_item(itm_list[i]);
    }
}

static void output_item(item_t* itm) {
    const char* state;
    if (itm->state == FINISHED)
        state = "Finished";
    else if (itm->state == UNFINISHED)
        state = "Unfinished";
    printf("[%s][%d]: %s\n---\n", state, itm->id, itm->content);
}