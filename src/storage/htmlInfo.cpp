#include "htmlInfo.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <string>
#include <vector>

GuardarInformacion::GuardarInformacion() {
}

void GuardarInformacion::save(EtiquetaInfo etiquetaInfo,
                              std ::string filename) {
    std::string String = structToString(etiquetaInfo);
    std::ofstream file(filename);
    file << String;
    file.close();
}

std::string GuardarInformacion::load(std::string filename) {
    std::ifstream file(filename);
    std::string content;

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            content += line + "\n";
        }
        file.close();
    } else {
        content = "No se pudo abrir el archivo.";
    }
    return content;
}

std::string GuardarInformacion::structToString(EtiquetaInfo info) {
    std::stringstream ss;

    ss << "Balanceado: " << (info.balanceado ? "Sí" : "No") << "\n";

    ss << "--------------------------------------------------------------------"
          "----------\n";

    ss << "Etiquetas No Permitidas:\n";
    for (const auto& etiqueta : info.etiquetasNoPermitidas) {
        ss << etiqueta << "\n";
    }

    ss << "--------------------------------------------------------------------"
          "----------\n";

    ss << "Atributos por Etiqueta:\n";
    for (const auto& par : info.atributosPorEtiqueta) {
        if (!par.second.empty()) {
            ss << "Etiqueta: " << par.first << ", Atributos: ";
            for (const auto& atributo : par.second) {
                ss << atributo << " ";
            }
            ss << "\n";
        }
    }

    ss << "--------------------------------------------------------------------"
          "----------\n";

    ss << "Enlaces por Etiqueta:\n";
    for (const auto& par : info.enlacesPorEtiqueta) {
        if (!par.second.empty()) {
            ss << "Etiqueta: " << par.first << ", Enlaces: ";
            for (const auto& enlace : par.second) {
                ss << enlace << " ";
            }
            ss << "\n";
        }
    }

    ss << "--------------------------------------------------------------------"
          "----------\n";

    ss << "Imágenes por Etiqueta:\n";
    for (const auto& par : info.imagenesPorEtiqueta) {
        if (!par.second.empty()) {
            ss << "Etiqueta: " << par.first << ", Imágenes: ";
            for (const auto& imagen : par.second) {
                ss << imagen << " ";
            }
            ss << "\n";
        }
    }

    ss << "--------------------------------------------------------------------"
          "----------\n";

    ss << "Contador de Etiquetas:\n";
    for (const auto& par : info.contadorEtiquetas) {
        double porcentaje = (par.second * 100.0) / info.totalEtiquetas;
        ss << "Etiqueta: " << par.first << ", Contador: " << par.second
           << ", Porcentaje: " << std::fixed << std::setprecision(2)
           << porcentaje << "%\n";
    }

    return ss.str();
}
