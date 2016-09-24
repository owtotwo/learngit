/*
 * 错误码 用于返回值 来确定某些错误信息 皆为常量
 */
#ifndef TODOLIST_TODOLISTERRORCODE_H__
#define TODOLIST_TODOLISTERRORCODE_H__

typedef enum {
    FAILURE = -1, SUCCESS = 0, FATAL_ERROR = 1
} error_t;

#endif // TODOLIST_TODOLISTERRORCODE_H__