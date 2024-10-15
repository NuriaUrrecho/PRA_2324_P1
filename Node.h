#ifndef NODE_H
#define NODE_H

#include <iostream>

template <typename T>
class Node {
public:
    T data;            // El elemento almacenado, de tipo genérico T
    Node<T>* next;    // Puntero al siguiente nodo

    // Constructor
    Node(T data, Node<T>* next = nullptr) : data(data), next(next) {}

    // Sobrecarga del operador <<
    friend std::ostream& operator<<(std::ostream &out, const Node<T> &node) {
        out << node.data;
        return out;
    }
};

#endif
