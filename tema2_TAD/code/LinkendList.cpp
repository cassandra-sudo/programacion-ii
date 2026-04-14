#include<iostream>
#include<stdexcept>

template <typename T>
class LinkendList {
    private:
        struct Node {
            T data;
            Node* next;
            Node(T d) : data(d), next(nullptr) {} 
        };
    Node* head;
    int currentSize;

    public:
    LinkendList() : head(nullptr), currentSize(0) {}

    ~LinkendList() {
        while (!isEmpty()) pop_front();
    }

    void push_front(T data) {
        Node* newNode = new Node(data);
        newNode->next = head;
        head = newNode;
        currentSize++;
    }

    T pop_front() {
        if (isEmpty()) throw std::underflow_error("List is empty");
        Node* temp = head;
        T value = temp->data;
        head = head->next;
        delete temp;
        currentSize--;
        return value;
    }

    T front() const {
        if(isEmpty()) throw std::underflow_error("List is empty");
        return head->data;
    }

    bool isEmpty() const {
        return currentSize == 0;
    }
    int size() const {
        return currentSize;
    }
};
