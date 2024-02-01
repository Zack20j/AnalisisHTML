#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include "storage/htmlInfo.hpp"
#include "logic/engine.hpp"

int main() {
    std::string nombreArchivoHTML = "../index.html";

    std::ifstream archivoHTML(nombreArchivoHTML);
    if (!archivoHTML.is_open()) {
        std::cerr << "Error al abrir el archivo: " << nombreArchivoHTML
                  << std::endl;
        return 1;
    }

    std::string contenidoHTML((std::istreambuf_iterator<char>(archivoHTML)),
                              std::istreambuf_iterator<char>());

    archivoHTML.close();

    //EtiquetaInfo etiquetaInfo = esHTMLBalanceado(contenidoHTML);
    //mostrarAnalisisHTMLInfo(etiquetaInfo);

    AnalisisHTML analisisHTML = AnalisisHTML();
    EtiquetaInfo info = analisisHTML.analizarHTML(contenidoHTML);

    for (const auto& par : info.atributosPorEtiqueta) {
        std::cout << "Etiqueta: " << par.first << ", Atributos: ";
        for (const auto& atributo : par.second) {
            std::cout << atributo << " ";
        }
        std::cout << std::endl;
    }
    
    /*for ( const std::string& etiqueta : info.etiquetasNoPermitidas ) {
        std::cout << "Etiqueta no permitida: " << etiqueta << std::endl;
    }*/

    for (const auto& par : info.enlacesPorEtiqueta) {
        std::cout << "Etiqueta: " << par.first << ", Enlaces: ";
        for (const auto& enlace : par.second) {
            std::cout << enlace << " ";
        }
        std::cout << std::endl;
    }
  
    for (const auto& par : info.imagenesPorEtiqueta) {
        std::cout << "Etiqueta: " << par.first << ", Imagenes: ";
        for (const auto& imagen : par.second) {
            std::cout << imagen << " ";
        }
        std::cout << std::endl;
    }

    std :: cout << "Balanceado: " << info.balanceado << std :: endl;



    for (const auto& par : info.contadorEtiquetas) {

        std::cout << "Etiqueta: " << par.first << ", Contador: " << par.second << std::endl;

    }
    /*std::cout << "Etiquetas:" << std::endl;
    for (const auto& par : etiquetasPermitidas) {
        if (par.second > 0) {
            double porcentaje = (par.second * 100.0) / totalEtiquetas;
            std::cout << "Etiqueta: " << par.first << ", Contador: " << par.second
                      << ", Porcentaje: " << std::fixed << std::setprecision(2)
                      << porcentaje << "%" << std::endl;
        }
    }*/

    return 0;
}
