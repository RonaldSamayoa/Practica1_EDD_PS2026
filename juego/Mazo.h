//
// Created by ronald on 16/2/26.
//

#ifndef UNO_MAZO_H
#define UNO_MAZO_H

#include "../estructuras/Stack.h"
#include "../estructuras/ListaSimple.h"
#include "../cartas/Carta.h"
#include "Configuracion.h"

class Mazo {
private:
    Stack<Carta*> pila;

    static void barajarLista(ListaSimple<Carta*>& lista);
    static int contarElementos(ListaSimple<Carta*>& lista);

public:
    Mazo() = default;

    void construir(int cantidadJugadores, const Configuracion& config);

    Carta* robar();

    [[nodiscard]] bool estaVacio() const;

    void apilar(Carta* carta);

};
#endif //UNO_MAZO_H