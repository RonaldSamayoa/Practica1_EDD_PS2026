//
// Created by ronald on 16/2/26.
//

#include "Mazo.h"
#include "../cartas/CartaNumero.h"
#include "../cartas/CartaAccion.h"
#include "../cartas/CartaComodin.h"
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

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

    std::vector<Carta*> temp;

    // Extrae todas las cartas de la lista original y las guarda en un vector temporal
    while (!lista.estaVacia()) {
        temp.push_back(lista.extraerPrimero());
    }

    int n = temp.size();

    // Algoritmo Fisher-Yates para mezclar el vector
    // Recorre desde el último elemento hasta el segundo
    for (int i = n - 1; i > 0; i--) {

        // Genera una posición aleatoria entre 0 e i
        int j = rand() % (i + 1);

        // Intercambia la carta actual con otra posición aleatoria
        std::swap(temp[i], temp[j]);
    }

    // Inserta nuevamente las cartas ya mezcladas en la lista original
    for (int i = 0; i < n; i++) {
        lista.insertarFinal(temp[i]);
    }
}
