#include <stdarg.h> // for va_list, va_arg, va_start, va_end
#include <string.h> // for strlen strstr
#include <stdio.h> // for printf
#include <time.h> // for time
#include "TodolistService.h"
#include "TodolistModel.h"
#include "TodolistErrorCode.h"

static int filter_by_id(const item_t* item, va_list ap);
static int filter_by_keyword(const item_t* item, va_list ap);
static int filter_by_nothing(const item_t* item, va_list ap);
static int filter_by_state(const item_t* item, va_list ap);

error_t service_add_item(todolist_t* tdl, const char* content) {
    if (!tdl) return FATAL_ERROR;
    
    /* check some invalid word */
    if (strlen(content) > 1024)
        return FAILURE; // content should be less than 1024 bytes;

    return todolist_add_item(tdl, content, ++(tdl->id_count),
                             UNFINISHED, time(NULL));
}

error_t service_finish_item(todolist_t* tdl, int item_id) {
    if (!tdl) return FATAL_ERROR;

    /* id should be greater than zero */
    if (item_id <= 0) return FAILURE;

    return todolist_finish_item(tdl, item_id, time(NULL));
}


error_t service_find_item_by_id(todolist_t* tdl, int item_id, const item_t** item) {
    return todolist_find_item(tdl, item, filter_by_id, item_id);
}

error_t service_find_item_by_keyword(todolist_t* tdl, const char* item_keyword,
                                 const item_t** item) {
    return todolist_find_item(tdl, item, filter_by_keyword, item_keyword);
}

error_t service_get_n_items_by_state(todolist_t* tdl, item_node_t** item_list,
                                     int line_max, int done_needed) {
    int items_count = line_max;
    error_t result = FAILURE;

    if (done_needed)
        result = todolist_query_item(tdl, item_list, items_count, 
                                     filter_by_state, UNFINISHED);
    else
        result = todolist_query_item(tdl, item_list, items_count,
                                     filter_by_nothing);

    return result;
}

// consume arg1=id
static int filter_by_id(const item_t* item, va_list ap) {

    int item_id = va_arg(ap, int);
    int result = (item_id == item->id ? 1 : 0);

    return result;
}

static int filter_by_keyword(const item_t* item, va_list ap) {

    const char* item_keyword = va_arg(ap, const char*);
    int result = (strstr(item->content, item_keyword) != NULL ? 1 : 0);

    return result;
}

static int filter_by_nothing(const item_t* item, va_list ap) { return 1; }

static int filter_by_state(const item_t* item, va_list ap) {
    item_state_t state = va_arg(ap, item_state_t);
    int result = (state == item->state ? 1 : 0);

    return result;
}
