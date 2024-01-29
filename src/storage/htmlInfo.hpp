#ifndef HTMLINFO_HPP
#define HTMLINFO_HPP
#include <string>
#include <map>
#include <vector>
#include "archive.hpp"

struct EtiquetaInfo {
    bool balanceado;
    std::vector<std::string> etiquetasNoPermitidas;
    std::map<std::string, std::vector<std::string>> atributosPorEtiqueta;
    std::map<std::string, std::vector<std::string>> enlacesPorEtiqueta;
    std::map<std::string, std::vector<std::string>> imagenesPorEtiqueta;
    std::map<std::string, int> contadorEtiquetas;
    int totalEtiquetas = 0;
};

class GuardarInformacion {
    public:
    
    void agregarAtributos(const std::string& etiqueta, const std::vector<std::string>& atributos) {
        etiquetasInfo.atributosPorEtiqueta[etiqueta] = atributos;
    }

    void agregarEnlaces(const std::string& etiqueta, const std::vector<std::string>& enlaces) {
        etiquetasInfo.enlacesPorEtiqueta[etiqueta] = enlaces;
    }

    void agregarImagenes(const std::string& etiqueta, const std::vector<std::string>& imagenes) {
        etiquetasInfo.imagenesPorEtiqueta[etiqueta] = imagenes;
    }

    void agregarEtiquetaNoPermitida(std::string etiqueta) {
        etiquetasInfo.etiquetasNoPermitidas.push_back(etiqueta);
    }

    void actualizarContador(const std::string& etiqueta) {
        etiquetasInfo.contadorEtiquetas[etiqueta]++;
        etiquetasInfo.totalEtiquetas++;
    }

    private:
    EtiquetaInfo etiquetasInfo;
};


#endif // HTMLINFO_HPP