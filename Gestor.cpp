#include "../include/Gestor.h"
#include <iostream>
#include <iomanip>

// Cambiado a 'cargar' para que el Main no de error
bool Gestor::cargar(const std::string& archivo) {
    std::ifstream file(archivo);
    if (!file.is_open()) return false;

    std::string linea;
    cartera.clear();
    while (std::getline(file, linea)) {
        if (linea.empty()) continue;
        std::stringstream ss(linea);
        std::string n, a, c, p;
        if (std::getline(ss, n, ',') && std::getline(ss, a, ',') && 
            std::getline(ss, c, ',') && std::getline(ss, p, ',')) {
            try {
                cartera.push_back(std::make_unique<Activo>(n, a, std::stod(c), std::stod(p)));
            } catch (...) { continue; }
        }
    }
    return true;
}

// Implementamos la conexión con el Motor de Precios
void Gestor::actualizarPrecios() {
    std::vector<std::string> ids;
    for (const auto& a : cartera) ids.push_back(a->getNombre());

    MotorDePrecios::getInstance().actualizarPrecios(ids);

    for (auto& a : cartera) {
        double p = MotorDePrecios::getInstance().obtenerPrecio(a->getNombre());
        if (p > 0) a->actualizarPrecio(p);
    }
}

void Gestor::informe() const {
    std::cout << "\n>>> ESTADO DE CARTERA - GALAHAD CORE <<<" << std::endl;
    for (auto& a : cartera) a->mostrar();
}

// El Main llama a esta función
void Gestor::generarSalidaWeb(bool firmado) {
    generarJsonWeb(firmado); // Reutilizamos tu lógica de JSON
    std::cout << "[IA] Datos exportados a cartera_web.json" << std::endl;
}

void Gestor::generarJsonWeb(bool modoAutonomo) const {
    std::ofstream webFile("Datos/cartera_web.json");
    double total = 0;
    for (const auto& a : cartera) total += a->getValorActual();

    webFile << "{\n";
    webFile << "  \"total_capital\": " << std::fixed << std::setprecision(2) << total << ",\n";
    webFile << "  \"modo_autonomo\": " << (modoAutonomo ? "true" : "false") << ",\n";
    webFile << "  \"last_update\": \"Sincronizado con Galahad Core\"\n";
    webFile << "}";
    webFile.close();
}