#include <stdlib.h> // for malloc, free
#include <string.h> // for strlen
#include <stdarg.h> // for va_start, va_end, va_arg, va_list
#include <time.h> // for time
#include "TodolistModel.h"
#include "TodolistErrorCode.h"
#include "TodolistStorage.h"


void create_item(item_t** item, const char* content, int item_id,
                 item_state_t state, time_t timestamp) {
    if (!item) return; // neew Not NULL
    if (*item) return; // need NULL 

    item_t* p = (item_t*)malloc(1 * sizeof(item_t));
    p->id = item_id;
    p->content = (char*)malloc(strlen(content) * sizeof(char) + 1);
    p->state = UNFINISHED;
    p->timestamp = timestamp;
    if (p->content)
        strcpy(p->content, content);

    (*item) = p;
}

void destroy_item(item_t** item) {
    if (!item) return;

    free((*item)->content);
    free(*item);

    *item = NULL;
}

void create_item_list(item_node_t** item_list) {
    *item_list = NULL;
}

void destroy_item_list(item_node_t** item_list) {
    if (!item_list) return;

    item_node_t* p = (*item_list);
    while (p) {
        destroy_item(&(p->data));
        item_node_t* tmp = p;
        p = p->next;
        free(tmp);
    }

    (*item_list) = NULL;
}

void create_todolist(todolist_t** tdl) {
    if (!tdl) return;
    if (*tdl) return;

    todolist_t* p = (todolist_t*)malloc(1 * sizeof(todolist_t));
    p->id_count = 0;
    create_item_list(&(p->item_list));
    p->file_address = DEFAULT_ADDRESS;

    todolist_load(p);

    *tdl = p;
}

void destroy_todolist(todolist_t** tdl) {
    if (!tdl) return;

    todolist_save(*tdl);

    destroy_item_list(&((*tdl)->item_list));
    free(*tdl);

    *tdl = NULL;
}

error_t todolist_add_item(todolist_t* tdl, const char* content, int item_id,
                          item_state_t state, time_t timestamp) {
    item_t* p = NULL;
    create_item(&p, content, item_id, state, timestamp);

    if (!p) return FAILURE;

    item_node_t* new_node = (item_node_t*)malloc(1 * sizeof(item_node_t));
    new_node->next = tdl->item_list;
    new_node->data = p;
    tdl->item_list = new_node;

    return SUCCESS;
}

error_t todolist_finish_item(todolist_t* tdl, int item_id, time_t timestamp) {
    item_node_t* p = tdl->item_list;
    while (p) {
        if (p->data->id == item_id) {
            p->data->state = FINISHED;
            return SUCCESS;
        }
        p = p->next;
    }
    return FAILURE;
}

error_t todolist_find_item(todolist_t* tdl, const item_t** item,
                           int(*filter)(const item_t*, ...), ...) {
    va_list ap;
    va_start(ap, filter);
    int item_id = va_arg(ap, int); // get first argument item_id
    va_end(ap);

    item_node_t* p = tdl->item_list;
    while (p) {
        if (filter(p->data, item_id)) {
            *item = p->data;
            return SUCCESS;
        }
        p = p->next;
    }
    return FAILURE;
}
