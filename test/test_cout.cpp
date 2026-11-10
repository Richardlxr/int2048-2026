#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec = {0};
    int size = vec.size();
    if (size > 0) {
        std::cout << vec[size - 1];
    }
    for (int i = size - 2; i >= 0; --i) {
        std::string number = std::to_string(vec[i]);
        int zero_to_fill = 4 - number.size();
        std::string fill;
        fill.resize(zero_to_fill, '0');
        number.insert(0, fill);
        std::cout << number;
    }
}