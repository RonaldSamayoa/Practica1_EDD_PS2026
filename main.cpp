#include <iostream>
#include "estructuras/ListaSimple.h"
#include "estructuras/Stack.h"
#include "juego/Juego.h"
#include "juego/Configuracion.h"
#include <ctime>
#include <limits>

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

void configurarReglas(Configuracion& config) {
    char opcion;

    std::cout << "\n=== CONFIGURACION ===\n";

    std::cout << "Activar stacking? (s/n): ";
    std::cin >> opcion;
    config.setStacking(opcion == 's' || opcion == 'S');

    std::cout << "Obligatorio declarar UNO? (s/n): ";
    std::cin >> opcion;
    config.setReglaUNO(opcion == 's' || opcion == 'S');

    std::cout << "Permitir ganar con negra? (s/n): ";
    std::cin >> opcion;
    config.setGanarConNegra(opcion == 's' || opcion == 'S');
}

int main() {
    srand(time(nullptr));

    Configuracion config;
    configurarReglas(config);
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

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for (int i = 0; i < cantidadCartasPersonalizadas; i++) {
        std::string castigo;
        std::cout << "Castigo " << i + 1 << ": ";
        std::getline(std::cin, castigo);
        juego.agregarCastigo(castigo);
    }

    juego.iniciarPartida();

    while (!juego.estaTerminada()) {
        // Si se jugó comodín y se espera color
        if (juego.estaEsperandoColor()) {

            Jugador* actual = juego.getJugadorActual();
            juego.limpiarEstadoUNO();
            std::cout << "\n=== COMODIN ACTIVADO ===\n";
            std::cout << actual->getNombre() << " debe elegir el nuevo color.\n";

            std::cout << "0) ROJO\n";
            std::cout << "1) VERDE\n";
            std::cout << "2) AZUL\n";
            std::cout << "3) AMARILLO\n";

            int c;
            std::cout << "Seleccione color: ";
            std::cin >> c;

            juego.elegirColor(static_cast<Color>(c));

            std::cout << "Color elegido correctamente.\n\n";

            continue;
        }

        //turno normal
        Jugador* actual = juego.getJugadorActual();

        std::cout << "\n==============================\n";
        std::cout << "Turno de: " << actual->getNombre() << "\n";
        std::cout << "Carta superior:\n";
        juego.getCartaSuperior()->mostrar();

        if (juego.getRoboAcumulado() > 0) {
            std::cout << "Hay "<< juego.getRoboAcumulado()<< " cartas acumuladas.\n";
        }

        if (juego.getCartaSuperior()->esNegra()) {
            std::cout << "Color activo actual: ";

            switch (juego.getColorActivo()) {
                case ROJO: std::cout << "ROJO\n"; break;
                case VERDE: std::cout << "VERDE\n"; break;
                case AZUL: std::cout << "AZUL\n"; break;
                case AMARILLO: std::cout << "AMARILLO\n"; break;
                default: break;
            }
        }

        std::cout << "\nTus cartas:\n";
        mostrarMano(actual);

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
                break;

            case 4:
                juego.reportarUNO();
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