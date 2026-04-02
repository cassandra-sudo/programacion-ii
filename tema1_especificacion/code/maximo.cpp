#include <iostream>
#include <cassert>
#include <vector>
#include <stdexcept>

int maximo(const std::vector<int>& list) {
    if (list.empty()) throw std::invalid_argument("Lista vacía");

    int mayor = list[0];    // el primero es provisionalmente el mayor

    for (size_t i = 1; i < list.size(); ++i) {
        if (list[i] > mayor) {  // si alguno en la lista es mayor al primero, o al que lo sustituyo
            mayor = list[i];  // declaro al encontrado como mayor
        }
    }
    return mayor;
}

int main() {
    std::vector<int> list = {3, 1, 4, 1, 5, 9};
    assert(maximo(list) == 9);

    std::vector<int> list2 = {-1, -5, -3};
    assert(maximo(list2) == -1);

    std::vector<int> list3 = {42};
    assert(maximo(list3) == 42);

    try {
        std::vector<int> emptyList;
        maximo(emptyList);
        assert(false); // No debería llegar aquí
    } catch (const std::invalid_argument& e) {
        assert(std::string(e.what()) == "Lista vacía");
    }

    std::cout << "Todas las pruebas pasaron exitosamente." << std::endl;
    return 0;
}
