#include "int2048.h"
#include <complex>
#include <cstdio>
#include <string>
#include <vector>

namespace sjtu {

int2048::int2048() : is_positive(true) {
    num.reserve(2048);
    num.push_back(0);
}
int2048::int2048(long long input) { read(input); }
int2048::int2048(const std::string& input) { read(input); }
int2048::int2048(const int2048& other) {
    this->num = other.num;
    this->is_positive = other.is_positive;
    normalize();
}

void int2048::read(long long input) {
    this->num.clear();
    unsigned long long uinput;
    if (input < 0) {
        this->is_positive = false;
        uinput = 0ULL - static_cast<unsigned long long>(input);
    } else {
        this->is_positive = true;
        uinput = static_cast<unsigned long long>(input);
    }

    num.reserve(2048);
    while (uinput / 10000 > 0) {
        long long extra = uinput % 10000;
        num.push_back(extra);
        uinput = uinput / 10000;
    }
    num.push_back(uinput);
    normalize();
}

void int2048::read(const std::string& input) {
    this->num.clear();
    if (input.size() == 0) {
        return;
    }
    if (input[0] == '-') {
        is_positive = false;
    } else {
        is_positive = true;
    }
    num.reserve(2048);
    int mode4 = 0;
    std::string temp_string;
    for (auto it = input.rbegin(); it != input.rend(); ++it) {
        if (*it == '-') {
            break;
        }
        if (mode4 == 4) {
            num.push_back(std::stoi(temp_string));
            mode4 = 0;
            temp_string.clear();
        }
        temp_string.insert(temp_string.begin(), *it);
        ++mode4;
    }
    if (!temp_string.empty()) {
        num.push_back(std::stoi(temp_string));
    }
    normalize();
}

void int2048::normalize() {
    int size = num.size();
    for (int i = size - 1; i >= 0; --i) {
        if (i == 0 && num[i] == 0) {
            is_positive = true;
            break;
        }
        if (num[i] == 0) {
            num.pop_back();
        } else {
            break;
        }
    }
}

void int2048::print() {
    normalize();
    if (!is_positive) {
        std::cout << '-';
    }
    int size = num.size();
    if (size > 0) {
        std::cout << num[size - 1];
    }
    for (int i = size - 2; i >= 0; --i) {
        std::printf("%04lld", num[i]);
    }
    if (size == 0) {
        std::cout << '0';
    }
}

void int2048::add_abs(const int2048& other) {
    auto a = this->num.begin();
    auto b = other.num.begin();
    bool carry = false;
    while (a != this->num.end() && b != other.num.end()) {
        long long ans_on_position = *a + *b + static_cast<int>(carry);
        if (ans_on_position >= 10000) {
            carry = true;
            ans_on_position -= 10000;
        } else {
            carry = false;
        }
        *a = ans_on_position;
        ++a;
        ++b;
    }
    while (a != this->num.end()) {
        long long ans_on_position = *a + static_cast<int>(carry);
        if (ans_on_position >= 10000) {
            carry = true;
            ans_on_position -= 10000;
        } else {
            carry = false;
        }
        *a = ans_on_position;
        ++a;
    }
    while (b != other.num.end()) {
        long long ans_on_position = *b + static_cast<int>(carry);
        if (ans_on_position >= 10000) {
            carry = true;
            ans_on_position -= 10000;
        } else {
            carry = false;
        }
        this->num.push_back(ans_on_position);
        ++b;
    }
    if (carry) {
        this->num.push_back(1);
    }
}

// 加上一个大整数
int2048& int2048::add(const int2048& other) {
    // 同号
    if (is_positive == other.is_positive) {
        add_abs(other);
        normalize();
        return *this;
    }

    // 异号
    auto a = this->num.begin();
    auto b = other.num.begin();
    int carry = 0;
    while (a != this->num.end() && b != other.num.end()) {
        long long num_on_this = is_positive ? *a : -(*a);
        long long num_on_other = other.is_positive ? *b : -(*b);
        long long ans_on_position = num_on_this + num_on_other + carry;
        if (ans_on_position < 0) {
            ans_on_position += 10000;
            carry = -1;
        } else {
            carry = 0;
        }
        *a = ans_on_position;
        ++a;
        ++b;
    }
    while (a != this->num.end()) {
        long long num_on_this = is_positive ? *a : -(*a);
        long long ans_on_position = num_on_this + carry;
        if (ans_on_position < 0) {
            ans_on_position += 10000;
            carry = -1;
        } else {
            carry = 0;
        }
        *a = ans_on_position;
        ++a;
    }
    while (b != other.num.end()) {
        long long num_on_other = other.is_positive ? *b : -(*b);
        long long ans_on_position = num_on_other + carry;
        if (ans_on_position < 0) {
            ans_on_position += 10000;
            carry = -1;
        } else {
            carry = 0;
        }
        this->num.push_back(ans_on_position);
        ++b;
    }
    if (carry == 0) {
        is_positive = true;
    } else {
        // 例如 9999-10000
        // 出来是 -1 9999
        this->is_positive = false;
        int borrow = 0;
        for (int i = 0; i < num.size(); ++i) {
            int ans_on_pos = 0 - num[i] - borrow;
            if (ans_on_pos < 0) {
                num[i] = ans_on_pos + 10000;
                borrow = 1;
            } else {
                num[i] = ans_on_pos;
                borrow = 0;
            }
        }
    }
    normalize();
    return *this;
}
// 返回两个大整数之和
int2048 add(const int2048& a, const int2048& b) {
    int2048 ans = a;
    return ans.add(b);
}

// 减去一个大整数
int2048& int2048::minus(const int2048& other) { return add(-other); }
// 返回两个大整数之差
int2048 minus(const int2048& a, const int2048& b) { return add(a, -b); }

// ===================================
// Integer2
// ===================================

int2048 int2048::operator+() const { return *this; }
int2048 int2048::operator-() const {
    int2048 ans = *this;
    ans.is_positive = !ans.is_positive;
    ans.normalize();
    return ans;
}

int2048& int2048::operator=(const int2048& other) {
    if (&other == this) {
        return *this;
    }
    this->num = other.num;
    this->is_positive = other.is_positive;
    this->normalize();
    return *this;
}
int2048& int2048::operator=(const std::string& input) {
    read(input);
    normalize();
    return *this;
}
int2048& int2048::operator=(long long other) {
    read(other);
    normalize();
    return *this;
}

int2048& int2048::operator+=(const int2048& other) { return add(other); }
int2048 operator+(const int2048& a, const int2048& b) { return add(a, b); }

int2048& int2048::operator-=(const int2048& other) { return minus(other); }
int2048 operator-(const int2048& a, const int2048& b) { return minus(a, b); }

int2048& int2048::operator*=(const int2048& other) {
    int2048 ans = *this * other;
    *this = ans;
    return *this;
}
int2048 operator*(const int2048& a, const int2048& b) {
    int2048 ans;
    int2048 tmp;

    int factor_a = 0;
    int factor_b = 0;
    for (auto x : b.num) {
        factor_a = 0;
        for (auto y : a.num) {
            tmp.num.assign(factor_a + factor_b, 0);
            long long bit = x * y;
            tmp.num.push_back(bit % 10000);
            tmp.num.push_back(bit / 10000);
            tmp.normalize();
            ans += tmp;
            ++factor_a;
        }
        ++factor_b;
    }
    if (a.is_positive == b.is_positive) {
        ans.is_positive = true;
    } else {
        ans.is_positive = false;
    }
    ans.normalize();
    return ans;
}

int2048& int2048::operator/=(const int2048& other) {}
int2048 operator/(const int2048& a, const int2048& b) {}

int2048& int2048::operator%=(const int2048& other) {}
int2048 operator%(const int2048& a, const int2048& b) {}

std::istream& operator>>(std::istream& is, int2048& other) {
    std::string in;
    is >> in;
    other.read(in);
    return is;
}
std::ostream& operator<<(std::ostream& os, const int2048& other) {
    if (!other.is_positive) {
        os << '-';
    }
    int size = other.num.size();
    if (size > 0) {
        os << other.num[size - 1];
    }

    for (int i = size - 2; i >= 0; --i) {
        std::string number = std::to_string(other.num[i]);
        int zero_to_fill = 4 - number.size();
        std::string fill;
        fill.resize(zero_to_fill, '0');
        number.insert(0, fill);
        os << number;
    }

    if (size == 0) {
        os << '0';
    }
    return os;
}

bool operator==(const int2048& a, const int2048& b) {
    if (a.is_positive != b.is_positive) {
        return false;
    }
    if (a.num.size() != b.num.size()) {
        return false;
    }
    auto x = a.num.begin();
    auto y = b.num.begin();
    while (x != a.num.end() && y != b.num.end()) {
        if (*x != *y) {
            return false;
        }
        ++x;
        ++y;
    }

    return true;
}
bool operator!=(const int2048& a, const int2048& b) { return !(a == b); }
bool operator<(const int2048& a, const int2048& b) { return (a - b).is_positive == false; }
bool operator>(const int2048& a, const int2048& b) {
    int2048 outcome = a - b;
    return outcome.is_positive && !outcome.num.empty() && outcome.num[0] > 0;
}
bool operator<=(const int2048& a, const int2048& b) {
    int2048 outcome = a - b;
    return !outcome.is_positive || outcome.num.empty() ||
           (outcome.num.size() == 1 && outcome.num[0] == 0);
}
bool operator>=(const int2048& a, const int2048& b) {
    int2048 outcome = a - b;
    return outcome.is_positive;
}
} // namespace sjtu
