#include <stdio.h>
#include "stack_s.h"

int main() {
    Stack_s p;

    initStack(p, int, 100);

    pushStack(p, int, 99);
    pushStack(p, int, 100);

    printf("Peek: %d\n", peekStack(p, int));
    popStack(p, int);

    printf("Size: %lu\n", sizeStack(p, int));

    while (!emptyStack(p))
        popStack(p, int);

    printf("Clear!\n");

    return 0;
}