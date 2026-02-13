//
// Created by ronald on 9/2/26.
//

#ifndef UNO_STACK_H
#define UNO_STACK_H
#include <stdexcept>
#include "Nodo.h"
// Implementación de una Pila (Stack) usando nodos. Se usará para:
// Mazo principal
// Mazo de descarte

template <typename T>
class Stack {
private:
    Nodo<T>* tope; // Nodo que está arriba de la pila

public:
    Stack() {
        tope = nullptr;
    }

    void push(T dato) {
        auto* nuevo = new Nodo<T>(dato);
        nuevo->siguiente = tope; // El nuevo apunta al antiguo tope
        tope = nuevo; // Ahora el nuevo es el tope
    }
    // Elimina y devuelve el elemento de la cima
    T pop() {
        if (tope == nullptr)
            throw std::runtime_error("Stack vacío");

        Nodo<T>* temp = tope;
        T dato = temp->dato;
        tope = tope->siguiente;
        delete temp;
        return dato;
    }
    // Devuelve el elemento de la cima sin eliminarlo
    T peek() {
        if (tope == nullptr)
            throw std::runtime_error("Stack vacío");

        return tope->dato;
    }
    // Verifica si la pila está vacía
    bool estaVacia() {
        return tope == nullptr;
    }
    // Destructor: libera memoria de la pila
    ~Stack() {
        while (tope != nullptr) {
            Nodo<T>* temp = tope;
            tope = tope->siguiente;
            delete temp;
        }
    }
};


#endif //UNO_STACK_H