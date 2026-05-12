#include "Activo.h"
#include "MotorDePrecios.h"
#include <iostream>

int main() {
    Gestor galahad;
    std::string input;
    bool mandatoFirmado = false;

    if (galahad.cargar("Datos/cartera.csv")) {
        std::cout << "GALAHAD INTELLIGENCE v1.5 [BOOTING...]" << std::endl;
        
        while (input != "salir") {
            std::cout << "\n[COMANDOS]: 'enter' (Actualizar), 'firmar' (Activar IA), 'salir'\n>> ";
            std::getline(std::cin, input);

            if (input == "firmar") {
                mandatoFirmado = true;
                std::cout << "[!] MANDATO DE EJECUCION AUTONOMA ACTIVADO." << std::endl;
                continue;
            }

            // SIMULACIÓN DE IA GEOPOLÍTICA
            double riesgoGeopolitico = 8.0; // Esto vendría de un análisis de noticias
            
            std::cout << "[INFO] Analizando S&P 500 y Factores Globales..." << std::endl;
            galahad.actualizarPrecios();
            
            if (riesgoGeopolitico > 7.0) {
                std::cout << "[ALERTA] Inestabilidad detectada (Nivel " << riesgoGeopolitico << ")" << std::endl;
                if (mandatoFirmado) {
                    std::cout << "[AUTO] Galahad rebalanceando para maximizar beneficio..." << std::endl;
                } else {
                    std::cout << "[AVISO] IA sugiere vender. Falta firma de mandato en web." << std::endl;
                }
            }

            galahad.informe();
            galahad.generarSalidaWeb(mandatoFirmado);
        }
    }
    return 0;
}