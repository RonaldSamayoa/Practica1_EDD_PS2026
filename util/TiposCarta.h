//
// Created by ronald on 9/2/26.
//

#ifndef UNO_TIPOSCARTA_H
#define UNO_TIPOSCARTA_H

// Tipos de cartas que existen en el juego
enum TipoCarta {
        NUMERO,        // Cartas 0–9
        SKIP,          // Salta turno
        REVERSE,       // Cambia dirección
        DRAW,          // Robar cartas (+1, +2, +3, etc.)
        COMODIN,       // Cambio de color
        FLIP,          // Activa lado oscuro
        PERSONALIZADA  // Cartas inventadas por el grupo
};


#endif //UNO_TIPOSCARTA_H