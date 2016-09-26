#ifndef TODOLIST_TODOLISTSTORAGE_H__
#define TODOLIST_TODOLISTSTORAGE_H__

#include "TodolistErrorCode.h" // for error_t
#include "TodolistModel.h" // for todolist_t

error_t todolist_save(todolist_t* tdl);
error_t todolist_load(todolist_t* tdl);

#endif // TODOLIST_TODOLISTSTORAGE_H__