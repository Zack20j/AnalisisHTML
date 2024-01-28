#include "engine.hpp"
#include <iomanip>
#include <iostream>
#include <map>
#include <regex>
#include <stack>
#include <string>
#include "obtenerEtiquetasPermitidas.hpp"
#include "obtenerEtiquetasAtributos.hpp"

std::string obtenerPrimeraPalabra(const std::string& texto) {
    std::regex patron("\\b\\w+\\b");
    std::smatch matches;

    if (std::regex_search(texto, matches, patron)) {
        return matches.str();
    }

    return "";
}

std::string obtenerUltimosDosCaracteres(const std::string& str) {
    if (str.length() >= 2) {
        //std :: cout << str.substr(str.length() - 2) << std :: endl;
        return str.substr(str.length() - 2);
    } else {
        return str;
    }
}

std::map<std::string, std::vector<std::string>> obtenerAtributos(const std::string& match) {
    std::map<std::string, std::vector<std::string>> atributosPorEtiqueta = obtenerEtiquetasAtributos();

    std::regex patronAtributos("\\s+([^=\\s]+)=\"([^\"]*)\"");
    std::sregex_iterator itAtributos(match.begin(), match.end(), patronAtributos);
    std::sregex_iterator itAtributosEnd;

    // Extraer atributos para la etiqueta correspondiente
    if (itAtributos != itAtributosEnd) {
        std::string etiqueta = obtenerPrimeraPalabra(match); // Obtener el nombre de la etiqueta
        do {
            std::string nombreAtributo = itAtributos->str(1);
            atributosPorEtiqueta[etiqueta].push_back(nombreAtributo);
            ++itAtributos;
        } while (itAtributos != itAtributosEnd);
    }

    return atributosPorEtiqueta;
}

bool esHTMLBalanceado(const std::string& texto) {
    std::stack<std::string> pila;
    std::map<std::string, int> etiquetasPermitidas = obtenerEtiquetasPermitidas();

    std::regex patron("<[^><]*>");
    std::sregex_iterator it(texto.begin(), texto.end(), patron);
    std::sregex_iterator itEnd;

    std::regex patronEnlace("<(?:a|link)\\s+[^>]*href=\"([^\"]*)\"[^>]*>");
    std::smatch matchesEnlace;

    std::regex patronImagen("<img\\s+[^>]*src=\"([^\"]*)\"[^>]*>");  
    std::smatch matchesImagen;

    int totalEtiquetas = 0;
    
    for (; it != itEnd; ++it) {
        std::string match = it->str();

        if (match.find("<!DOCTYPE html>") != std::string::npos) {
            continue;
        }

        std::string tag = obtenerPrimeraPalabra(match);
        auto itEtiqueta = etiquetasPermitidas.find(tag);

        if (itEtiqueta == etiquetasPermitidas.end()) {
            return false;
        }

        std::map<std::string, std::vector<std::string>> atributos = obtenerAtributos(match);

        // Imprimir atributos
       if (!atributos[tag].empty()) {
            std::cout << "Etiqueta: " << tag << ", Atributos: ";
            
            // Imprimir atributos
            for (const auto& atributo : atributos[tag]) {
                std::cout << atributo << " ";
            }

            std::cout << std::endl;
        }

        std::string link = match;
        while (std::regex_search(link, matchesEnlace, patronEnlace)) {
            std::cout << "Enlace: " << matchesEnlace[1].str() << std::endl;
            link = matchesEnlace.suffix();
        }

        std::string image = match;
        while (std::regex_search(image, matchesImagen, patronImagen)) {
            std::cout << "Imagen: " << matchesImagen[1].str() << std::endl;
            image = matchesImagen.suffix();
        }

        if (obtenerUltimosDosCaracteres(match) == "/>") {
            itEtiqueta->second++;
            totalEtiquetas++;
        }

        else if (match.find("</") == 0) {
            //std :: cout << "Etiqueta de cierre: " << std::endl;
            if (pila.empty() || tag != pila.top()) {
                return false;
            }
            pila.pop();

            itEtiqueta->second++; 
            totalEtiquetas++;

        }else {
            //std :: cout << "Etiqueta de apertura: " << std::endl;
            pila.push(tag);
        }
    }

    std::cout << "Etiquetas:" << std::endl;
     for (const auto& par : etiquetasPermitidas) {
         if (par.second > 0) {
             double porcentaje = (par.second * 100.0) / totalEtiquetas;
             std::cout << "Etiqueta: " << par.first << ", Contador: " << par.second
                       << ", Porcentaje: " << std::fixed << std::setprecision(2)
                       << porcentaje << "%" << std::endl;
         }
     }
    return pila.empty();
}