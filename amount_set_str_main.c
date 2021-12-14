#include "amount_set_str_tests.h"
#include "tests/test_utilities.h"

int main()
{
    RUN_TEST(testAmountSetCreateDestroy);
    RUN_TEST(testRegisterAndClearAndContains);
    RUN_TEST(testCopyAndRegisterAndGetSize);
    RUN_TEST(testDelete);
    RUN_TEST(testGetFirstGetNext);
    RUN_TEST(testGetAmountAndChangeAmount);
    return 0;
}