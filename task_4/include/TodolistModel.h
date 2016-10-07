#ifndef TODOLIST_TODOLISTMODEL_H__
#define TODOLIST_TODOLISTMODEL_H__

#include <stdarg.h> // for va_list
#include <time.h> // for time
#include "TodolistErrorCode.h"


typedef enum {
    UNKNOWN_ITEM_STATE, FINISHED, UNFINISHED
} item_state_t;

typedef struct {
    int id;
    char* content;
    item_state_t state;
    time_t timestamp;
} item_t;

struct item_node {
    struct item_node* next;
    item_t* data;
};

typedef struct item_node item_node_t;

typedef struct {
    int id_count;
    item_node_t* item_list;
    const char* file_address;
} todolist_t;


/* both of them should be call in the same scope */
void create_item(item_t** item, const char* content, int item_id,
                 item_state_t state, time_t timestamp);
void destroy_item(item_t** item);
void create_item_list(item_node_t** item_list);
void destroy_item_list(item_node_t** item_list);
void item_list_add(item_node_t** item_list, item_t* item);
void create_todolist(todolist_t** tdl);
void destroy_todolist(todolist_t** tdl);


error_t todolist_add_item(todolist_t* tdl, const char* content, int item_id,
                          item_state_t state, time_t timestamp);
error_t todolist_finish_item(todolist_t* tdl, int item_id, time_t timestamp);
error_t todolist_find_item(todolist_t* tdl, const item_t** item,
                           int(*filter)(const item_t*, va_list), ...);
error_t todolist_query_item(todolist_t* tdl,
                            item_node_t** item_list,
                            int item_max,
                            int(*filter)(const item_t*, va_list),
                            ...);

#endif // TODOLIST_TODOLISTMODEL_H__