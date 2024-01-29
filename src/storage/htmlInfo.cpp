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

EtiquetaInfo GuardarInformacion :: stringToStruct( std::string& inputString) {
        std::istringstream ss(inputString);
        std::string line;
        EtiquetaInfo info;


        // Leer y procesar cada línea del string
        while (std::getline(ss, line)) {
            if (line.find("Balanceado: ") != std::string::npos) {
                info.balanceado = (line.find("Sí") != std::string::npos);
            } else if (line == "Etiquetas No Permitidas:") {
                while (std::getline(ss, line) && !line.empty()) {
                    info.etiquetasNoPermitidas.push_back(line);
                }
            } else if (line == "Atributos por Etiqueta:") {
                while (std::getline(ss, line) && line.find("Etiqueta: ") != std::string::npos) {
                    std::string etiqueta;
                    std::vector<std::string> atributos;
                    std::istringstream lineStream(line);
                    lineStream.ignore(std::numeric_limits<std::streamsize>::max(), ' '); // Ignorar "Etiqueta: "
                    lineStream >> etiqueta;

                    std::string atributo;
                    while (lineStream >> atributo) {
                        atributos.push_back(atributo);
                    }

                    info.atributosPorEtiqueta[etiqueta] = atributos;
                }
            } else if (line == "Enlaces por Etiqueta:") {
                while (std::getline(ss, line) && line.find("Etiqueta: ") != std::string::npos) {
                    std::string etiqueta;
                    std::vector<std::string> enlaces;
                    std::istringstream lineStream(line);
                    lineStream.ignore(std::numeric_limits<std::streamsize>::max(), ' '); // Ignorar "Etiqueta: "
                    lineStream >> etiqueta;

                    std::string enlace;
                    while (lineStream >> enlace) {
                        enlaces.push_back(enlace);
                    }

                    info.enlacesPorEtiqueta[etiqueta] = enlaces;
                }
            } else if (line == "Imágenes por Etiqueta:") {
                while (std::getline(ss, line) && line.find("Etiqueta: ") != std::string::npos) {
                    std::string etiqueta;
                    std::vector<std::string> imagenes;
                    std::istringstream lineStream(line);
                    lineStream.ignore(std::numeric_limits<std::streamsize>::max(), ' '); // Ignorar "Etiqueta: "
                    lineStream >> etiqueta;

                    std::string imagen;
                    while (lineStream >> imagen) {
                        imagenes.push_back(imagen);
                    }

                    info.imagenesPorEtiqueta[etiqueta] = imagenes;
                }
            } else if (line == "Contador de Etiquetas:") {
                while (std::getline(ss, line) && line.find("Etiqueta: ") != std::string::npos) {
                    std::string etiqueta;
                    int contador;
                    double porcentaje;
                    std::istringstream lineStream(line);
                    lineStream.ignore(std::numeric_limits<std::streamsize>::max(), ' '); // Ignorar "Etiqueta: "
                    lineStream >> etiqueta;
                    lineStream.ignore(std::numeric_limits<std::streamsize>::max(), ':'); // Ignorar ", Contador: "
                    lineStream >> contador;
                    lineStream.ignore(std::numeric_limits<std::streamsize>::max(), ':'); // Ignorar ", Porcentaje: "
                    lineStream >> porcentaje;

                    info.contadorEtiquetas[etiqueta] = contador;
                }
            }
        }

        // Calcular totalEtiquetas sumando los contadores
        info.totalEtiquetas = 0;
        for (const auto& par : info.contadorEtiquetas) {
            info.totalEtiquetas += par.second;
        }
    }





