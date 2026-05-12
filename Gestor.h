#ifndef GESTOR_H
#define GESTOR_H

#include "Activo.h"
#include "MotorDePrecios.h"
#include <vector>
#include <memory>
#include <string>
#include <fstream>
#include <sstream>

class Gestor {
private:
    std::vector<std::unique_ptr<Activo>> cartera;

public:
    // Métodos para el CSV
    bool cargar(const std::string& archivo); // Tu Main lo llama 'cargar'
    
    // Métodos para la IA y el Motor
    void actualizarPrecios();
    void informe() const;
    
    // Métodos para la Web
    void generarSalidaWeb(bool firmado); // Nombre que usa tu Main
    void generarJsonWeb(bool modoAutonomo) const;
};

#endif