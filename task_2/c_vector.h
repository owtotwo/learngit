// The header of a dynamic array -- C vector in task 2.
// Copyright (c) 2016 sysu_AT. All righs reserved.

/*
 * Vectors are sequence containers representing arrays that can
 *    change in size. Their size can change dynamically, with their
 *    storage being handled automatically by the container.
 * For details: http://www.cplusplus.com/reference/vector/vector/
 */

// Macros for concatenating tokens
#define AUX__CAT_TOKEN_IN_MACRO(A, B) A##B
#define CAT_TOKEN_IN_MACRO(A, B) AUX__CAT_TOKEN_IN_MACRO(A, B)

#if !defined(CAT_TOKEN_IN_MACRO(TASK_C_VECTOR_H_FOR_TYPE__, C_VECTOR_VALUE_TYPE))
#define (CAT_TOKEN_IN_MACRO(TASK_C_VECTOR_H_FOR_TYPE__, C_VECTOR_VALUE_TYPE))

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdlib.h> // for malloc, free, NULL
#include <stdint.h> // for uintptr_t
#include <string.h> // for memset, memmove, memcpy


/* Definition of some constant values */
#define C_VECTOR_GROWTH_RATE    2       // double size every reallocation

#define MAX(x, y) (((x) > (y)) ? (x) : (y))

/*-- Definition of the struction of C vector --*/
#define value_t C_VECTOR_VALUE_TYPE
#define AUX__VEC_(T) Vector_##T
#define VEC_(T) AUX__VEC_(T)

typedef struct {
    size_t count; // used size
    size_t capacity; // data[] size
    value_t* data; // the pointer of array which stores the elements
} VEC_(value_t);


/*-- Implementation detials --*/
#define AUX__VECTOR_IMPLEMENTATION(T) \
\
VEC_(value_t)* create_vector_##T(VEC_(value_t)** vec_ptr) {\
    VEC_(value_t)* ptr = (VEC_(value_t)*)malloc(sizeof(VEC_(value_t)));\
    ptr->count = 0;\
    ptr->capacity = 0;\
    ptr->data = (value_t*)malloc(0);\
    if (vec_ptr != NULL) *vec_ptr = ptr;\
    return ptr;\
}\
\
void destroy_vector_##T(VEC_(value_t)** vec_ptr) {\
    if (vec_ptr != NULL) {\
        free((void*)((*vec_ptr)->data));\
        free((void*)*vec_ptr);\
        *vec_ptr = NULL;\
    }\
}\
\
size_t vec_##T##_size(VEC_(value_t)* vec) {\
    return vec->count;\
}\
\
value_t* vec_##T##_data(VEC_(value_t)* vec) {\
    return vec->data;\
}\
\
size_t vec_##T##_capacity(VEC_(value_t)* vec) {\
    return vec->capacity;\
}\
\
void vec_##T##_reserve(VEC_(value_t)* vec, size_t n) {\
    if (vec_##T##_capacity(vec) < n) {\
        vec->data = (value_t*)realloc((void*)vec->data, n * sizeof(value_t));\
        vec->capacity = n;\
    }\
}\
\
void vec_##T##_assign(VEC_(value_t)* vec, size_t size, value_t vals[]) {\
    vec_##T##_reserve(vec, size);\
    memcpy((void*)vec->data, (const void*)vals, size * sizeof(value_t));\
    vec->count = size;\
}\
\
VEC_(value_t)* copy_vector_##T(VEC_(value_t)* vec_src, VEC_(value_t)** vec_ptr) {\
    VEC_(value_t)* ptr = create_vector_##T(NULL);\
    vec_##T##_assign(ptr, vec_##T##_size(vec_src), vec_##T##_data(vec_src));\
    if (vec_ptr != NULL) *vec_ptr = ptr;\
    return ptr;\
}\
\
void vec_##T##_erase(VEC_(value_t)* vec, size_t n, size_t size) {\
    memmove((void*)(vec->data + n),\
           (const void*)(vec->data + n + size),\
           (vec_##T##_size(vec) - n - size) * sizeof(value_t));\
    vec->count -= size;\
}\
\
void vec_##T##_resize(VEC_(value_t)* vec, size_t n, value_t val) {\
    size_t current_size = vec_##T##_size(vec);\
    if (n < current_size) {\
        vec_##T##_erase(vec, n, current_size - n);\
    } else if (n > current_size) {\
        vec_##T##_reserve(vec, n);\
        for (size_t i = current_size; i < n; i++)\
            vec->data[i] = val;\
        vec->count = n;\
    }\
}\
\
int vec_##T##_empty(VEC_(value_t)* vec) {\
    return vec_##T##_size(vec) == 0;\
}\
\
value_t vec_##T##_get(VEC_(value_t)* vec, size_t n) {\
    return vec->data[n];\
}\
\
void vec_##T##_set(VEC_(value_t)* vec, size_t n, value_t val) {\
    vec->data[n] = val;\
}\
\
void vec_##T##_insert(VEC_(value_t)* vec, size_t n, size_t size, value_t vals[]) {\
    size_t required_size = vec_##T##_size(vec) + size;\
    size_t new_size = MAX(required_size, C_VECTOR_GROWTH_RATE * vec_##T##_size(vec));\
    vec_##T##_reserve(vec, new_size);\
    memmove((void*)(vec->data + n + size),\
                    (const void*)(vec->data + n),\
                    (vec_##T##_size(vec) - n) * sizeof(value_t));\
    memcpy((void*)(vec->data + n),\
           (const void*)vals,\
           size * sizeof(value_t));\
    vec->count += size;\
}\
\
void vec_##T##_push_back(VEC_(value_t)* vec, value_t val) {\
    vec_##T##_insert(vec, vec_##T##_size(vec), 1, &val);\
}\
\
value_t vec_##T##_front(VEC_(value_t)* vec) {\
    return vec->data[0];\
}\
\
value_t vec_##T##_back(VEC_(value_t)* vec) {\
    return vec->data[vec_##T##_size(vec) - 1];\
}\
\
void vec_##T##_pop_back(VEC_(value_t)* vec) {\
    vec_##T##_erase(vec, vec_##T##_size(vec) - 1, 1);\
}\
\
void vec_##T##_clear(VEC_(value_t)* vec) {\
    vec_##T##_erase(vec, 0, vec_##T##_size(vec));\
}


#define VECTOR_IMPLEMENTATION(T) AUX__VECTOR_IMPLEMENTATION(T)

VECTOR_IMPLEMENTATION(value_t)

#undef value_t
#undef AUX__VEC_
#undef VEC_

#ifdef __cplusplus
}
#endif

#endif // TASK_C_VECTOR_H_FOR_TYPE__*ANY_TYPE*