#include <stdarg.h> // for va_list, va_arg, va_start, va_end
#include <string.h> // for strlen strstr
#include <stdio.h> // for printf
#include <time.h> // for time
#include "TodolistService.h"
#include "TodolistModel.h"
#include "TodolistErrorCode.h"

static int filter_by_id(const item_t* item, ...);
static int filter_by_keyword(const item_t* item, ...);
static int filter_nothing(const item_t* item, ...);

error_t service_add_item(todolist_t* tdl, const char* content) {
    if (!tdl) return FATAL_ERROR;
    
    /* check some invalid word */
    if (strlen(content) > 1024)
        return FAILURE; // content should be less than 1024 bytes;

    /*  ......  */

    // ensure the content is valid

    return todolist_add_item(tdl, content, ++(tdl->id_count),
                             UNFINISHED, time(NULL));
}

error_t service_finish_item(todolist_t* tdl, int item_id) {
    if (!tdl) return FATAL_ERROR;

    /* id should be greater than zero */
    if (item_id <= 0) return FAILURE;

    // item_t* item = NULL;

    return todolist_finish_item(tdl, item_id, time(NULL));
}

// line_size is return 
error_t service_get_list(todolist_t* tdl, int line_max, const item_t*** item_list,
                     size_t* return_size) {
    if (!tdl || !item_list) return FATAL_ERROR;

    /* line_max should be not less than zero */
    if (line_max < 0) return FAILURE;
    
    for (int i = 0; i < line_max; i++) {
        const item_t* item = NULL;
        error_t result = todolist_find_item(tdl, &item, filter_nothing);
        if (result) {
            (*item_list)[i] = item;
        } else {
            (*item_list)[i] = NULL;
            (*return_size) = i;
            return result;
        }
    }

    (*item_list)[line_max] = NULL;

    return SUCCESS;
}

error_t service_find_item_by_id(todolist_t* tdl, int item_id, const item_t** item) {
    return todolist_find_item(tdl, item, filter_by_id, item_id);
}

error_t service_find_item_by_keyword(todolist_t* tdl, const char* item_keyword,
                                 const item_t** item) {
    return todolist_find_item(tdl, item, filter_by_keyword, item_keyword);
}

// consume arg1=id
static int filter_by_id(const item_t* item, ...) {
    va_list ap;
    va_start(ap, item);

    int item_id = va_arg(ap, int);
    int result = (item_id == item->id ? 1 : 0);

    va_end(ap);
    return result;
}

static int filter_by_keyword(const item_t* item, ...) {
    va_list ap;
    va_start(ap, item);

    const char* item_keyword = va_arg(ap, const char*);
    int result = (strstr(item->content, item_keyword) != NULL ? 1 : 0);

    va_end(ap);
    return result;
}

static int filter_nothing(const item_t* item, ...) {
    return 1;
}
