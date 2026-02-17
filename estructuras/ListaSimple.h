//
// Created by ronald on 9/2/26.
//
#ifndef UNO_LISTASIMPLE_H
#define UNO_LISTASIMPLE_H

#include <iostream>
#include "Nodo.h"

// Lista enlazada simple genérica. Se usará para:
// Mano de los jugadores
// Bolsa temporal del mazo

template <typename T>

class ListaSimple {
    private:
    Nodo<T>* cabeza;  // Primer nodo de la lista

public:
    // Constructor: inicia la lista vacía
    ListaSimple() {
        cabeza = nullptr;
    }

    // Inserta un nuevo nodo al final de la lista
    void insertarFinal(T dato) {
        auto* nuevo = new Nodo<T>(dato);

        // Si la lista está vacía, el nuevo nodo es la cabeza
        if (cabeza == nullptr) {
            cabeza = nuevo;
            return;
        }

        // Recorremos hasta el último nodo
        Nodo<T>* temp = cabeza;
        while (temp->siguiente != nullptr) {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevo; // Enlazamos el último nodo con el nuevo
    }

    // Elimina el primer nodo que contenga el dato indicado
    bool eliminar(T dato) {
        if (cabeza == nullptr) return false;

        // Caso especial: el dato está en la cabeza
        if (cabeza->dato == dato) {
            Nodo<T>* eliminar = cabeza;
            cabeza = cabeza->siguiente;
            delete eliminar;
            return true;
        }

        // Buscar el nodo anterior al que queremos eliminar
        Nodo<T>* actual = cabeza;
        while (actual->siguiente != nullptr && actual->siguiente->dato != dato) {
            actual = actual->siguiente;
        }
        // Si no se encontró el dato
        if (actual->siguiente == nullptr) return false;

        Nodo<T>* eliminar = actual->siguiente;
        actual->siguiente = eliminar->siguiente;
        delete eliminar;
        return true;
    }

    // Busca si un dato existe en la lista
    bool buscar(T dato) const {
        Nodo<T>* temp = cabeza;
        while (temp != nullptr) {
            if (temp->dato == dato)
                return true;
            temp = temp->siguiente;
        }
        return false;
    }

    // Retorna true si la lista no tiene nodos
    [[nodiscard]] bool estaVacia() const  {
        return cabeza == nullptr;
    }
    //para pruebas
    void mostrar() const {
        Nodo<T>* temp = cabeza;
        while (temp != nullptr) {
            std::cout << temp->dato << " -> ";
            temp = temp->siguiente;
        }
        std::cout << "NULL\n";
    }

    // Devuelve el dato del primer nodo sin eliminarlo
    T obtenerPrimero() const {
        if (cabeza == nullptr) throw std::runtime_error("Lista vacía");
        return cabeza->dato;
    }

    // Extrae y devuelve el primer nodo (lo elimina de la lista)
    T extraerPrimero() {
        if (cabeza == nullptr) throw std::runtime_error("Lista vacía");

        Nodo<T>* temp = cabeza;
        T dato = temp->dato;
        cabeza = cabeza->siguiente;
        delete temp;
        return dato;
    }

    Nodo<T>* getCabeza() const {
        return cabeza;
    }

    // Destructor: libera toda la memoria de la lista
    ~ListaSimple() {
        while (cabeza != nullptr) {
            Nodo<T>* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
    }
};


#endif //UNO_LISTASIMPLE_H