#include "check.h"
#include <stdio.h>
#include "test.h"

START_TEST(test_addition)
{
    int result = add(2,3);
    ck_assert_int_eq(result,5);
}
END_TEST

Suite *test_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("TestSuite");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core,test_addition);
    suite_add_tcase(s,tc_core);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = test_suite();
    sr = srunner_create(s);

    srunner_run_all(sr,CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    if(number_failed == 0){
        printf("ALL TEST PASSED\n");
        return 0;
    }
    else{
        printf("Some tests failed\n");
        return 0;
    }

}