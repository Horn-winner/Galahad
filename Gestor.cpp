#include "Gestor.h"
#include <iostream>

bool Gestor::cargarCSV(const std::string& archivo) {
    std::ifstream file(archivo);
    if (!file.is_open()) return false;

    std::string linea;
    while (std::getline(file, linea)) {
        std::stringstream ss(linea);
        std::string n, a, c, p;
        std::getline(ss, n, ','); std::getline(ss, a, ',');
        std::getline(ss, c, ','); std::getline(ss, p, ',');
        if(!n.empty())
            cartera.push_back(std::make_unique<Activo>(n, a, std::stod(c), std::stod(p)));
    }
    return true;
}

void Gestor::generarJsonWeb(bool modoAutonomo) const {
    std::ofstream webFile("cartera_web.json");
    double total = 0;
    for (auto& a : cartera) total += a->getValorActual();

    webFile << "{\n";
    webFile << "  \"total_capital\": " << total << ",\n";
    webFile << "  \"modo_autonomo\": " << (modoAutonomo ? "true" : "false") << ",\n";
    webFile << "  \"last_update\": \"Sincronizado con Galahad Core\"\n";
    webFile << "}";
    webFile.close();
}

void Gestor::informe() const {
    for (auto& a : cartera) a->mostrar();
}