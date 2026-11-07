#include "../src/include/int2048.h"
#include <iostream>

int main() {
    sjtu::int2048 superint1;
    sjtu::int2048 superint2;
    superint1 = "1";
    superint2 = "9999";
    superint1.add(superint2);
    superint1.print();
    std::cout << '\n';
}