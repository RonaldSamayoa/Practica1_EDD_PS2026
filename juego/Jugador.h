//
// Created by ronald on 9/2/26.
//

#ifndef UNO_JUGADOR_H
#define UNO_JUGADOR_H
#include <string>
#include "../estructuras/ListaSimple.h"
#include "../cartas/Carta.h"

class Jugador {
private:
    std::string nombre;            // Nombre del jugador
    ListaSimple<Carta*> mano;      // Lista de cartas que tiene en la mano
public:
    // Constructor
    Jugador(std::string n) : nombre(std::move(n)) {}

    // Devuelve el nombre del jugador
    [[nodiscard]] std::string getNombre() const {
        return nombre;
    }

    // Agrega una carta a la mano (cuando roba)
    void agregarCarta(Carta* carta) {
        mano.insertarFinal(carta);
    }

    // Elimina una carta específica de la mano (cuando juega)
    bool quitarCarta(Carta* carta) {
        return mano.eliminar(carta);
    }

    // Verifica si el jugador ya no tiene cartas
    [[nodiscard]] bool sinCartas() const {
        return mano.estaVacia();
    }

};

#endif //UNO_JUGADOR_H