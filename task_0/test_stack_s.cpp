#include "gtest/gtest.h"

#include "stack_s.h"

#define ONE_SITUATION_FOR_INIT_AND_DESTROY(P, TYPE, SIZE) \
    do {\
        initStack((P), int, (SIZE));\
        EXPECT_EQ(((TYPE*)((P).top) - ((TYPE*)(P).bottom)) / sizeof(int), 0);\
        destroyStack((P));\
    } while (0)


#define MANY_SITUATION_FOR_INIT_AND_DESTROY(TYPE) \
    do {\
        Stack_s p;\
        ONE_SITUATION_FOR_INIT_AND_DESTROY(p, TYPE, 0);\
        ONE_SITUATION_FOR_INIT_AND_DESTROY(p, TYPE, 1);\
        ONE_SITUATION_FOR_INIT_AND_DESTROY(p, TYPE, 2);\
        ONE_SITUATION_FOR_INIT_AND_DESTROY(p, TYPE, 10);\
        ONE_SITUATION_FOR_INIT_AND_DESTROY(p, TYPE, 100);\
        ONE_SITUATION_FOR_INIT_AND_DESTROY(p, TYPE, 12345678);\
    } while (0)

#define MANY_SITUATION_FOR_PUSH_POP_AND_SIZE(TYPE) \
    do {\
        Stack_s p;\
        initStack(p, TYPE, 12345678);\
        for (size_t i = 1; i <= 12345678; i++) {\
            pushStack(p, TYPE, 0);\
            EXPECT_EQ((size_t)i, sizeStack(p, TYPE));\
        }\
        for (int i = 12345678 - 1; i >= 0; i--) {\
            popStack(p, TYPE);\
            EXPECT_EQ((size_t)i, sizeStack(p, TYPE));\
        }\
        destroyStack(p);\
    } while (0)

TEST(MacroStack, Init_and_Destroy) {
    MANY_SITUATION_FOR_INIT_AND_DESTROY(int);
    MANY_SITUATION_FOR_INIT_AND_DESTROY(unsigned int);
    MANY_SITUATION_FOR_INIT_AND_DESTROY(double);
    MANY_SITUATION_FOR_INIT_AND_DESTROY(long long);
    MANY_SITUATION_FOR_INIT_AND_DESTROY(char);
    MANY_SITUATION_FOR_INIT_AND_DESTROY(unsigned char);
    MANY_SITUATION_FOR_INIT_AND_DESTROY(short);
}

TEST(MacroStack, Push_Pop_and_Size) {
    printf("int...\n");
    MANY_SITUATION_FOR_PUSH_POP_AND_SIZE(int);
    printf("unsigned...\n");
    MANY_SITUATION_FOR_PUSH_POP_AND_SIZE(unsigned int);
    printf("double...\n");
    MANY_SITUATION_FOR_PUSH_POP_AND_SIZE(double);
    printf("long long...\n");
    MANY_SITUATION_FOR_PUSH_POP_AND_SIZE(long long);
    printf("char...\n");
    MANY_SITUATION_FOR_PUSH_POP_AND_SIZE(char);
    printf("unsigned char...\n");
    MANY_SITUATION_FOR_PUSH_POP_AND_SIZE(unsigned char);
    printf("short...\n");
    MANY_SITUATION_FOR_PUSH_POP_AND_SIZE(short);
    printf("int pointer...\n");
    MANY_SITUATION_FOR_PUSH_POP_AND_SIZE(int*);
    printf("double pointer...\n");
    MANY_SITUATION_FOR_PUSH_POP_AND_SIZE(double*);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}