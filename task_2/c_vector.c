// The implementation of the C vector in task 2.
// Copyright (c) 2016 sysu_AT. All righs reserved.

/* You can include some C standard libraries here. */

#include "c_vector.h"

/*-- Aux functions --*/

// Returns the largest of x and y.
#define MAX(x, y) /* Your code here. */

// You can take the place of two functions below by memmove in <string.h>, or
// challenge yourself by the implementations of them.

// Copy the values of n bytes from the location pointed to by source (src)
//    directly to the memory block pointed to by destination (dst).
// It does support overlapping buffers, but it is only safe when dst > src, so
//    always do it backwards.
// For speedy copying, optimize the common case where both pointers and the
//    length are word-aligned, and copy word-at-a-time instead of
//    byte-at-a-time. Otherwise, copy by bytes. (Optional)
static inline void* memcpy_backward(void* dst, const void* src, size_t n) {
    /* Your code here. */
    return dst;
}

// It is safe for the overlapping buffers unlike the memcpy in <string.h>.
// You should make sure that dst < src before you call this.
static inline void* memcpy_forward(void* dst, const void* src, size_t n) {
    /* Your code here. */
    return dst;
}


/*-- Implementation detials --*/

Vector* create_vector(Vector** vec_ptr) {
    /* Your code here. */
}

void destroy_vector(Vector** vec_ptr) {
    /* Your code here. */
}

Vector* copy_vector(Vector* vec_src, Vector** vec_ptr) {
    /* Your code here. */
}

size_t vec_size(Vector* vec) {
    /* Your code here. */
}

size_t vec_capacity(Vector* vec) {
    /* Your code here. */
}

void vec_resize(Vector* vec, size_t n, value_type val) {
    /* Your code here. */
}

int vec_empty(Vector* vec) {
    /* Your code here. */
}

void vec_reserve(Vector* vec, size_t n) {
    /* Your code here. */
}

value_type vec_get(Vector* vec, size_t n) {
    /* Your code here. */
}

void vec_set(Vector* vec, size_t n, value_type val) {
    /* Your code here. */
}

void vec_assign(Vector* vec, size_t size, value_type vals[]) {
    /* Your code here. */
}

void vec_insert(Vector* vec, size_t n, size_t size, value_type vals[]) {
    /* Your code here. */
}

void vec_push_back(Vector* vec, value_type val) {
    /* Your code here. */
}

value_type vec_front(Vector* vec) {
    /* Your code here. */
}

value_type vec_back(Vector* vec) {
    /* Your code here. */
}

void vec_erase(Vector* vec, size_t n, size_t size) {
    /* Your code here. */
}

void vec_pop_back(Vector* vec) {
    /* Your code here. */
}

void vec_clear(Vector* vec) {
    /* Your code here. */
}

value_type* vec_data(Vector* vec) {
    /* Your code here. */
}
