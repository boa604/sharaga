#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

START_TEST (test_base_insert_empty)
{
    struct TSHOP tsPRODUCT;
    
    strcpy(tsPRODUCT.PRODUCT_NAME, "");
    strcpy(tsPRODUCT.CATEGORY    , "");
    strcpy(tsPRODUCT.NOTE        , "");
    tsPRODUCT.PRICE        = 0.00;
    
    ck_assert(BASE_INSERT(tsPRODUCT) == 0);
}
END_TEST

START_TEST (test_base_insert_valid)
{
    struct TSHOP tsPRODUCT;
    
    strcpy(tsPRODUCT.PRODUCT_NAME, "123");
    strcpy(tsPRODUCT.CATEGORY    , "123");
    strcpy(tsPRODUCT.NOTE        , "123");
    tsPRODUCT.PRICE        = 123.00;
    
    ck_assert(BASE_INSERT(tsPRODUCT) == 1);
}
END_TEST

Suite * money_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Money");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_base_insert_empty);
    tcase_add_test(tc_core, test_base_insert_valid);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
   int number_failed;
   Suite *s;
   SRunner *sr;

    s = money_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}