/**
 * @file test_add_integers.c
 * 
 * @brief Unit Test File
 * @version 0.1
 * @date 2022-04-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef TEST
#define TEST


#include "unity.h"

#include "add_integers.h"

void test_add_integers(void);

void setUp(void)
{
}

void tearDown(void)
{
}

int main(){
    UNITY_BEGIN();

    //RUN TESTS
    RUN_TEST(test_add_integers);

    return UNITY_END();
}

void test_add_integers(void)
{
    int res=0;
    TEST_ASSERT_EQUAL( OVERFLOW, sum(INT_MAX,10,&res));
    TEST_ASSERT_EQUAL( UNDERFLOW, sum(INT_MIN,-10,&res));
    TEST_ASSERT_EQUAL( SUCCESS, sum(2,1,&res));
}


#endif // TEST
