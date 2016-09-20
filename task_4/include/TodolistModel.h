#include <time.c> // for time

todolist_t

typedef enum item_state {
    UNKNOWN, FINISHED, UNFINISHED
} item_state_t;

typdef struct {
    int id;
    char* content;
    item_state_t state;
    struct tm date;
} item_t;