//
// Created by ronald on 9/2/26.
//

#ifndef UNO_CARTAACCION_H
#define UNO_CARTAACCION_H
#include "Carta.h"
#include "CartaNumero.h"
#include <string>
#include <iostream>

class CartaAccion : public Carta {
public:
    // Constructor recibe color y tipo específico de acción
    CartaAccion(Color c, TipoCarta t)
        : Carta(c, t) {}

    void mostrar() const {
        std::cout << "[Accion] Color: " << CartaNumero::colorToString(color)
                  << " Tipo: " << tipoToString(tipo) << std::endl;
    }

    [[nodiscard]] static std::string tipoToString(TipoCarta t) {
        switch (t) {
            case SKIP: return "Skip";
            case REVERSE: return "Reverse";
            case DRAW: return "Draw";
            case FLIP: return "Flip";
            case PERSONALIZADA: return "Personalizada";
            default: return "Accion Desconocida";
        }
    }
};


#endif //UNO_CARTAACCION_H