#ifndef TODOLIST_TODOLISTCONSOLE_H__
#define TODOLIST_TODOLISTCONSOLE_H__

const int DEFAULT_PRINT_LINE_SIZE = 10;

const char* PRINT_LINE_SIZE_FLAG = "--list";
const char* PRINT_LINE_SIZE_FLAG_ABBR = "-l";
const char* ADD_ITEM_FLAG = "--short";
const char* ADD_ITEM_FLAG_ABBR = "-s";
const char* FIND_ITEM_BY_ID_FLAG = "--id";
const char* FIND_ITEM_BY_ID_FLAG_ABBR = "-i";
const char* FIND_ITEM_BY_KEYWORD_FLAG = "--keyword";
const char* FIND_ITEM_BY_KEYWORD_FLAG_ABBR = "-k";

typedef enum {
    UNKNOWN_CMD, NONE, LIST, ADD, FINISH, FIND, UPDATE, COMMIT, ROLLBACK
} cmd_t;

int todolist_console(int argc, char* argv[]);


#endif // !TODOLIST_TODOLISTCONSOLE_H__
