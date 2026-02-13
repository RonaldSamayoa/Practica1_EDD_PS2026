cmake_minimum_required(VERSION 4.1)
project(UNO)

set(CMAKE_CXX_STANDARD 20)

add_executable(UNO main.cpp
        estructuras/Nodo.h
        estructuras/ListaSimple.h
        estructuras/ListaCircular.h
        estructuras/Stack.h
        cartas/Carta.cpp
        cartas/Carta.h
        cartas/CartaNumero.cpp
        cartas/CartaNumero.h
        cartas/CartaAccion.cpp
        cartas/CartaAccion.h
        cartas/CartaComodin.cpp
        cartas/CartaComodin.h
        juego/Jugador.cpp
        juego/Jugador.h
        juego/Configuracion.cpp
        juego/Configuracion.h
        juego/Juego.cpp
        juego/Juego.h
        util/Colores.h
        util/TiposCarta.h)
