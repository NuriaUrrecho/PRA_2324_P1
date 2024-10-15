#ifndef LISTLINKED_H
#define LISTLINKED_H

#include <ostream>
#include <stdexcept>
#include "Node.h"
#include "List.h"

template <typename T>
class ListLinked : public List<T> {
private:
    Node<T>* first;  // Puntero al primer nodo de la lista
    int n;          // Número de elementos en la lista

public:
    // Constructor
    ListLinked() : first(nullptr), n(0) {}

    // Destructor
    ~ListLinked() {
        Node<T>* aux = first;
        while (aux != nullptr) {
            Node<T>* toDelete = aux;
            aux = aux->next;
            delete toDelete;
        }
    }

    // Sobrecarga del operador []
    T operator[](int pos) {
        if (pos < 0 || pos >= n) {
            throw std::out_of_range("Índice fuera de rango");
        }
        Node<T>* current = first;
        for (int i = 0; i < pos; ++i) {
            current = current->next;
        }
        return current->data;
    }

    // Sobrecarga del operador <<
    friend std::ostream& operator<<(std::ostream &out, const ListLinked<T> &list) {
        Node<T>* current = list.first;
        out << "[";
        while (current != nullptr) {
            out << current->data;
            if (current->next != nullptr) {
                out << ", ";
            }
            current = current->next;
        }
        out << "]";
        return out;
    }

    // Implementación de métodos de la interfaz List<T>
    void insert(int pos, T e) override {
        if (pos < 0 || pos > n) {
            throw std::out_of_range("Índice fuera de rango");
        }
        Node<T>* newNode = new Node<T>(e);
        if (pos == 0) {
            newNode->next = first;
            first = newNode;
        } else {
            Node<T>* current = first;
            for (int i = 0; i < pos - 1; ++i) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
        n++;
    }

    void append(T e) override {
        Node<T>* newNode = new Node<T>(e);
        if (first == nullptr) {
            first = newNode;
        } else {
            Node<T>* current = first;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
        n++;
    }

    void prepend(T e) override {
        Node<T>* newNode = new Node<T>(e);
        newNode->next = first;
        first = newNode;
        n++;
    }

    T remove(int pos) override {
        if (pos < 0 || pos >= n) {
            throw std::out_of_range("Índice fuera de rango");
        }
        Node<T>* toDelete;
        if (pos == 0) {
            toDelete = first;
            first = first->next;
        } else {
            Node<T>* current = first;
            for (int i = 0; i < pos - 1; ++i) {
                current = current->next;
            }
            toDelete = current->next;
            current->next = toDelete->next;
        }
        T data = toDelete->data;
        delete toDelete;
        n--;
        return data;
    }

    T get(int pos) override {
        return operator[](pos);
    }

    int search(T e) override {
        Node<T>* current = first;
        for (int i = 0; i < n; ++i) {
            if (current->data == e) {
                return i;
            }
            current = current->next;
        }
        return -1; // No encontrado
    }

    bool empty() override {
        return n == 0;
    }

    int size() override { 
        return n;
    }
};

#endif // LISTLINKED_H
