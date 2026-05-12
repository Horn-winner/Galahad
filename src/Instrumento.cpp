#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <memory>
#include <cstdlib>

#include "Instrumento.h"


// ================== MODELO BASE ==================
Instrumento::Instrumento(const std::string& n, const std::string& a, double c, double p): nombre(n), acronimo(a), cantidad(c), precioEntrada(p) {
    precioActual = 0.0;
}
std::string Instrumento::getNombre() const {
    return nombre;
}