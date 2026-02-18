//
// Created by ronald on 17/2/26.
//

#ifndef UNO_GESTORCARTAS_H
#define UNO_GESTORCARTAS_H

#include "Mazo.h"
#include "../estructuras/Stack.h"
#include "../estructuras/ListaCircular.h"
#include "Jugador.h"
class GestorCartas {
private:
    Mazo mazo;
    Stack<Carta*> descarte;

    // Mezcla el descarte (excepto la carta superior) dentro del mazo
    void remezclarDescarte();

public:
    GestorCartas() = default;

    // Inicializa el sistema de cartas para una nueva partida
    void inicializar(int cantidadJugadores, const Configuracion& config);

    // Reparte cartas iniciales a todos los jugadores
    void repartirInicial(ListaCircular<Jugador*>& jugadores, int cantidad);

    // Coloca la primera carta válida en el descarte
    void colocarPrimeraCarta();

    // Roba una carta del mazo (remezcla si es necesario)
    Carta* robarCarta();

    // Coloca una carta en el descarte
    void descartar(Carta* carta);

    // Devuelve la carta superior del descarte
    Carta* cartaSuperior();

    // Indica si el mazo está vacío
    [[nodiscard]] bool mazoVacio() const;

    // Fuerza remezcla del descarte en el mazo
    void forzarRemezcla();

};

#endif //UNO_GESTORCARTAS_H