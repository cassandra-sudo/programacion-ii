#include <iostream>
#include <cassert>
#include <vector>
#include <stdexcept>

int maximo(const std::vector<int>& list) {
    if (list.empty()) throw std::invalid_argument("Lista vacía");
}
