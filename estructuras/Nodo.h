//
// Created by ronald on 9/2/26.
//

#ifndef UNO_NODO_H
#define UNO_NODO_H

template <typename T>
class Nodo {
public:
    T dato; // Información que guarda el nodo
    Nodo<T>* siguiente; // Apunta al siguiente nodo en la estructura

    // Constructor: inicializa el nodo con un dato
    Nodo(T d) {
        dato = d;
        siguiente = nullptr; // No apunta a nadie al crearse
    }
};
#endif //UNO_NODO_H