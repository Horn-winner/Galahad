#include "../include/Activo.h"
#include <iostream>
#include <iomanip>

void Activo::mostrar() const {
    double valorInv = cantidad * precioEntrada;
    double valorAct = cantidad * precioActual;
    double pnl = valorAct - valorInv;

    // Formato de tabla: Nombre | Ticker | Cantidad | Precio | Ganancia/Perdida
    std::cout << std::left << std::setw(15) << nombre 
              << " | " << std::setw(6) << acronimo 
              << " | Cant: " << std::fixed << std::setprecision(2) << std::setw(8) << cantidad 
              << " | P.Act: $" << std::setw(10) << precioActual 
              << " | P/L: " << (pnl >= 0 ? "+" : "") << pnl << " USD" << std::endl;
}