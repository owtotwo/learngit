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

VEC_(VALUE_T)* create_vector(VEC_(VALUE_T)** vec_ptr) {
    VEC_(VALUE_T)* ptr = (VEC_(VALUE_T)*)malloc(sizeof(VEC_(VALUE_T)));
    ptr->count = 0;
    ptr->capacity = 0;
    ptr->data = (VALUE_T*)malloc(0);
    if (vec_ptr != NULL) *vec_ptr = ptr;
    return ptr;
}

void destroy_vector(VEC_(VALUE_T)** vec_ptr) {
    if (vec_ptr != NULL) {
        free((*vec_ptr)->data);
        free(*vec_ptr);
        *vec_ptr = NULL;
    }
}

VEC_(VALUE_T)* copy_vector(VEC_(VALUE_T)* vec_src, VEC_(VALUE_T)** vec_ptr) {
    VEC_(VALUE_T)* ptr = create_vector(NULL);
    vec_assign(ptr, vec_size(vec_src), vec_data(vec_src));
    if (vec_ptr != NULL) *vec_ptr = ptr;
    return ptr;
}

size_t vec_size(VEC_(VALUE_T)* vec) {
    return vec->count;
}

size_t vec_capacity(VEC_(VALUE_T)* vec) {
    return vec->capacity;
}

void vec_resize(VEC_(VALUE_T)* vec, size_t n, VALUE_T val) {
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

int vec_empty(VEC_(VALUE_T)* vec) {
    return vec_size(vec) == 0;
}

void vec_reserve(VEC_(VALUE_T)* vec, size_t n) {
    if (vec_capacity(vec) < n) {
        vec->data = realloc((void*)vec->data, n * sizeof(VALUE_T));
        vec->capacity = n;
    }
}

VALUE_T vec_get(VEC_(VALUE_T)* vec, size_t n) {
    return vec->data[n];
}

void vec_set(VEC_(VALUE_T)* vec, size_t n, VALUE_T val) {
    vec->data[n] = val;
}

void vec_assign(VEC_(VALUE_T)* vec, size_t size, VALUE_T vals[]) {
    vec_reserve(vec, size);
    memcpy((void*)vec->data, (const void*)vals, size * sizeof(VALUE_T));
    vec->count = size;
}

void vec_insert(VEC_(VALUE_T)* vec, size_t n, size_t size, VALUE_T vals[]) {
    size_t required_size = vec_size(vec) + size;
    size_t new_size = MAX(required_size, C_VECTOR_GROWTH_RATE * vec_size(vec));
    vec_reserve(vec, new_size);
    memcpy_backward((void*)(vec->data + n + size),
                    (const void*)(vec->data + n),
                    (vec_size(vec) - n) * sizeof(VALUE_T));
    memcpy((void*)(vec->data + n),
           (const void*)vals,
           size * sizeof(VALUE_T));
    vec->count += size;
}

void vec_push_back(VEC_(VALUE_T)* vec, VALUE_T val) {
    vec_insert(vec, vec_size(vec), 1, (VALUE_T[1]){val});
}

VALUE_T vec_front(VEC_(VALUE_T)* vec) {
    return vec->data[0];
}

VALUE_T vec_back(VEC_(VALUE_T)* vec) {
    return vec->data[vec_size(vec) - 1];
}

void vec_erase(VEC_(VALUE_T)* vec, size_t n, size_t size) {
    memcpy_forward((void*)(vec->data + n),
           (const void*)(vec->data + n + size),
           (vec_size(vec) - n - size) * sizeof(VALUE_T));
    vec->count -= size;
}

void vec_pop_back(VEC_(VALUE_T)* vec) {
    vec_erase(vec, vec_size(vec) - 1, 1);
}

void vec_clear(VEC_(VALUE_T)* vec) {
    vec_erase(vec, 0, vec_size(vec));
}

VALUE_T* vec_data(VEC_(VALUE_T)* vec) {
    return vec->data;
}
