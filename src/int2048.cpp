#include "int2048.h"
#include <string>

namespace sjtu {

int2048::int2048() : is_positibve(true) { num.reserve(2048); }
int2048::int2048(long long input) { num.reserve(2048); }
int2048::int2048(const std::string& input) { read(input); }
int2048::int2048(const int2048& other) { this->num = other.num; }

void int2048::read(const std::string& input) {}

void int2048::normalize() {}

void int2048::print() {}

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

int2048& int2048::operator=(const int2048& other) {}

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

std::istream& operator>>(std::istream& is, const int2048& other) {}
std::ostream& operator<<(std::ostream& os, const int2048& other) {}

bool operator==(const int2048& a, const int2048& b) {}
bool operator!=(const int2048& a, const int2048& b) {}
bool operator<(const int2048& a, const int2048& b) {}
bool operator>(const int2048& a, const int2048& b) {}
bool operator<=(const int2048& a, const int2048& b) {}
bool operator>=(const int2048& a, const int2048& b) {}
} // namespace sjtu
