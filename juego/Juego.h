//
// Created by ronald on 9/2/26.
//

#ifndef UNO_JUEGO_H
#define UNO_JUEGO_H
#include "../estructuras/ListaCircular.h"
#include "../estructuras/Stack.h"
#include "Jugador.h"
#include "Configuracion.h"
#include "../cartas/Carta.h"
#include "Mazo.h"

class Juego {
private:
    ListaCircular<Jugador*> jugadores;  // Lista circular de jugadores
    Mazo mazo; //implementamos las funciones de clase mazo
    Stack<Carta*> descarte; // Mazo de descarte

    [[nodiscard]] int contarJugadores() const;

    Configuracion config;               // Reglas activadas

    Nodo<Jugador*>* jugadorActual;      // Nodo actual en la lista circular
    int direccion;                      // 1 = normal, -1 = reversa

    void remezclarDescarteEnMazo();

    bool partidaTerminada;
    Jugador* ganador;

    Jugador* jugadorPendienteUNO;
    bool unoDeclarado;


public:
    // Constructor
    Juego(const Configuracion& configuracion);

    // Agregar jugadores antes de iniciar
    void agregarJugador(Jugador* jugador);

    // Inicializar partida (crear mazo, repartir, etc.)
    void iniciarPartida();

    void repartirCartasIniciales(int cantidad);

    void colocarPrimeraCarta();

    bool esJugadaValida(Carta* carta);

    bool jugarCarta(Carta* carta);

    void robarCarta();

    // Avanzar turno
    void siguienteTurno();

    // Cambiar dirección
    void cambiarDireccion();

    // Obtener jugador actual
    [[nodiscard]] Jugador* getJugadorActual() const;

    [[nodiscard]] bool estaTerminada() const;
    [[nodiscard]] Jugador* getGanador() const;

    void declararUNO();
    void reportarUNO();

};

#endif //UNO_JUEGO_H