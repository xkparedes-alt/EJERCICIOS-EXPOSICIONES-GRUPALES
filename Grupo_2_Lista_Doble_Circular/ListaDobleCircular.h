#ifndef LISTADOBLECIRCULAR_H
#define LISTADOBLECIRCULAR_H

#include <iostream>
#include <stdexcept>
#include "Nodo.h"

using namespace std;

template <typename T>
class ListaDobleCircular
{
public:
    ListaDobleCircular();
    ~ListaDobleCircular();

    bool estaVacia();
    int getTamanio();

    void insertarAlInicio(T valor);
    void insertarAlFinal(T valor);
    Nodo<T>* buscar(T dato);
    void eliminar(T dato);
    void imprimir();
    T obtenerEnPosicion(int pos);

private:
    Nodo<T>* cabeza;
    int tamanio;
};

template <typename T>
ListaDobleCircular<T>::ListaDobleCircular()
{
    cabeza = nullptr;
    tamanio = 0;
}

template <typename T>
ListaDobleCircular<T>::~ListaDobleCircular()
{
    while (!estaVacia())
    {
        eliminar(cabeza->getDato());
    }
}

template <typename T>
bool ListaDobleCircular<T>::estaVacia()
{
    return cabeza == nullptr;
}

template <typename T>
int ListaDobleCircular<T>::getTamanio()
{
    return tamanio;
}

template <typename T>
void ListaDobleCircular<T>::insertarAlFinal(T valor)
{
    Nodo<T>* nuevo = new Nodo<T>(valor);

    if (estaVacia())
    {
        nuevo->setSiguiente(nuevo);
        nuevo->setAnterior(nuevo);
        cabeza = nuevo;
    }
    else
    {
        Nodo<T>* ultimo = cabeza->getAnterior();

        nuevo->setSiguiente(cabeza);
        nuevo->setAnterior(ultimo);
        ultimo->setSiguiente(nuevo);
        cabeza->setAnterior(nuevo);
    }
    tamanio++;
}

template <typename T>
void ListaDobleCircular<T>::insertarAlInicio(T valor)
{
    Nodo<T>* nuevo = new Nodo<T>(valor);

    if (estaVacia())
    {
        nuevo->setSiguiente(nuevo);
        nuevo->setAnterior(nuevo);
    }
    else
    {
        Nodo<T>* ultimo = cabeza->getAnterior();

        nuevo->setSiguiente(cabeza);
        nuevo->setAnterior(ultimo);
        ultimo->setSiguiente(nuevo);
        cabeza->setAnterior(nuevo);
    }
    cabeza = nuevo;   // el nuevo nodo pasa a ser la cabeza
    tamanio++;
}

template <typename T>
Nodo<T>* ListaDobleCircular<T>::buscar(T dato)
{
    if (estaVacia())
    {
        return nullptr;
    }

    Nodo<T>* actual = cabeza;

    do
    {
        if (actual->getDato() == dato)
        {
            return actual;
        }
        actual = actual->getSiguiente();
    } while (actual != cabeza);

    return nullptr;
}

template <typename T>
void ListaDobleCircular<T>::eliminar(T dato)
{
    if (estaVacia())
    {
        cout << "La lista esta vacia" << endl;
        return;
    }

    Nodo<T>* actual = cabeza;

    do
    {
        if (actual->getDato() == dato)
        {
            // Caso 1: solo existe un nodo
            if (actual->getSiguiente() == actual)
            {
                cabeza = nullptr;
            }
            else
            {
                // Enlazar el anterior con el siguiente
                actual->getAnterior()->setSiguiente(actual->getSiguiente());
                actual->getSiguiente()->setAnterior(actual->getAnterior());

                // Si se elimina la cabeza
                if (actual == cabeza)
                {
                    cabeza = actual->getSiguiente();
                }
            }

            delete actual;
            tamanio--;
            cout << "Elemento eliminado" << endl;
            return;
        }

        actual = actual->getSiguiente();

    } while (actual != cabeza);

    cout << "Elemento no encontrado" << endl;
}

template <typename T>
void ListaDobleCircular<T>::imprimir()
{
    if (estaVacia())
    {
        cout << "Lista vacia" << endl;
        return;
    }

    Nodo<T>* actual = cabeza;

    do
    {
        cout << actual->getDato() << " ";
        actual = actual->getSiguiente();
    } while (actual != cabeza);

    cout << endl;
}

// Devuelve el dato almacenado en la posicion pos (la cabeza es la posicion 0).
// Lanza out_of_range si la lista esta vacia o la posicion no existe.
template <typename T>
T ListaDobleCircular<T>::obtenerEnPosicion(int pos)
{
    if (estaVacia())
    {
        throw out_of_range("La lista esta vacia");
    }
    if (pos < 0 || pos >= tamanio)
    {
        throw out_of_range("Posicion fuera de rango");
    }

    Nodo<T>* actual = cabeza;

    // Al ser doble y circular, se recorre por el lado mas corto:
    // hacia adelante si pos esta en la primera mitad,
    // hacia atras (desde el ultimo nodo) si esta en la segunda mitad.
    if (pos <= tamanio / 2)
    {
        for (int i = 0; i < pos; i++)
        {
            actual = actual->getSiguiente();
        }
    }
    else
    {
        for (int i = 0; i < tamanio - pos; i++)
        {
            actual = actual->getAnterior();
        }
    }

    return actual->getDato();
}

#endif
