#ifndef TODOLIST_TODOLISTSTORAGE_H__
#define TODOLIST_TODOLISTSTORAGE_H__

error_t todolist_add_item(todolist_t* tdl, const char* content);
error_t todolist_finish_item(todolist_t* tdl, int item_id);
error_t todolist_find_item(todolist_t* tdl, const item_t** item,
                           int(*filter)(const item_t*, ...), ...);



#endif // TODOLIST_TODOLISTSTORAGE_H__