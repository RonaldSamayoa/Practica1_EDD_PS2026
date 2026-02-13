//
// Created by ronald on 9/2/26.
//

#ifndef UNO_CARTACOMODIN_H
#define UNO_CARTACOMODIN_H
#include "Carta.h"
#include "CartaNumero.h"

// Carta comodín (cambio de color, con o sin robo)
class CartaComodin : public Carta  {
private:
    int cantidadRobo;
public:
    // Constructor: recibe cuántas cartas obliga a robar
    CartaComodin(int robo)
        : Carta(NEGRO, COMODIN), cantidadRobo(robo) {}

    // Devuelve cuántas cartas hace robar
    [[nodiscard]] int getCantidadRobo() const {
        return cantidadRobo;
    }

    void mostrar() const {
        std::cout << "[Comodin] Cambio de color";

        if (cantidadRobo > 0)
            std::cout << " + Robo " << cantidadRobo;

        std::cout << std::endl;
    }
};

#endif //UNO_CARTACOMODIN_H