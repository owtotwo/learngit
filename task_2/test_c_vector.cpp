#include "gtest/gtest.h"
#include <cstring> // for memcmp
#include <algorithm> // for all_of
#include <vector>

// Test C code

#define AUX__MANY_TEST_FOR_MANY_TYPE(T) \
typedef C_VECTOR_VALUE_TYPE value_type;\
\
static bool vec_##T##_eq(const std::vector<value_type>& vals, Vector_##T* vec) {\
    if (vals.size() != vec_##T##_size(vec)) return false;\
    return memcmp((const void*)vals.data(),\
                  (const void*)vec->data,\
                  vals.size() * sizeof(value_type)) == 0;\
}\
\
TEST(C_##T##_Vector, CreateVector_and_DestroyVector) {\
    Vector_##T *vec = create_vector_##T(0), *vec_##T##_tmp;\
    vec_##T##_tmp = create_vector_##T(&vec_##T##_tmp);\
\
    ASSERT_NE(nullptr, vec);\
    EXPECT_EQ(0, vec->count);\
    EXPECT_EQ(0, vec->capacity);\
    destroy_vector_##T(&vec);\
\
    ASSERT_NE(nullptr, vec_##T##_tmp);\
    EXPECT_EQ(0, vec_##T##_tmp->count);\
    EXPECT_EQ(0, vec_##T##_tmp->capacity);\
    destroy_vector_##T(&vec_##T##_tmp);\
}\
\
TEST(C_##T##_Vector, Size_and_Resize) {\
    Vector_##T *vec = create_vector_##T(0);\
    EXPECT_EQ(0, vec_##T##_size(vec));\
    vec_##T##_resize(vec, 0, 0);\
    EXPECT_EQ(0, vec_##T##_size(vec));\
    vec_##T##_resize(vec, 1, 99);\
    EXPECT_EQ(1, vec_##T##_size(vec));\
    EXPECT_EQ(99, vec->data[0]);\
    vec_##T##_resize(vec, 1234567, 123);\
    EXPECT_EQ(99, vec->data[0]);\
    EXPECT_TRUE(std::all_of(vec->data + 1,\
                            vec->data + 1234567,\
                            [](value_type x){ return x == 123; }));\
    vec_##T##_resize(vec, 5, 0);\
    EXPECT_EQ(5, vec_##T##_size(vec));\
    EXPECT_TRUE(vec_##T##_eq({99, 123, 123 ,123 ,123}, vec));\
    vec_##T##_resize(vec, 10, 0);\
    EXPECT_TRUE(vec_##T##_eq({99, 123, 123 ,123 ,123, 0, 0, 0, 0, 0}, vec));\
    destroy_vector_##T(&vec);\
}\
\
TEST(C_##T##_Vector, Capacity_and_Reserve) {\
    Vector_##T *vec = create_vector_##T(0);\
    EXPECT_GE(vec_##T##_capacity(vec), vec_##T##_size(vec));\
    vec_##T##_reserve(vec, 12345678);\
    EXPECT_GE(vec_##T##_capacity(vec), 12345678);\
    EXPECT_EQ(0, vec_##T##_size(vec));\
    vec_##T##_resize(vec, 10, 0);\
    EXPECT_EQ(10, vec_##T##_size(vec));\
    EXPECT_GE(vec_##T##_capacity(vec), 12345678);\
    destroy_vector_##T(&vec);\
}\
\
TEST(C_##T##_Vector, Get_and_Set) {\
    Vector_##T *vec = create_vector_##T(0);\
    vec_##T##_resize(vec, 5, 9);\
    for (size_t i = 0; i < 5; i++) {\
        EXPECT_EQ(9, vec_##T##_get(vec, i));\
        vec_##T##_set(vec, i, i + 1);\
    }\
    EXPECT_TRUE(vec_##T##_eq({1, 2, 3, 4, 5}, vec));\
    destroy_vector_##T(&vec);\
}\
\
TEST(C_##T##_Vector, Clear_and_Empty) {\
    Vector_##T *vec = create_vector_##T(0);\
    EXPECT_TRUE(vec_##T##_empty(vec));\
    vec_##T##_resize(vec, 10, 0);\
    EXPECT_FALSE(vec_##T##_empty(vec));\
    vec_##T##_clear(vec);\
    EXPECT_EQ(0, vec_##T##_size(vec));\
    EXPECT_TRUE(vec_##T##_empty(vec));\
    EXPECT_GE(10, vec_##T##_capacity(vec));\
    destroy_vector_##T(&vec);\
}\
\
TEST(C_##T##_Vector, Assignment) {\
    Vector_##T *vec = create_vector_##T(0);\
    value_type vals[] = {1, 2, 3, 4, 5};\
    vec_##T##_assign(vec, 5, vals);\
    EXPECT_TRUE(vec_##T##_eq({1, 2, 3, 4, 5}, vec));\
    destroy_vector_##T(&vec);\
}\
\
TEST(C_##T##_Vector, Insert_and_PushBack) {\
    Vector_##T *vec = create_vector_##T(0);\
    value_type vals_1[] = {1, 2}, vals_2[] = {3}, vals_3[] = {4};\
\
    vec_##T##_insert(vec, 0, 2, vals_1);\
    vec_##T##_insert(vec, 0, 1, vals_2);\
    vec_##T##_insert(vec, 1, 1, vals_3);\
    EXPECT_TRUE(vec_##T##_eq({3, 4, 1, 2}, vec));\
    destroy_vector_##T(&vec);\
    \
    create_vector_##T(&vec);\
    for (size_t i = 0; i < 1234; i++)\
        vec_##T##_push_back(vec, i);\
    for (size_t i = 0; i < 1234; i++)\
        EXPECT_EQ(i, vec_##T##_get(vec, i));\
    destroy_vector_##T(&vec);\
}\
\
TEST(C_##T##_Vector, Erase_and_PopBack) {\
    Vector_##T *vec = create_vector_##T(0);\
    value_type vals[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};\
    vec_##T##_insert(vec, 0, 10, vals);\
    vec_##T##_erase(vec, 0, 2);\
    EXPECT_EQ(8, vec_##T##_size(vec));\
    EXPECT_TRUE(vec_##T##_eq({3, 4, 5, 6, 7, 8, 9, 10}, vec));\
    vec_##T##_erase(vec, 6, 2);\
    EXPECT_TRUE(vec_##T##_eq({3, 4, 5, 6, 7, 8}, vec));\
    vec_##T##_erase(vec, 2, 3);\
    EXPECT_TRUE(vec_##T##_eq({3, 4, 8}, vec));\
    vec_##T##_pop_back(vec);\
    EXPECT_TRUE(vec_##T##_eq({3, 4}, vec));\
    vec_##T##_pop_back(vec);\
    EXPECT_TRUE(vec_##T##_eq({3}, vec));\
    vec_##T##_pop_back(vec);\
    EXPECT_TRUE(vec_##T##_eq({}, vec));\
    destroy_vector_##T(&vec);\
}\
\
TEST(C_##T##_Vector, Front_and_Back) {\
    Vector_##T *vec = create_vector_##T(0);\
    value_type vals[] = {1, 2, 3, 4, 5};\
    vec_##T##_assign(vec, 5, vals);\
    EXPECT_EQ(1, vec_##T##_front(vec));\
    EXPECT_EQ(5, vec_##T##_back(vec));\
    vec_##T##_erase(vec, 0, 1);\
    vec_##T##_pop_back(vec);\
    EXPECT_EQ(2, vec_##T##_front(vec));\
    EXPECT_EQ(4, vec_##T##_back(vec));\
    destroy_vector_##T(&vec);\
}\
\
TEST(C_##T##_Vector, CopyVector_and_DataPointer) {\
    Vector_##T *vec = create_vector_##T(0), *vec_##T##_tmp;\
    value_type vals[] = {1, 2, 3, 4, 5};\
    vec_##T##_assign(vec, 5, vals);\
    vec_##T##_tmp = copy_vector_##T(vec, NULL);\
    EXPECT_TRUE(vec_##T##_eq({1, 2, 3, 4, 5}, vec_##T##_tmp));\
    EXPECT_NE(vec->data, vec_##T##_tmp->data);\
    EXPECT_EQ(vec_##T##_tmp->data, vec_##T##_data(vec_##T##_tmp));\
    destroy_vector_##T(&vec_##T##_tmp);\
    copy_vector_##T(vec, &vec_##T##_tmp);\
    EXPECT_TRUE(vec_##T##_eq({1, 2, 3, 4, 5}, vec_##T##_tmp));\
    EXPECT_NE(vec->data, vec_##T##_tmp->data);\
    EXPECT_EQ(vec_##T##_tmp->data, vec_##T##_data(vec_##T##_tmp));\
    destroy_vector_##T(&vec);\
    destroy_vector_##T(&vec_##T##_tmp);\
}

#define MANY_TEST_FOR_MANY_TYPE(T) AUX__MANY_TEST_FOR_MANY_TYPE(T)


#define C_VECTOR_VALUE_TYPE int
#include "c_vector.h"
MANY_TEST_FOR_MANY_TYPE(int)
/*
#define C_VECTOR_VALUE_TYPE short
#include "c_vector.h"
MANY_TEST_FOR_MANY_TYPE(short)


#define C_VECTOR_VALUE_TYPE char
#include "c_vector.h"
MANY_TEST_FOR_MANY_TYPE(char)

#define C_VECTOR_VALUE_TYPE unsigned
#include "c_vector.h"
MANY_TEST_FOR_MANY_TYPE(unsigned)

#define C_VECTOR_VALUE_TYPE double
#include "c_vector.h"
MANY_TEST_FOR_MANY_TYPE(double)

#define C_VECTOR_VALUE_TYPE float
#include "c_vector.h"
MANY_TEST_FOR_MANY_TYPE(float)

#define C_VECTOR_VALUE_TYPE float
#include "c_vector.h"
MANY_TEST_FOR_MANY_TYPE(float)
*/
int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
