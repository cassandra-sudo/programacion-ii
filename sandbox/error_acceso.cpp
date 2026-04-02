#include <iostream>
#include <vector>

int main() {
    std::vector<int> v = {1, 2, 3};

    // Error: acceso fuera de limites
    // v tiene indices 0, 1, 2 = el indice 5 no existe
    std::cout << v[5] << std::endl;

    return 0;
}
