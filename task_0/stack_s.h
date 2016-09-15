// The Template Stack implementation in C Macro.

#ifndef STACK_S_MACRO_H_
#define STACK_S_MACRO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h> // for malloc

typedef struct {
    void *top;
    void *bottom;
} Stack_s;

#define initStack(P, TYPE, SIZE) \
    do {\
        (P).top = (P).bottom = malloc(((SIZE) + 1) * sizeof(TYPE));\
    } while (0)

#define destroyStack(P) \
    do {\
        free((P).bottom);\
    } while (0)

#define sizeStack(P, TYPE) \
    ((size_t)(((TYPE*)(P).top) - ((TYPE*)(P).bottom)))

#define emptyStack(P) \
    ((P).top == (P).bottom)

#define pushStack(P, TYPE, VALUE) \
    do {\
        TYPE* tmp = (TYPE*)((P).top);\
        *tmp = (VALUE);\
        (P).top = (void*)(tmp + 1);\
    } while (0)

#define popStack(P, TYPE) \
    do {\
        TYPE* tmp = (TYPE*)((P).top);\
        (P).top = (void*)(tmp - 1);\
    } while (0)

#define peekStack(P, TYPE) \
    (*(((TYPE*)((P).top)) - 1))

#ifdef __cplusplus
}
#endif

#endif // STACK_S_MACRO_H_