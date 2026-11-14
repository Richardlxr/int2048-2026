#include "../src/include/int2048.h"
#include <cstdlib>
#include <iostream>

int fail_count = 0;

void check(const sjtu::int2048& got, long long expected, long long x, long long y, const char* op) {
    if (got == sjtu::int2048(expected)) {
        return;
    }
    std::cout << "[FAIL] " << x << ' ' << op << ' ' << y << "\n  expected: " << expected
              << "\n  got:      " << got << '\n';
    ++fail_count;
}

long long random_number(long long limit) {
    long long r = static_cast<long long>(std::rand()) * RAND_MAX + std::rand();
    return r % (2 * limit + 1) - limit;
}

int main() {
    std::srand(2048);

    const int kTimes = 100000;
    for (int i = 0; i < kTimes; ++i) {
        long long x = random_number(1000000000);
        long long y = random_number(1000000000);

        if (i % 10 == 1) {
            y = random_number(100);
        }
        if (i % 10 == 2) {
            x = 0;
        }
        if (i % 10 == 3) {
            y = 0;
        }

        sjtu::int2048 a(x);
        sjtu::int2048 b(y);
        check(a * b, x * y, x, y, "*");

        a *= b;
        check(a, x * y, x, y, "*=");
    }

    std::cout << kTimes << " cases, " << fail_count << " failed\n";
    return fail_count == 0 ? 0 : 1;
}
