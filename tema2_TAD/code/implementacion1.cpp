#include <iostream>
#include <stdexcept>    // para std::undeflow_error

template <typename T>
class Stack {
private:
    T data[100];        // arreglo de tamaño fijo
    int tope;           //  indice del elemento superior
    
public:
    Stack() : tope(-1) {}  // constructor, pila vacía

    void push(T elemento) {
        if (tope >= 99) throw std::overflow_error("Stack overflow");
        data[++top] = elemento;  // agregar elemento y actualizar top
    }

    T pop() {
        if (isEmpty()) throw std::underflow_error("Stack underflow");
        return data[tope--];  // devolver elemento superior y actualizar top
    }

    T top() const {
        if (isEmpty()) throw std::underflow_error("Stack is empty");
        return data[tope];  // devolver elemento superior sin modificar top
    }

    bool isEmpty() const {
        return tope == -1;  // pila vacía si tope es -1
    }

    int size() const {
        return tope + 1;  // número de elementos en la pila
    }
};
