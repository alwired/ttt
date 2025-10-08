#include ".\unity\unity.h"
#include "..\src\ttt.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_atest(void) {
    TEST_ASSERT(atest());
}

// not needed when using generate_test_runner.rb
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_atest);
    return UNITY_END();
}