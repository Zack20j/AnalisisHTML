#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <iomanip>
#include <limits>
#include "htmlInfo.hpp"

void GuardarInformacion :: save(EtiquetaInfo etiquetaInfo) {
    

}

std::string GuardarInformacion :: structToString(EtiquetaInfo info){
    std::stringstream ss;
    
    ss << "Balanceado: " << (info.balanceado ? "Sí" : "No") << "\n";

    ss << "Etiquetas No Permitidas:\n";
    for (const auto& etiqueta : info.etiquetasNoPermitidas) {
        ss << etiqueta << "\n";
    }

    ss << "Atributos por Etiqueta:\n";
    for (const auto& par : info.atributosPorEtiqueta) {
        ss << "Etiqueta: " << par.first << ", Atributos: ";
        for (const auto& atributo : par.second) {
            ss << atributo << " ";
        }
        ss << "\n";
    }

    ss << "Enlaces por Etiqueta:\n";
    for (const auto& par : info.enlacesPorEtiqueta) {
        ss << "Etiqueta: " << par.first << ", Enlaces: ";
        for (const auto& enlace : par.second) {
            ss << enlace << " ";
        }
        ss << "\n";
    }

    ss << "Imágenes por Etiqueta:\n";
    for (const auto& par : info.imagenesPorEtiqueta) {
        ss << "Etiqueta: " << par.first << ", Imágenes: ";
        for (const auto& imagen : par.second) {
            ss << imagen << " ";
        }
        ss << "\n";
    }

    ss << "Contador de Etiquetas:\n";
    for (const auto& par : info.contadorEtiquetas) {
        double porcentaje = (par.second * 100.0) / info.totalEtiquetas;
        ss << "Etiqueta: " << par.first << ", Contador: " << par.second
            << ", Porcentaje: " << std::fixed << std::setprecision(2) << porcentaje << "%\n";
    }

    return ss.str();
}






