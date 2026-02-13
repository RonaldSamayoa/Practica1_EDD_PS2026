#include <iostream>
#include "estructuras/ListaSimple.h"
#include "estructuras/Stack.h"
// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main() {
    ListaSimple<int> lista;
    lista.insertarFinal(10);
    lista.insertarFinal(20);
    lista.insertarFinal(30);
    lista.mostrar();

    lista.eliminar(20);
    lista.mostrar();

    Stack<int> pila;
    pila.push(5);
    pila.push(15);
    pila.push(25);

    std::cout << "Tope: " << pila.peek() << std::endl;
    std::cout << "Pop: " << pila.pop() << std::endl;
    std::cout << "Nuevo tope: " << pila.peek() << std::endl;

    return 0;
}