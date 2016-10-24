#include <stdio.h>
#include <stdlib.h>

int iLoveYukiNagato(int *num, const int size, const int K);

static const int SCALE = 12345;

int main() {
    int* num = (int*)malloc(SCALE * sizeof(int));

    for (int i = 0; i < SCALE; i++) {
        num[i] = rand();
        printf("%d ", num[i]);
    }

    int result = iLoveYukiNagato(num, SCALE, SCALE / 2);

    printf("The result is %d.\n", result);

    return 0;
}