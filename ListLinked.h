#ifndef LISTLINKED_H
#define LISTLINKED_H

#include <stdexcept>
#include "List.h"
#include "Node.h"
#include <ostream>

using namespace std;

template <typename T>
class ListLinked : public List<T> {
private:
    Node<T>* first;
    int n;

public:
    ListLinked() : first(nullptr), n(0) {}

    ~ListLinked() {
        while (first != nullptr) {
            Node<T>* temp = first;
            first = first->next;
            delete temp;
        }
    }

    void insert(int pos, T e) override {
        if (pos < 0 || pos > n) {
            throw out_of_range("Posición inválida en insert");
        }
        if (pos == 0) {
            first = new Node<T>(e, first);
        } else {
            Node<T>* prev = first;
            for (int i = 0; i < pos - 1; ++i) {
                prev = prev->next;
            }
            prev->next = new Node<T>(e, prev->next);
        }
        ++n;
    }

    void append(T e) override {
        insert(n, e);
    }

    void prepend(T e) override {
        insert(0, e);
    }

    T remove(int pos) override {
        if (pos < 0 || pos >= n) {
            throw out_of_range("Posición inválida en remove");
        }
        Node<T>* toDelete;
        T data;
        if (pos == 0) {
            toDelete = first;
            first = first->next;
        } else {
            Node<T>* prev = first;
            for (int i = 0; i < pos - 1; ++i) {
                prev = prev->next;
            }
            toDelete = prev->next;
            prev->next = toDelete->next;
        }
        data = toDelete->data;
        delete toDelete;
        --n;
        return data;
    }

    T get(int pos) const override {
        if (pos < 0 || pos >= n) {
            throw out_of_range("Posición inválida en get");
        }
        Node<T>* current = first;
        for (int i = 0; i < pos; ++i) {
            current = current->next;
        }
        return current->data;
    }

    int search(T e) const override {
        Node<T>* current = first;
        int pos = 0;
        while (current != nullptr) {
            if (current->data == e) {
                return pos;
            }
            current = current->next;
            ++pos;
        }
        return -1;
    }

    bool empty() const override {
        return n == 0;
    }

    int size() const override {
        return n;
    }

    T operator[](int pos) {
        return get(pos);
    }

    friend ostream& operator<<(ostream &out, const ListLinked<T> &list) {
        Node<T>* current = list.first;
        out << "[";
        while (current != nullptr) {
            out << current->data;
            if (current->next != nullptr) out << ", ";
            current = current->next;
        }
        out << "]";
        return out;
    }
};

#endif // LISTLINKED_H

