#ifndef TODOLIST_TODOLISTCONSOLECONSTVAL_H__
#define TODOLIST_TODOLISTCONSOLECONSTVAL_H__

static const int DEFAULT_PRINT_LINE_SIZE = 10;

static const char* PRINT_LINE_SIZE_FLAG = "--list";
static const char* PRINT_LINE_SIZE_FLAG_ABBR = "-l";
static const char* ADD_ITEM_FLAG = "--short";
static const char* ADD_ITEM_FLAG_ABBR = "-s";
static const char* FIND_ITEM_BY_ID_FLAG = "--id";
static const char* FIND_ITEM_BY_ID_FLAG_ABBR = "-i";
static const char* FIND_ITEM_BY_KEYWORD_FLAG = "--keyword";
static const char* FIND_ITEM_BY_KEYWORD_FLAG_ABBR = "-k";

typedef enum {
    UNKNOWN_CMD, NONE, LIST, ADD, FINISH, FIND, UPDATE, COMMIT, ROLLBACK
} cmd_t;

#endif // !TODOLIST_TODOLISTCONSOLECONSTVAL_H__