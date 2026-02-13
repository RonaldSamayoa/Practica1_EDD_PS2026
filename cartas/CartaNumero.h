//
// Created by ronald on 9/2/26.
//

#ifndef UNO_CARTANUMERO_H
#define UNO_CARTANUMERO_H

#include "Carta.h"
#include <string>
#include <stdexcept>
#include <iostream>

class CartaNumero : public Carta{
private:
    int valor;  // Número de la carta

public:
    // Constructor: recibe color y número
    CartaNumero(Color c, int v)
        : Carta(c, NUMERO) {
        if (v < 0 || v > 9)
            throw std::invalid_argument("Valor de carta fuera de rango (0-9)");

        valor = v;
    }

    // Getter del valor
    [[nodiscard]] int getValor() const {
        return valor;
    }

    void mostrar() const {
        std::cout << "[Numero] Color: " << colorToString(color)
                  << " Valor: " << valor << std::endl;
    }

    // Funcion auxiliar para convertir color a texto
    [[nodiscard]] static std:: string colorToString(Color c) {
        switch (c) {
            case ROJO: return "Rojo";
            case VERDE: return "Verde";
            case AZUL: return "Azul";
            case AMARILLO: return "Amarillo";
            case ROSA: return "Rosa";
            case TURQUESA: return "Turquesa";
            case NARANJA: return "Naranja";
            case VIOLETA: return "Violeta";
            case NEGRO: return "Negro";
            default: return "Desconocido";
        }
    }
};


#endif //UNO_CARTANUMERO_H