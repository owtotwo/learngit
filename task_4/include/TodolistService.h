/*
 * 此部分为前后端首层
 * 接收所有的输入情况，需要进行情况判断
 * 调用下层的Storage中的增删查改函数
 * 仅处理逻辑部分
 * 换UI后可能要增加一层连接前后端的中间层
 */

#ifndef TODOLIST_TODOLISTSERVICE_H__
#define TODOLIST_TODOLISTSERVICE_H__

#include "TodolistModel.h"
#include "TodolistErrorCode.h"

// Return 0 if Success
error_t service_add_item(todolist_t* tdl, const char* content);
error_t service_finish_item(todolist_t* tdl, int item_id);
error_t service_get_list(todolist_t* tdl, int line_max, int done_needed,
                         const item_t** item_list);
error_t service_find_item_by_id(todolist_t* tdl, int item_id,
                                const item_t** item);
error_t service_find_item_by_keyword(todolist_t* tdl, const char* item_keyword,
                                 const item_t** item);

#endif // TODOLIST_TODOLISTSERVICE_H__