#include "engine.hpp"
#include <iomanip>
#include <iostream>
#include <map>
#include <regex>
#include <stack>
#include <string>

std::string obtenerPrimeraPalabra(const std::string& texto) {
    // Expresion regular para encontrar la primera palabra
    std::regex patron("\\b\\w+\\b");

    // Buscar la primera palabra en el texto
    std::smatch matches;
    if (std::regex_search(texto, matches, patron)) {
        return matches.str();
    }

    // Si no se encuentra ninguna palabra, devolver una cadena vacia
    return "";
}

bool esHTMLBalanceado(const std::string& texto,std::map<std::string, int>& contadorEtiquetas) {
    std::stack<std::string> pila;

    std::map<std::string, int> etiquetasPermitidas = {
        {"h1", 0},   {"h2", 0},  {"p", 0}, {"body", 0}, {"html", 0},
        {"head", 0}, {"div", 0}, {"a", 0}, {"title", 0}};

    std::regex patron("<[^<>]*>");

    std::sregex_iterator it(texto.begin(), texto.end(), patron);
    std::sregex_iterator itEnd;

    int totalEtiquetas = 0;

    std::regex patronEnlace("<a\\s+[^>]*href=\"([^\"]*)\"[^>]*>");
    std::smatch matchesEnlace;

    for (; it != itEnd; ++it) {
        std::string match = it->str();

        if (match.find("<!DOCTYPE html>") != std::string::npos) {
            continue;
        }

        std::string tag = obtenerPrimeraPalabra(match);
        auto itEtiqueta = etiquetasPermitidas.find(tag);

        if (itEtiqueta == etiquetasPermitidas.end()) {
            // La etiqueta no es permitida
            return false;
        }
        itEtiqueta->second++;
        totalEtiquetas++;

        if (match.find('/') == std::string::npos) {
            pila.push(tag);
        } else {
            if (pila.empty() || tag != pila.top()) {
                return false;
            }

            // std::string ultimaEtiquetaApertura = pila.top();
            pila.pop();

            /*if ( tag !=  ultimaEtiquetaApertura ) {
                return false;
            }*/
            while (std::regex_search(match, matchesEnlace, patronEnlace)) {
                std::cout << "Enlace: " << matchesEnlace[1].str() << std::endl;
                match = matchesEnlace.suffix();
            }
        }
    }

    std::cout << "Porcentaje de etiquetas:" << std::endl;
    for (const auto& par : etiquetasPermitidas) {
        double porcentaje = (par.second * 100.0) / totalEtiquetas;
        std::cout << "Etiqueta: " << par.first << ", Contador: " << par.second
                  << ", Porcentaje: " << std::fixed << std::setprecision(2)
                  << porcentaje << "%" << std::endl;
    }

    // contadorEtiquetas = etiquetasPermitidas;
    return pila.empty();
}