// The main file for testing the C vector in task 2 simply.
// Copyright (c) 2016 sysu_AT. All righs reserved.

// This file could not ensure that your implementation of C vector is bug-free.
// You should complie this project in command-line as below:
//    "gcc -std=c99 -Wall -Werror -g main.c c_vector.c -o task_2"
// Pay Attention: You should not modify this file.

#include <stdio.h>
#include <assert.h>

#define C_VECTOR_VALUE_TYPE double
#include "c_vector.h"

// Output all elements in vector in pretty format.
void vec_double_print(Vector_double* vec, const char* name) {
    printf("  %s: {", name);
	for (size_t i = 0; i < vec_double_size(vec); i++) {
        if (i != 0) printf(", ");
		printf("%lf", vec_double_get(vec, i));
	}
	printf("}\n");
}

int main() {
    Vector_double *vec_double_1 = NULL, *vec_double_2 = NULL;

    create_vector_double(&vec_double_1);
    printf("create vector 1 Done.\n");
    vec_double_2 = create_vector_double(NULL);
    printf("create_vector_double 2 Done.\n");

    printf("vec_double_1 size is %lu\n", vec_double_size(vec_double_1));
    printf("vec_double_2 size is %lu\n", vec_double_size(vec_double_2));

    printf("vec_double_1 capacity is %lu\n", vec_double_capacity(vec_double_1));
    printf("vec_double_2 capacity is %lu\n", vec_double_capacity(vec_double_2));

    // compound literal
    vec_double_assign(vec_double_1, 10, (C_VECTOR_VALUE_TYPE[]){1, 2, 3, 4, 5, 
                                                  6, 7, 8, 9, 10});
    // get pointer of data
    vec_double_assign(vec_double_2, 5, vec_double_data(vec_double_1));
    vec_double_assign(vec_double_2, 5, vec_double_data(vec_double_1) + 2);

    printf("vec_double_assign Done.\n");
    vec_double_print(vec_double_1, "vec_double_1"); // {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
    vec_double_print(vec_double_2, "vec_double_2"); // {3, 4, 5, 6, 7}

    assert(*vec_double_data(vec_double_2) == vec_double_get(vec_double_2, 0));
    printf("vec_double_data Done.\n");

    vec_double_set(vec_double_1, 0, 99);
    assert(vec_double_get(vec_double_1, 0) == 99);
    assert(vec_double_get(vec_double_2, 0) == 3);
    printf("vec_double_set Done.\n");    
    printf("vec_double_get Done.\n");

    assert(vec_double_front(vec_double_1) == 99);
    printf("vec_double_front Done.\n");
    
    assert(vec_double_back(vec_double_2) == 7);
    printf("vec_double_back Done.\n");

    vec_double_push_back(vec_double_2, -1);
    vec_double_push_back(vec_double_2, 0);
    assert(vec_double_size(vec_double_2) == 7);
    printf("vec_double_push_back Done.\n");

    vec_double_pop_back(vec_double_1);
    assert(vec_double_size(vec_double_1) == 9);
    printf("vec_double_pop_back Done.\n");

    vec_double_print(vec_double_1, "vec_double_1"); // {99, 2, 3, 4, 5, 6, 7, 8, 9}
    vec_double_print(vec_double_2, "vec_double_2"); // {3, 4, 5, 6, 7, -1, 0}
    
    vec_double_erase(vec_double_1, 2, 5);
    assert(vec_double_size(vec_double_1) == 4);
    vec_double_erase(vec_double_2, 0, 4);
    assert(vec_double_size(vec_double_2) == 3);

    vec_double_insert(vec_double_1, 0, 2, (C_VECTOR_VALUE_TYPE[]){-99, -100});
    vec_double_insert(vec_double_2, 3, 1, (C_VECTOR_VALUE_TYPE[]){1});
    vec_double_insert(vec_double_2, 1, 2, (C_VECTOR_VALUE_TYPE[]){22, 40});

    vec_double_print(vec_double_1, "vec_double_1"); // {-99, -100, 99, 2, 8, 9}
    vec_double_print(vec_double_2, "vec_double_2"); // {7, 22, 40, -1, 0, 1}
    printf("vec_double_insert Done.\n");

    vec_double_clear(vec_double_1);
    vec_double_print(vec_double_1, "vec_double_1"); // {}
    printf("vec_double_clear Done.\n");

    destroy_vector_double(&vec_double_1);
    copy_vector_double(vec_double_2, &vec_double_1);
    vec_double_print(vec_double_1, "vec_double_1"); // {7, 22, 40, -1, 0, 1}
    printf("Destroy vector Done.\n");
    printf("Copy vector Done.\n");

    vec_double_resize(vec_double_1, 10, 0);
    vec_double_print(vec_double_1, "vec_double_1"); // {7, 22, 40, -1, 0, 1, 0, 0, 0, 0}

    for (size_t i = 0; i < vec_double_size(vec_double_1); i++)
        vec_double_set(vec_double_1, i, i);

    vec_double_print(vec_double_1, "vec_double_1"); // {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}

    for (size_t i = 10; i < 100; i++)
        vec_double_push_back(vec_double_1, i);

    assert(vec_double_size(vec_double_1) == 100);

    C_VECTOR_VALUE_TYPE *p = vec_double_data(vec_double_1);
    for (size_t i = 0; i < vec_double_size(vec_double_1); i++)
        assert(p[i] == i);

    printf("vec_double_1 capacity is %lu\n", vec_double_capacity(vec_double_1));
    printf("vec_double_2 capacity is %lu\n", vec_double_capacity(vec_double_2));

    destroy_vector_double(&vec_double_1);
    destroy_vector_double(&vec_double_2);

    printf("\n[All Done].\n\n");

    return 0;
}
