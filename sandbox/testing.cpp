#include <iostream>
#include <cassert>  // para assert()
#include <vector>

int find(const std::vector<int>& list, int x) {
    for (size_t i = 0; i < list.size(); ++i) {
        if (list[i] == x) return i;  // Encontrado, devuelve el índice
        }
        return -1;  // No encontrado, devuelve -1
    }

int main() {
    std::vector<int> myList = {1, 2, 3, 7, 8};

    // assert() lanza un error si la condición es falsa
    assert(find(myList, 3) == 2);  // El número 3 está en el índice 2
    assert(find(myList, 7) == 3);  // El número 7 está en el índice 3
    assert(find(myList, 99) == -1); // no está en la lista, debería devolver -1
    std::cout << "Todos los tests pasaron exitosamente!.\n";    return 0;
}
