#include <iostream>
#include "estructuras/ListaSimple.h"
#include "estructuras/Stack.h"
#include <QApplication>
#include <QLabel>
#include "juego/Juego.h"
#include "cartas/CartaNumero.h"
#include "cartas/CartaAccion.h"
#include "juego/Configuracion.h"
#include <ctime>
#include <cstdlib>

int main() {
    srand(time(nullptr));

    Configuracion config;
    config.setStacking(false);

    Juego juego(config);

    Jugador* A = new Jugador("A");
    Jugador* B = new Jugador("B");

    juego.agregarJugador(A);
    juego.agregarJugador(B);

    std::cout << "Antes de iniciar partida \n ";
    juego.iniciarPartida();
    std::cout << "Despues de iniciar partida \n ";

    // Crear cartas manualmente
    Carta* masDos = new CartaAccion(ROJO, DRAW);
    Carta* cincoAzul = new CartaNumero(AZUL, 5);

    A->agregarCarta(masDos);
    B->agregarCarta(cincoAzul);

    std::cout << "Turno inicial: "
              << juego.getJugadorActual()->getNombre()
              << "\n";

    juego.jugarCarta(masDos);

    std::cout << "Cartas de B después del +2: "
              << B->cantidadCartas()
              << "\n";

    std::cout << "Turno actual ahora: "
              << juego.getJugadorActual()->getNombre()
              << "\n";

    return 0;
}