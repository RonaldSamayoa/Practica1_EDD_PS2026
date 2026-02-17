//
// Created by ronald on 9/2/26.
//

#include "Jugador.h"

int Jugador::cantidadCartas() const {

    int contador = 0;

    Nodo<Carta*>* temp = mano.getCabeza();

    while (temp != nullptr) {
        contador++;
        temp = temp->siguiente;
    }

    return contador;
}

bool Jugador::tieneColor(Color color) const {

    Nodo<Carta*>* temp = mano.getCabeza();

    while (temp != nullptr) {

        if (temp->dato->getColor() == color)
            return true;

        temp = temp->siguiente;
    }

    return false;
}

