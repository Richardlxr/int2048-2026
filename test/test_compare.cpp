#include "../src/include/int2048.h"
#include <iostream>

void test_comp(bool outcome, std::string messg = "") {
    if (outcome) {
        std::cout << messg << '\n';
    } else {
        std::cout << messg << " is not true" << '\n';
    }
}

int main() {
    sjtu::int2048 superint1;
    sjtu::int2048 superint2;
    sjtu::int2048 superint3;
    superint1 = "-10000";
    superint2 = "9999";
    superint3 = "-10000";
    test_comp(superint1 < superint2, "superint1 < superint2");
    test_comp(superint1 <= superint2, "superint1 <= superint2");
    test_comp(superint1 >= superint2, "superint1 >= superint2");
    test_comp(superint1 > superint2, "superint1 > superint2");
    test_comp(superint1 < superint3, "superint1 < superint3");
    test_comp(superint1 <= superint3, "superint1 <= superint3");
    test_comp(superint1 >= superint3, "superint1 >= superint3");
    test_comp(superint1 > superint3, "superint1 > superint3");
}