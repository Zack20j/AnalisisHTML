#include <iomanip>
#include <iostream>
#include <map>
#include <regex>
#include <stack>
#include <string>
#include "engine.hpp"
#include "htmlInfo.hpp"
#include "obtenerEtiquetasPermitidas.hpp"
#include "obtenerEtiquetasAtributos.hpp"


AnalisisHTML::AnalisisHTML() {
}

std::string AnalisisHTML:: obtenerPrimeraPalabra(const std::string& texto) {
    std::regex patron("\\b\\w+\\b");
    std::smatch matches;

    if (std::regex_search(texto, matches, patron)) {
        return matches.str();
    }

    return "";
}

std::vector<std::string> AnalisisHTML::joinVectors( std::vector<std::string>& vector1,  std::vector<std::string>& vector2) {
    std::vector<std::string> resultado;

    // Insertar elementos de vector1
    resultado.insert(resultado.end(), vector1.begin(), vector1.end());

    // Insertar elementos de vector2 que no estén en vector1
    for (const auto& elemento : vector2) {
        if (std::find(vector1.begin(), vector1.end(), elemento) == vector1.end()) {
            resultado.push_back(elemento);
        }
    }

    return resultado;
}

std::string AnalisisHTML:: obtenerUltimosDosCaracteres(const std::string& str) {
    if (str.length() >= 2) {
        //std :: cout << str.substr(str.length() - 2) << std :: endl;
        return str.substr(str.length() - 2);
    } else {
        return str;
    }
}

std::map<std::string, std::vector<std::string>> AnalisisHTML:: obtenerAtributos(const std::string& match) {
    std::map<std::string, std::vector<std::string>> atributosPorEtiqueta = obtenerEtiquetasAtributos();

    std::regex patronAtributos("\\s+([^=\\s]+)=\"([^\"]*)\"");
    std::sregex_iterator itAtributos(match.begin(), match.end(), patronAtributos);
    std::sregex_iterator itAtributosEnd;

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
std::vector<std::string> AnalisisHTML:: encontrarCoincidencias(std::string texto,std::string expresionRegular) {
    std::vector<std::string> coincidencias;
    std::string link = texto;
    std::regex patronEnlace(expresionRegular);
    std::smatch matchesEnlace;

    while (std::regex_search(link, matchesEnlace, patronEnlace)) {
        coincidencias.push_back(matchesEnlace[1].str());
        link = matchesEnlace.suffix();
    }

    return coincidencias;
}

EtiquetaInfo AnalisisHTML:: analizarHTML(const std::string& texto) {

    std::stack<std::string> pila;
    EtiquetaInfo etiquetaInfo;
    bool esBalanceado = true;
    std::map<std::string, int> etiquetasPermitidas = obtenerEtiquetasPermitidas();

    int totalEtiquetas = 0;
    
    std::regex patron("<[^><]*>");
    std::sregex_iterator it(texto.begin(), texto.end(), patron);
    std::sregex_iterator itEnd;
    
    for (; it != itEnd; ++it) {
        std::string match = it->str();

        if (match.find("<!DOCTYPE html>") != std::string::npos) {
            continue;
        }

        std::string tag = obtenerPrimeraPalabra(match);
        auto itEtiqueta = etiquetasPermitidas.find(tag);

        if (itEtiqueta == etiquetasPermitidas.end()) {
            etiquetaInfo.etiquetasNoPermitidas.push_back(tag);
            continue;
        }

        std::map<std::string, std::vector<std::string>> atributos = obtenerAtributos(match);

        etiquetaInfo.atributosPorEtiqueta[tag] = joinVectors(etiquetaInfo.atributosPorEtiqueta[tag], atributos[tag]);
 
        std::vector<std::string> links = encontrarCoincidencias(match, "(?:a|link)\\s+[^>]*href=\"([^\"]*)\"[^>]*");
        std::vector<std::string> images = encontrarCoincidencias(match, "<img\\s+[^>]*src=\"([^\"]*)\"[^>]*>");

        etiquetaInfo.enlacesPorEtiqueta[tag] = joinVectors(etiquetaInfo.enlacesPorEtiqueta[tag], links);
        etiquetaInfo.imagenesPorEtiqueta[tag] = joinVectors(etiquetaInfo.imagenesPorEtiqueta[tag], images);


        if (obtenerUltimosDosCaracteres(match) == "/>") {

            etiquetaInfo.contadorEtiquetas[tag]++;
            etiquetaInfo.totalEtiquetas++;
        }

        else if (match.find("</") == 0) {
            if (pila.empty() || tag != pila.top()) {
                etiquetaInfo.balanceado = false;
            }
            pila.pop();
            
            etiquetaInfo.contadorEtiquetas[tag]++;
            etiquetaInfo.totalEtiquetas++;

        }else {
            pila.push(tag);
        }
    }

    etiquetaInfo.balanceado = pila.empty();
    return etiquetaInfo;
}