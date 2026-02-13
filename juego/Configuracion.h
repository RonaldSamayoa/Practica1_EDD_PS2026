//
// Created by ronald on 9/2/26.
//

#ifndef UNO_CONFIGURACION_H
#define UNO_CONFIGURACION_H

// Contiene las reglas activadas para una partida
class Configuracion {
private:
    bool stacking;           // Permite acumular +2 y +4
    bool retoMas4;           // Permite retar un +4
    bool robarHastaPoder;    // Robar hasta poder jugar
    bool reglaUNO;           // Obligatorio decir UNO
    bool ganarConNegra;      // Permite ganar con comodín
    bool modoFlip;           // Activa UNO Flip

public:
    // Constructor por defecto (todas desactivadas)
    Configuracion()
        : stacking(false),
          retoMas4(false),
          robarHastaPoder(false),
          reglaUNO(false),
          ganarConNegra(false),
          modoFlip(false) {}

    // Getters
    [[nodiscard]] bool isStacking() const { return stacking; }
    [[nodiscard]] bool isRetoMas4() const { return retoMas4; }
    [[nodiscard]] bool isRobarHastaPoder() const { return robarHastaPoder; }
    [[nodiscard]] bool isReglaUNO() const { return reglaUNO; }
    [[nodiscard]] bool isGanarConNegra() const { return ganarConNegra; }
    [[nodiscard]] bool isModoFlip() const { return modoFlip; }

    // Setters
    void setStacking(bool v) { stacking = v; }
    void setRetoMas4(bool v) { retoMas4 = v; }
    void setRobarHastaPoder(bool v) { robarHastaPoder = v; }
    void setReglaUNO(bool v) { reglaUNO = v; }
    void setGanarConNegra(bool v) { ganarConNegra = v; }
    void setModoFlip(bool v) { modoFlip = v; }
};


#endif //UNO_CONFIGURACION_H