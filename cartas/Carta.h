//
// Created by ronald on 9/2/26.
//

#ifndef UNO_CARTA_H
#define UNO_CARTA_H

#include "../util/Colores.h"
#include "../util/TiposCarta.h"

// Clase base abstracta para todas las cartas
class Carta {
protected:
    Color color;          // Color de la carta
    TipoCarta tipo;       // Tipo de carta (número, acción, etc.)

public:
    // Constructor
    Carta(Color c, TipoCarta t) {
        color = c;
        tipo = t;
    }

    // Métodos getters
    Color getColor() {
        return color;
    }

    TipoCarta getTipo() {
        return tipo;
    }

    //Metodo virtual para mostrar la carta
    virtual void mostrar() = 0;

    virtual ~Carta() = default;
};

#endif //UNO_CARTA_H