#ifndef TODOLIST_TODOLISTMODEL_H__
#define TODOLIST_TODOLISTMODEL_H__

#include <time.h> // for time
#include "TodolistErrorCode.h"

typedef enum {
    UNKNOWN_ITEM_STATE, FINISHED, UNFINISHED
} item_state_t;

typedef struct {
    int id;
    char* content;
    item_state_t state;
    time_t date;
} item_t;

typedef struct {
    item_node_t* next;
    item_t* data;
} item_node_t;

typedef struct {
    int id_count;
    item_node_t* item_list;
} todolist_t;


/* both of them should be call in the same scope */
void create_todolist(todolist_t** tdl);
void destroy_todolist(todolist_t** tdl);


error_t todolist_add_item(todolist_t* tdl, const char* content);
error_t todolist_finish_item(todolist_t* tdl, int item_id);
error_t todolist_find_item(todolist_t* tdl, const item_t** item,
                           int(*filter)(const item_t*, ...), ...);

#endif // TODOLIST_TODOLISTMODEL_H__