#include <iostream>
#include "ListaDobleCircular.h"

using namespace std;

int main() {
    ListaDobleCircular<int> lista;

    // Pruebas de insercion
    lista.insertarAlFinal(20);
    lista.insertarAlFinal(30);
    lista.insertarAlFinal(40);
    lista.insertarAlInicio(10);

    cout << "ESTADO INICIAL" << endl;
    lista.imprimir();
    cout << "Tamanio: " << lista.getTamanio() << endl;

    cout << "\nOBTENER EN POSICION (la cabeza es la posicion 0)" << endl;
    for (int i = 0; i < lista.getTamanio(); i++)
        cout << "Posicion " << i << ": " << lista.obtenerEnPosicion(i) << endl;

    try
    {
        int valor = lista.obtenerEnPosicion(10);
        cout << "Posicion 10: " << valor << endl;
    }
    catch (const out_of_range& e)
    {
        cout << "Error: " << e.what() << endl;
    }

    cout << "\nBUSCANDO EL 30" << endl;
    Nodo<int>* encontrado = lista.buscar(30);
    if (encontrado != nullptr)
        cout << "Elemento " << encontrado->getDato() << " encontrado." << endl;
    else
        cout << "Elemento no encontrado." << endl;

    cout << "\nELIMINANDO UN VALOR EN MEDIO (20)" << endl;
    lista.eliminar(20);
    lista.imprimir();

    cout << "\nELIMINANDO LA CABEZA (10)" << endl;
    lista.eliminar(10);
    lista.imprimir();

    cout << "\nELIMINANDO UN VALOR QUE NO EXISTE (99)" << endl;
    lista.eliminar(99);

    cout << "\nPRUEBA CON OTRO TIPO (string)" << endl;
    ListaDobleCircular<string> nombres;
    nombres.insertarAlFinal("Ana");
    nombres.insertarAlInicio("Luis");
    nombres.imprimir();
    cout << "Posicion 1: " << nombres.obtenerEnPosicion(1) << endl;

    cout << "\nOBTENER EN POSICION EN LISTA VACIA" << endl;
    ListaDobleCircular<int> vacia;
    try
    {
        cout << vacia.obtenerEnPosicion(0) << endl;
    }
    catch (const out_of_range& e)
    {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
