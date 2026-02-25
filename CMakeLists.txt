cmake_minimum_required(VERSION 4.1)
project(UNO)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(UNO main.cpp
        juego/Jugador.cpp
        juego/Juego.cpp
        juego/Mazo.cpp
        juego/MotorReglas.cpp
        juego/GestorCartas.cpp
        juego/ControlUNO.cpp
)
