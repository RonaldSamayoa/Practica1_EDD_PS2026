//
// Created by ronald on 16/2/26.
//

#include "Mazo.h"
#include "../cartas/CartaNumero.h"
#include "../cartas/CartaAccion.h"
#include "../cartas/CartaComodin.h"

void Mazo::construir(int cantidadJugadores, const Configuracion& config) {

    ListaSimple<Carta*> bolsa;

    Color colores[] = { ROJO, AMARILLO, VERDE, AZUL };

    int cantidadMazos = ((cantidadJugadores - 1) / 6) + 1;

    for (int m = 0; m < cantidadMazos; m++) {

        for (Color color : colores) {

            bolsa.insertarFinal(new CartaNumero(color, 0));

            for (int i = 1; i <= 9; i++) {
                bolsa.insertarFinal(new CartaNumero(color, i));
                bolsa.insertarFinal(new CartaNumero(color, i));
            }

            bolsa.insertarFinal(new CartaAccion(color, SKIP));
            bolsa.insertarFinal(new CartaAccion(color, SKIP));

            bolsa.insertarFinal(new CartaAccion(color, REVERSE));
            bolsa.insertarFinal(new CartaAccion(color, REVERSE));

            bolsa.insertarFinal(new CartaAccion(color, DRAW));
            bolsa.insertarFinal(new CartaAccion(color, DRAW));

            if (config.isModoFlip()) {
                bolsa.insertarFinal(new CartaAccion(color, FLIP));
                bolsa.insertarFinal(new CartaAccion(color, FLIP));
            }
        }

        for (int i = 0; i < 4; i++) {
            bolsa.insertarFinal(new CartaComodin(0));
            bolsa.insertarFinal(new CartaComodin(4));
        }
    }

    barajarLista(bolsa);

    while (!bolsa.estaVacia()) {
        pila.push(bolsa.extraerPrimero());
    }
}

Carta* Mazo::robar() {
    if (pila.estaVacia())
        return nullptr;

    return pila.pop();
}

bool Mazo::estaVacio() const {
    return pila.estaVacia();
}

void Mazo::apilar(Carta* carta) {
    pila.push(carta);
}

int Mazo::contarElementos(ListaSimple<Carta*>& lista) {

    int contador = 0;
    ListaSimple<Carta*> temp;

    // Contamos moviendo elementos temporalmente
    while (!lista.estaVacia()) {
        temp.insertarFinal(lista.extraerPrimero());
        contador++;
    }

    // Restauramos la lista original
    while (!temp.estaVacia()) {
        lista.insertarFinal(temp.extraerPrimero());
    }

    return contador;
}

void Mazo::barajarLista(ListaSimple<Carta*>& lista) {
    // Se obtiene la cantidad total de elementos en la lista
    int n = contarElementos(lista);
    // Si la lista tiene 0 o 1 elemento, no es necesario barajar
    if (n <= 1)
        return;

    // Se recorre la lista completa realizando reordenamientos progresivos
    for (int i = 0; i < n; i++) {
        // Se extrae el primer elemento de la lista original. Esta carta será reinsertada en una nueva posición calculada
        Carta* primera = lista.extraerPrimero();

        // Se calcula una posición de inserción basada en la iteración actual
        // La fórmula permite variar la posición sin utilizar números aleatorios
        int saltos = (i * 3 + 1) % n;

        // Se crea una lista temporal auxiliar para reconstruir el orden
        ListaSimple<Carta*> temp;

        // Se trasladan los primeros saltos de elementos de la lista original hacia la lista temporal, preservando su orden relativo
        for (int j = 0; j < saltos && !lista.estaVacia(); j++) {
            temp.insertarFinal(lista.extraerPrimero());
        }

        // Se inserta la carta extraída inicialmente en la nueva posición calculada
        temp.insertarFinal(primera);

        // Se trasladan los elementos restantes de la lista original hacia la lista temporal
        while (!lista.estaVacia()) {
            temp.insertarFinal(lista.extraerPrimero());
        }

        // Finalmente, se reconstruye la lista original utilizando el nuevo orden generado en la lista temporal
        while (!temp.estaVacia()) {
            lista.insertarFinal(temp.extraerPrimero());
        }
    }
}
