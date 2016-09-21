#include "gtest/gtest.h"
#include <cstring> // for memcmp
#include <algorithm> // for all_of
#include <vector>

// Test C code
extern "C" {
#include "c_vector.h"
}

// For testing whether the vector includes to the vals.
static bool vec_eq(const std::vector<value_type>& vals, Vector* vec) {
    if (vals.size() != vec_size(vec)) return false;
    return memcmp((const void*)vals.data(),
                  (const void*)vec->data,
                  vals.size() * sizeof(value_type)) == 0;
}


TEST(C_Vector, CreateVector_and_DestroyVector) {
    Vector *vec = create_vector(0), *vec_tmp;
    vec_tmp = create_vector(&vec_tmp);

    ASSERT_NE(nullptr, vec);
    EXPECT_EQ(0, vec->count);
    EXPECT_EQ(0, vec->capacity);
    destroy_vector(&vec);

    ASSERT_NE(nullptr, vec_tmp);
    EXPECT_EQ(0, vec_tmp->count);
    EXPECT_EQ(0, vec_tmp->capacity);
    destroy_vector(&vec_tmp);
}

TEST(C_Vector, Size_and_Resize) {
    Vector *vec = create_vector(0);
    EXPECT_EQ(0, vec_size(vec));
    vec_resize(vec, 0, 0);
    EXPECT_EQ(0, vec_size(vec));
    vec_resize(vec, 1, 99);
    EXPECT_EQ(1, vec_size(vec));
    EXPECT_EQ(99, vec->data[0]);
    vec_resize(vec, 1234567, 123);
    EXPECT_EQ(99, vec->data[0]);
    EXPECT_TRUE(std::all_of(vec->data + 1,
                            vec->data + 1234567,
                            [](value_type x){ return x == 123; }));
    vec_resize(vec, 5, 0);
    EXPECT_EQ(5, vec_size(vec));
    EXPECT_TRUE(vec_eq({99, 123, 123 ,123 ,123}, vec));
    vec_resize(vec, 10, 0);
    EXPECT_TRUE(vec_eq({99, 123, 123 ,123 ,123, 0, 0, 0, 0, 0}, vec));
    destroy_vector(&vec);
}

TEST(C_Vector, Capacity_and_Reserve) {
    Vector *vec = create_vector(0);
    EXPECT_GE(vec_capacity(vec), vec_size(vec));
    vec_reserve(vec, 12345678);
    EXPECT_GE(vec_capacity(vec), 12345678);
    EXPECT_EQ(0, vec_size(vec));
    vec_resize(vec, 10, 0);
    EXPECT_EQ(10, vec_size(vec));
    EXPECT_GE(vec_capacity(vec), 12345678);
    destroy_vector(&vec);
}

TEST(C_Vector, Get_and_Set) {
    Vector *vec = create_vector(0);
    vec_resize(vec, 5, 9);
    for (size_t i = 0; i < 5; i++) {
        EXPECT_EQ(9, vec_get(vec, i));
        vec_set(vec, i, i + 1);
    }
    EXPECT_TRUE(vec_eq({1, 2, 3, 4, 5}, vec));
    destroy_vector(&vec);    
}

TEST(C_Vector, Clear_and_Empty) {
    Vector *vec = create_vector(0);
    EXPECT_TRUE(vec_empty(vec));
    vec_resize(vec, 10, 0);
    EXPECT_FALSE(vec_empty(vec));
    vec_clear(vec);
    EXPECT_EQ(0, vec_size(vec));
    EXPECT_TRUE(vec_empty(vec));
    EXPECT_GE(vec_capacity(vec), 10);
    destroy_vector(&vec); 
}

TEST(C_Vector, Assignment) {
    Vector *vec = create_vector(0);
    value_type vals[] = {1, 2, 3, 4, 5};
    vec_assign(vec, 5, vals);
    EXPECT_TRUE(vec_eq({1, 2, 3, 4, 5}, vec));
    destroy_vector(&vec);
}

TEST(C_Vector, Insert_and_PushBack) {
    Vector *vec = create_vector(0);
    value_type vals_1[] = {1, 2}, vals_2[] = {3}, vals_3[] = {4};

    vec_insert(vec, 0, 2, vals_1);
    vec_insert(vec, 0, 1, vals_2);
    vec_insert(vec, 1, 1, vals_3);
    EXPECT_TRUE(vec_eq({3, 4, 1, 2}, vec));
    destroy_vector(&vec);
    
    create_vector(&vec);
    for (size_t i = 0; i < 1234; i++)
        vec_push_back(vec, i);
    for (size_t i = 0; i < 1234; i++)
        EXPECT_EQ(i, vec_get(vec, i));
    destroy_vector(&vec);
}

TEST(C_Vector, Erase_and_PopBack) {
    Vector *vec = create_vector(0);
    value_type vals[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vec_insert(vec, 0, 10, vals);
    vec_erase(vec, 0, 2);
    EXPECT_EQ(8, vec_size(vec));
    EXPECT_TRUE(vec_eq({3, 4, 5, 6, 7, 8, 9, 10}, vec));
    vec_erase(vec, 6, 2);
    EXPECT_TRUE(vec_eq({3, 4, 5, 6, 7, 8}, vec));
    vec_erase(vec, 2, 3);
    EXPECT_TRUE(vec_eq({3, 4, 8}, vec));
    vec_pop_back(vec);
    EXPECT_TRUE(vec_eq({3, 4}, vec));
    vec_pop_back(vec);
    EXPECT_TRUE(vec_eq({3}, vec));
    vec_pop_back(vec);
    EXPECT_TRUE(vec_eq({}, vec));
    destroy_vector(&vec);
}

TEST(C_Vector, Front_and_Back) {
    Vector *vec = create_vector(0);
    value_type vals[] = {1, 2, 3, 4, 5};
    vec_assign(vec, 5, vals);
    EXPECT_EQ(1, vec_front(vec));
    EXPECT_EQ(5, vec_back(vec));
    vec_erase(vec, 0, 1);
    vec_pop_back(vec);
    EXPECT_EQ(2, vec_front(vec));
    EXPECT_EQ(4, vec_back(vec));
    destroy_vector(&vec);
}

TEST(C_Vector, CopyVector_and_DataPointer) {
    Vector *vec = create_vector(0), *vec_tmp;
    value_type vals[] = {1, 2, 3, 4, 5};
    vec_assign(vec, 5, vals);
    vec_tmp = copy_vector(vec, NULL);
    EXPECT_TRUE(vec_eq({1, 2, 3, 4, 5}, vec_tmp));
    EXPECT_NE(vec->data, vec_tmp->data);
    EXPECT_EQ(vec_tmp->data, vec_data(vec_tmp));
    destroy_vector(&vec_tmp);
    copy_vector(vec, &vec_tmp);
    EXPECT_TRUE(vec_eq({1, 2, 3, 4, 5}, vec_tmp));
    EXPECT_NE(vec->data, vec_tmp->data);
    EXPECT_EQ(vec_tmp->data, vec_data(vec_tmp));
    destroy_vector(&vec);
    destroy_vector(&vec_tmp);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
