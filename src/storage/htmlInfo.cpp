#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <iomanip>
#include <limits>
#include <fstream>
#include "htmlInfo.hpp"

GuardarInformacion :: GuardarInformacion() {
}

void GuardarInformacion :: save(EtiquetaInfo etiquetaInfo) {

    std::string String = structToString(etiquetaInfo);
    std::ofstream file("htmlInfo.txt");
    file << String;
    file.close();
}

std::string GuardarInformacion :: structToString(EtiquetaInfo info){
    std::stringstream ss;
    
    ss << "Balanceado: " << (info.balanceado ? "Sí" : "No") << "\n";

    ss << "----------------------------------------------------------------\n";

    ss << "Etiquetas No Permitidas:\n";
    for (const auto& etiqueta : info.etiquetasNoPermitidas) {
        ss << etiqueta << "\n";
    }

    ss << "----------------------------------------------------------------\n";

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

    ss << "----------------------------------------------------------------\n";

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
    ss << "----------------------------------------------------------------\n";

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

    ss << "----------------------------------------------------------------\n";

    ss << "Contador de Etiquetas:\n";
    for (const auto& par : info.contadorEtiquetas) {
        double porcentaje = (par.second * 100.0) / info.totalEtiquetas;
        ss << "Etiqueta: " << par.first << ", Contador: " << par.second
            << ", Porcentaje: " << std::fixed << std::setprecision(2) << porcentaje << "%\n";
    }

    return ss.str();
}

EtiquetaInfo GuardarInformacion :: stringToStruct( std::string String){

    EtiquetaInfo info;

    std::istringstream ss(String);
    std::string line;

    // Leer el estado de balanceado
    std::getline(ss, line);
    if (line.find("Sí") != std::string::npos) {
        info.balanceado = true;
    } else {
        info.balanceado = false;
    }

    // Omitir líneas hasta llegar a las Etiquetas No Permitidas
    while (std::getline(ss, line) && line.find("Etiquetas No Permitidas:") == std::string::npos);

    // Leer las etiquetas no permitidas
    while (std::getline(ss, line) && line != "----------------------------------------------------------------") {
        info.etiquetasNoPermitidas.push_back(line);
    }

    // Omitir líneas hasta llegar a Atributos por Etiqueta
    while (std::getline(ss, line) && line.find("Atributos por Etiqueta:") == std::string::npos);

    // Leer atributos por etiqueta
    while (std::getline(ss, line) && line != "----------------------------------------------------------------") {
        std::istringstream lineStream(line);
        std::string etiqueta, atributo;
        lineStream >> etiqueta; // Leer la etiqueta
        while (lineStream >> atributo) {
            info.atributosPorEtiqueta[etiqueta].push_back(atributo);
        }
    }

        // Repite el mismo proceso para Enlaces por Etiqueta
    while (std::getline(ss, line) && line.find("Enlaces por Etiqueta:") == std::string::npos);

    // Leer enlaces por etiqueta
    while (std::getline(ss, line) && line != "----------------------------------------------------------------") {
        std::istringstream lineStream(line);
        std::string etiqueta, enlace;
        lineStream >> etiqueta; // Leer la etiqueta
        while (lineStream >> enlace) {
            info.enlacesPorEtiqueta[etiqueta].push_back(enlace);
        }
    }

    // Repite el mismo proceso para Imágenes por Etiqueta
    while (std::getline(ss, line) && line.find("Imágenes por Etiqueta:") == std::string::npos);

    // Leer imágenes por etiqueta
    while (std::getline(ss, line) && line != "----------------------------------------------------------------") {
        std::istringstream lineStream(line);
        std::string etiqueta, imagen;
        lineStream >> etiqueta; // Leer la etiqueta
        while (lineStream >> imagen) {
            info.imagenesPorEtiqueta[etiqueta].push_back(imagen);
        }
    }

    // Omitir líneas hasta llegar a Contador de Etiquetas
    while (std::getline(ss, line) && line.find("Contador de Etiquetas:") == std::string::npos);

    // Leer contador de etiquetas
    while (std::getline(ss, line)) {
        std::istringstream lineStream(line);
        std::string etiqueta;
        int contador;
        double porcentaje;
        lineStream >> etiqueta >> contador >> porcentaje;
        info.contadorEtiquetas[etiqueta] = contador;
    }

    return info;
}






