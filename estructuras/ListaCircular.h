//
// Created by ronald on 9/2/26.
//
#ifndef UNO_LISTACIRCULAR_H
#define UNO_LISTACIRCULAR_H

#include "Nodo.h"
// Lista enlazada circular simple. Se usará para:
// Almacenar jugadores
// Manejar turnos de forma continua
// Soportar cambios de dirección (Reverse)

template <typename T>
class ListaCircular {
private:
    Nodo<T>* cabeza;   // Primer nodo
    Nodo<T>* cola;     // Último nodo (apunta de nuevo a cabeza)

public:
    // Constructor: inicia vacía
    ListaCircular() {
        cabeza = nullptr;
        cola = nullptr;
    }

    // Inserta un elemento al final de la lista circular
    void insertar(T dato) {
        auto* nuevo = new Nodo<T>(dato);

        // Si está vacía, cabeza y cola apuntan al nuevo nodo
        if (cabeza == nullptr) {
            cabeza = nuevo;
            cola = nuevo;
            cola->siguiente = cabeza; // Se hace circular
            return;
        }

        // Insertar al final y mantener circularidad
        cola->siguiente = nuevo;
        cola = nuevo;
        cola->siguiente = cabeza;
    }

    // Devuelve la cabeza (inicio de la lista)
    Nodo<T>* getCabeza() {
        return cabeza;
    }

    // Verifica si la lista está vacía
    bool estaVacia() {
        return cabeza == nullptr;
    }

    // Busca el nodo anterior al nodo actual
    // Se usa para retroceder cuando la dirección es -1 (carta reverse)
    Nodo<T>* buscarAnterior(Nodo<T>* actual) {
        if (cabeza == nullptr || actual == nullptr)
            return nullptr;

        Nodo<T>* temp = cabeza;

        // Recorremos hasta que el siguiente sea el nodo actual
        do {
            if (temp->siguiente == actual)
                return temp;
            temp = temp->siguiente;
        } while (temp != cabeza);

        return nullptr; // No encontrado
    }

    // Destructor: libera memoria
    ~ListaCircular() {
        if (cabeza == nullptr) return;

        Nodo<T>* actual = cabeza->siguiente;
        while (actual != cabeza) {
            auto* temp = actual;
            actual = actual->siguiente;
            delete temp;
        }

        delete cabeza;
    }
};

#endif //UNO_LISTACIRCULAR_H