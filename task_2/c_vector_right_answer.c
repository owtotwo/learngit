// The implementation of the C vector in task 2.
// Copyright (c) 2016 sysu_AT.

#include <stdlib.h> // for malloc, free, NULL
#include <stdint.h> // for uintptr_t
#include <string.h> // for memset
#include "c_vector.h"

/*-- Aux functions --*/

// Returns the largest of x and y.
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

// Copy the values of n bytes from the location pointed to by source (src)
//    directly to the memory block pointed to by destination (dst).
// It does support overlapping buffers, but it is only safe when dst > src, so
//    always do it backwards.
// For speedy copying, optimize the common case where both pointers and the
//    length are word-aligned, and copy word-at-a-time instead of
//    byte-at-a-time. Otherwise, copy by bytes.
static inline void* memcpy_backward(void * dst, const void * src, size_t n) {
    if ((uintptr_t)dst % sizeof(long) == 0 &&
        (uintptr_t)src % sizeof(long) == 0 &&
        n % sizeof(long) == 0) {
            long* d = dst;
            const long* s = src;
            n /= sizeof(long);
            while (n--) d[n] = s[n];
    } else {
            char* d = dst;
            const char* s = src;
            while (n--) d[n] = s[n];
    }
    return dst;
}

// You should make sure that dst < src before you call this.
static inline void* memcpy_forward(void * dst, const void * src, size_t n) {
    if ((uintptr_t)dst % sizeof(long) == 0 &&
        (uintptr_t)src % sizeof(long) == 0 &&
        n % sizeof(long) == 0) {
            long* d = dst;
            const long* s = src;
            n /= sizeof(long);
            for (size_t i = 0; i < n; i++) d[i] = s[i];
    } else {
            char* d = dst;
            const char* s = src;
            for (size_t i = 0; i < n; i++) d[i] = s[i];
    }
    return dst;
}


/*-- Implementation detials --*/

Vector* create_vector(Vector** vec_ptr) {
    Vector* ptr = (Vector*)malloc(sizeof(Vector));
    ptr->count = 0;
    ptr->capacity = 0;
    ptr->data = (value_type*)malloc(0);
    if (vec_ptr != NULL) *vec_ptr = ptr;
    return ptr;
}

void destroy_vector(Vector** vec_ptr) {
    if (vec_ptr != NULL) {
        free((*vec_ptr)->data);
        free(*vec_ptr);
        *vec_ptr = NULL;
    }
}

Vector* copy_vector(Vector* vec_src, Vector** vec_ptr) {
    Vector* ptr = create_vector(NULL);
    vec_assign(ptr, vec_size(vec_src), vec_data(vec_src));
    if (vec_ptr != NULL) *vec_ptr = ptr;
    return ptr;
}

size_t vec_size(Vector* vec) {
    return vec->count;
}

size_t vec_capacity(Vector* vec) {
    return vec->capacity;
}

void vec_resize(Vector* vec, size_t n, value_type val) {
    size_t current_size = vec_size(vec);
    if (n < current_size) {
        vec_erase(vec, n, current_size - n);
    } else if (n > current_size) {
        vec_reserve(vec, n);
        for (size_t i = current_size; i < n; i++)
            vec->data[i] = val;
        vec->count = n;
    }
}

int vec_empty(Vector* vec) {
    return vec_size(vec) == 0;
}

void vec_reserve(Vector* vec, size_t n) {
    if (vec_capacity(vec) < n) {
        vec->data = realloc((void*)vec->data, n * sizeof(value_type));
        vec->capacity = n;
    }
}

value_type vec_get(Vector* vec, size_t n) {
    return vec->data[n];
}

void vec_set(Vector* vec, size_t n, value_type val) {
    vec->data[n] = val;
}

void vec_assign(Vector* vec, size_t size, value_type vals[]) {
    vec_reserve(vec, size);
    memcpy((void*)vec->data, (const void*)vals, size * sizeof(value_type));
    vec->count = size;
}

void vec_insert(Vector* vec, size_t n, size_t size, value_type vals[]) {
    size_t required_size = vec_size(vec) + size;
    size_t new_size = MAX(required_size, C_VECTOR_GROWTH_RATE * vec_size(vec));
    vec_reserve(vec, new_size);
    memcpy_backward((void*)(vec->data + n + size),
                    (const void*)(vec->data + n),
                    (vec_size(vec) - n) * sizeof(value_type));
    memcpy((void*)(vec->data + n),
           (const void*)vals,
           size * sizeof(value_type));
    vec->count += size;
}

void vec_push_back(Vector* vec, value_type val) {
    vec_insert(vec, vec_size(vec), 1, (value_type[1]){val});
}

value_type vec_front(Vector* vec) {
    return vec->data[0];
}

value_type vec_back(Vector* vec) {
    return vec->data[vec_size(vec) - 1];
}

void vec_erase(Vector* vec, size_t n, size_t size) {
    memcpy_forward((void*)(vec->data + n),
           (const void*)(vec->data + n + size),
           (vec_size(vec) - n - size) * sizeof(value_type));
    vec->count -= size;
}

void vec_pop_back(Vector* vec) {
    vec_erase(vec, vec_size(vec) - 1, 1);
}

void vec_clear(Vector* vec) {
    vec_erase(vec, 0, vec_size(vec));
}

value_type* vec_data(Vector* vec) {
    return vec->data;
}
