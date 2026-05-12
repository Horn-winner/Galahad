#ifndef ACTIVO_H
#define ACTIVO_H

#include "Instrumento.h"
#include <iostream>
#include <string>

class Activo : public Instrumento {
public:
    // Constructor: Pasa los datos a la clase base Instrumento
    Activo(std::string n, std::string a, double c, double p) 
        : Instrumento(n, a, c, p) {}

    // Implementación del método para mostrar datos en consola
    void mostrar() const override;

    // Métodos para que el Gestor pueda calcular totales
    double getValorActual() const { return cantidad * precioActual; }
    void actualizarPrecio(double p) { precioActual = p; }
};

#endif
