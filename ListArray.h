#include <stdexcept>
#include <iostream>
#include "List.h"

template <typename T>
class ListArray : public List<T> {
private:
    T* arr;
    int max;
    int n;
    static const int MINSIZE = 2;

    void resize(int new_size) {
        T* newArr = new T[new_size];
        for (int i = 0; i < n; ++i) {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
        max = new_size;
    }

public:
    // Constructor
    ListArray() : max(MINSIZE), n(0) {
        arr = new T[max];
    }

    // Destructor
    ~ListArray() {
        delete[] arr;
    }

    // Insertar un elemento en una posición
    void insert(int pos, T e) override {
        if (pos < 0 || pos > n) {  // Debe ser pos <= n, no max
            throw std::out_of_range("Posición fuera de rango");
        }

        if (n >= max) {
            resize(max * 2);
        }

        for (int i = n; i > pos; --i) {  // Cambié max por n
            arr[i] = arr[i - 1];
        }

        arr[pos] = e;
        n++;
    }

    // Añadir al final
    void append(T e) override {
        insert(n, e);
    }

    // Añadir al principio
    void prepend(T e) override {
        insert(0, e);
    }

    // Eliminar un elemento
    T remove(int pos) override {
        if (pos < 0 || pos >= n) {  // Cambié max por n
            throw std::out_of_range("Posición fuera de rango");
        }

        T removedValue = arr[pos];
        for (int i = pos; i < n - 1; ++i) {
            arr[i] = arr[i + 1];
        }
        --n;

        if (n < max / 4 && max > MINSIZE) {
            resize(max / 2);
        }

        return removedValue;
    }

    // Obtener un elemento
    T get(int pos) override {
        if (pos < 0 || pos >= n) {
            throw std::out_of_range("Posición fuera de rango");
        }
        return arr[pos];
    }

    // Buscar un elemento
    int search(T e) override {
        for (int i = 0; i < n; ++i) {
            if (arr[i] == e) {
                return i;  // Retornar la posición si se encuentra
            }
        }
        return -1;
    }

    // Verificar si la lista está vacía
    bool empty() override {
        return n == 0;
    }

    // Retornar el tamaño de la lista
    int size() override {
        return n;
    }

    // Sobrecarga del operador []
    T operator[](int pos) {
        if (pos < 0 || pos >= n) {
            throw std::out_of_range("Posición fuera de rango");
        }
        return arr[pos];
    }

    // Sobrecarga del operador <<
    friend std::ostream& operator<<(std::ostream &out, const ListArray<T> &list) {
        out << "[";
        for (int i = 0; i < list.n; ++i) {
            out << list.arr[i];
            if (i < list.n - 1) {
                out << ", ";
            }
        }
        out << "]";
        return out;
    }
};
