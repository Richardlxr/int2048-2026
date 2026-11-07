#include "int2048.h"
#include <cstdio>
#include <string>

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
        int extra = uinput % 10000;
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
    int group = 0;
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
        std::printf("%04d", num[i]);
    }
    if (size == 0) {
        std::cout << '0';
    }
}

// 加上一个大整数
int2048& int2048::add(const int2048&) {}
// 返回两个大整数之和
int2048 add(const int2048& a, const int2048& b) {}

// 减去一个大整数
int2048& int2048::minus(const int2048& other) {}
// 返回两个大整数之差
int2048 minus(const int2048& a, const int2048& b) {}

// ===================================
// Integer2
// ===================================

int2048 int2048::operator+() const {}
int2048 int2048::operator-() const {}

int2048& int2048::operator=(const int2048& other) {
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

int2048& int2048::operator+=(const int2048&) {}
int2048 operator+(const int2048& a, const int2048& b) {}

int2048& int2048::operator-=(const int2048&) {}
int2048 operator-(const int2048& a, const int2048& b) {}

int2048& int2048::operator*=(const int2048& other) {}
int2048 operator*(const int2048&, const int2048&) {}

int2048& int2048::operator/=(const int2048& other) {}
int2048 operator/(const int2048& a, const int2048& b) {}

int2048& int2048::operator%=(const int2048& other) {}
int2048 operator%(const int2048& a, const int2048& b) {}

std::istream& operator>>(std::istream& is, int2048& other) {}
std::ostream& operator<<(std::ostream& os, const int2048& other) {}

bool operator==(const int2048& a, const int2048& b) {}
bool operator!=(const int2048& a, const int2048& b) {}
bool operator<(const int2048& a, const int2048& b) {}
bool operator>(const int2048& a, const int2048& b) {}
bool operator<=(const int2048& a, const int2048& b) {}
bool operator>=(const int2048& a, const int2048& b) {}
} // namespace sjtu
