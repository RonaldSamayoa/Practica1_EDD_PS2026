#include <iostream>
#include "estructuras/ListaSimple.h"
#include "estructuras/Stack.h"
#include <QApplication>
#include "juego/Juego.h"
#include "juego/Configuracion.h"
#include <ctime>

void mostrarMano(Jugador* jugador) {
    Nodo<Carta*>* temp = jugador->getMano().getCabeza();
    int i = 0;

    while (temp != nullptr) {
        std::cout << i << ") ";
        temp->dato->mostrar();
        temp = temp->siguiente;
        i++;
    }
}

Carta* obtenerCartaPorIndice(Jugador* jugador, int indice) {
    Nodo<Carta*>* temp = jugador->getMano().getCabeza();
    int i = 0;

    while (temp != nullptr) {
        if (i == indice)
            return temp->dato;

        temp = temp->siguiente;
        i++;
    }
    return nullptr;
}

void mostrarMenu() {
    std::cout << "\nOpciones:\n";
    std::cout << "1) Jugar carta\n";
    std::cout << "2) Robar carta\n";
    std::cout << "3) Declarar UNO\n";
    std::cout << "4) Reportar UNO\n";
    std::cout << "5) Salir partida\n";
    std::cout << "Seleccione opcion: ";
}

int main() {
    srand(time(nullptr));

    Configuracion config;
    Juego juego(config);

    int numJugadores;
    std::cout << "Numero de jugadores: ";
    std::cin >> numJugadores;

    for (int i = 0; i < numJugadores; i++) {
        std::string nombre;
        std::cout << "Nombre jugador " << i + 1 << ": ";
        std::cin >> nombre;
        juego.agregarJugador(new Jugador(nombre));
    }

    // Agregar castigos personalizados
    int cantidadMazos = ((numJugadores - 1) / 6) + 1;
    int cantidadCartasPersonalizadas = cantidadMazos * 2;

    std::cout << "\nDebes ingresar " << cantidadCartasPersonalizadas<< " castigos personalizados.\n";

    for (int i = 0; i < cantidadCartasPersonalizadas; i++) {
        std::string castigo;
        std::cout << "Castigo " << i + 1 << ": ";
        std::cin.ignore();
        std::getline(std::cin, castigo);
        juego.agregarCastigo(castigo);
    }

    juego.iniciarPartida();

    while (!juego.estaTerminada()) {

        Jugador* actual = juego.getJugadorActual();

        std::cout << "\n==============================\n";
        std::cout << "Turno de: " << actual->getNombre() << "\n";
        std::cout << "Carta superior:\n";
        juego.getCartaSuperior()->mostrar();

        std::cout << "\nTus cartas:\n";
        mostrarMano(actual);

        // Si se jugó comodín y se espera color
        if (juego.estaEsperandoColor()) {
            int c;
            std::cout << "\nElige color (0=ROJO,1=VERDE,2=AZUL,3=AMARILLO): ";
            std::cin >> c;
            juego.elegirColor(static_cast<Color>(c));
            continue;
        }

        mostrarMenu();

        int opcion;
        std::cin >> opcion;

        switch (opcion) {

            case 1: {
                std::cout << "Indice de carta: ";
                int indice;
                std::cin >> indice;

                Carta* carta = obtenerCartaPorIndice(actual, indice);
                if (!carta || !juego.jugarCarta(carta)) {
                    std::cout << "Jugada invalida.\n";
                }
                break;
            }

            case 2:
                juego.robarCarta();
                break;

            case 3:
                juego.declararUNO();
                std::cout << "UNO declarado.\n";
                break;

            case 4:
                juego.reportarUNO();
                std::cout << "Reporte realizado.\n";
                break;

            case 5:
                std::cout << "Partida finalizada manualmente.\n";
                return 0;

            default:
                std::cout << "Opcion invalida.\n";
        }
    }

    std::cout << "\n==============================\n";
    std::cout << "Ganador: "
              << juego.getGanador()->getNombre()
              << "\n";

    return 0;
}