#include <map>
#include <regex>
#include <stack>
#include <string>
#include "engine.hpp"
#include "storage/htmlInfo.hpp"
#include "obtenerEtiquetasPermitidas.hpp"

AnalisisHTML::AnalisisHTML() {
}

std :: string AnalisisHTML:: init(std::string texto, std ::string filename) {
    EtiquetaInfo etiquetaInfo = analizarHTML(texto);
    info.save(etiquetaInfo, filename);
    return info.load(filename);
}

std::string AnalisisHTML:: load(std :: string filename) {
    return info.load(filename);
}

std::string AnalisisHTML:: obtenerPrimeraPalabra( std::string texto) {
    std::regex patron("\\b\\w+\\b");
    std::smatch matches;

    if (std::regex_search(texto, matches, patron)) {
        return matches.str();
    }

    return "";
}

std::vector<std::string> AnalisisHTML::unirVectores( std::vector<std::string> vector1,  std::vector<std::string> vector2) {
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

std::string AnalisisHTML:: obtenerUltimosDosCaracteres( std::string str) {
    if (str.length() >= 2) {
        // std :: cout << str.substr(str.length() - 2) << std :: endl;
        return str.substr(str.length() - 2);
    } else {
        return str;
    }
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

EtiquetaInfo AnalisisHTML:: analizarHTML( std::string texto) {

    std::stack<std::string> pila;
    EtiquetaInfo etiquetaInfo;
    std::map<std::string, int> etiquetasPermitidas = obtenerEtiquetasPermitidas();
    
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

        std::vector<std::string> atributos = encontrarCoincidencias(match, "\\s+([^=\\s]+)=\"([^\"]*)\"");
        std::vector<std::string> links = encontrarCoincidencias(match, "(?:a|link)\\s+[^>]*href=\"([^\"]*)\"[^>]*");
        std::vector<std::string> images = encontrarCoincidencias(match, "<img\\s+[^>]*src=\"([^\"]*)\"[^>]*>");

        etiquetaInfo.atributosPorEtiqueta[tag] = unirVectores(etiquetaInfo.atributosPorEtiqueta[tag], atributos);
        etiquetaInfo.enlacesPorEtiqueta[tag] = unirVectores(etiquetaInfo.enlacesPorEtiqueta[tag], links);
        etiquetaInfo.imagenesPorEtiqueta[tag] = unirVectores(etiquetaInfo.imagenesPorEtiqueta[tag], images);


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
