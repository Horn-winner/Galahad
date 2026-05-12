#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include <cmath> // Para NAN
#include "MotorDePrecios.h"

using json = nlohmann::json;

MotorDePrecios::MotorDePrecios() : output("Datos/precios.json") {}

MotorDePrecios& MotorDePrecios::getInstance() {
    static MotorDePrecios instance;
    return instance;
}

void MotorDePrecios::actualizarPrecios(const std::vector<std::string>& listaActivos) {
    if (listaActivos.empty()) return;

    std::cout << "[MOTOR] Consultando API para: ";
    
    // Unimos los nombres en una sola cadena separada por comas
    std::string consulta = "";
    for (size_t i = 0; i < listaActivos.size(); ++i) {
        consulta += listaActivos[i];
        if (i < listaActivos.size() - 1) consulta += ",";
        std::cout << listaActivos[i] << " ";
    }
    std::cout << "..." << std::endl;

    // Construimos la URL dinámica
    std::string url = "https://api.coingecko.com/api/v3/simple/price?ids=" + consulta + "&vs_currencies=usd";
    std::string command = "curl -s \"" + url + "\" -o " + output;

    system(command.c_str());
}

double MotorDePrecios::obtenerPrecio(const std::string& nombre) {
    std::ifstream f(output);
    if (!f.is_open()) {
        std::cerr << "[ERROR] No se pudo abrir " << output << std::endl;
        return 0.0;
    }

    try {
        json j;
        f >> j;
        
        // Convertimos el nombre a minúsculas para que coincida con el JSON de la API
        std::string nombreLower = nombre;
        for(auto &c : nombreLower) c = tolower(c);

        if (j.contains(nombreLower)) {
            return j[nombreLower]["usd"];
        } else {
            std::cout << "[WARN] Activo no encontrado en JSON: " << nombreLower << std::endl;
        }
    } catch (json::parse_error& e) {
        std::cerr << "[ERROR] Error al procesar JSON: " << e.what() << std::endl;
    }

    return 0.0; // O NAN si prefieres
}