#include <iostream>
#include <stdexcept>

template <typename T>
class StackList {
private:
    struct Node {
        T data;
        Node* next;
        Node(T d) : data(d), next(nullptr) {}
    };
    Node* top_ptr;  // Pointer to the top of the stack
    int currentSize;       // Number of elements in the StackList

public:
    StackList() : top_ptr(nullptr), currentSize(0) {}

    ~StackList() {
        while (!isEmpty()) pop();
    }

    void push(T element) {
        Node* new_node = new Node(element);
        new_node->next = top_ptr;
        top_ptr = new_node;
        size++;
    }

    T pop() {
        if (isEmpty()) throw std::underflow_error("Stack is empty");
        Node* temp = top_ptr;
        T valor = temp->data;
        top_ptr = top_ptr->next;
        delete temp;    // Free the memory of the popped node
        size--;
        return valor;
    }

    T top() const {
        if (isEmpty()) throw std::underflow_error("Stack is empty");
        return top_ptr->data;
    }

    bool isEmpty() const {
        return top_ptr == nullptr;
    }

    int size() const {
        return size;
    }
};  
