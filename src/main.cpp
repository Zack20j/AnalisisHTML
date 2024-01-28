#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include "logic/engine.hpp"

int main() {
  std::string nombreArchivoHTML = "../index.html";

     std::ifstream archivoHTML(nombreArchivoHTML);
    if (!archivoHTML.is_open()) {
        std::cerr << "Error al abrir el archivo: " << nombreArchivoHTML << std::endl;
        return 1;
    }

    std::string contenidoHTML((std::istreambuf_iterator<char>(archivoHTML)),
                              std::istreambuf_iterator<char>());

    archivoHTML.close();

    if (esHTMLBalanceado(contenidoHTML)) {
        std::cout << "El HTML esta bien balanceado." << std::endl;
    } else {
        std::cout << "El HTML esta mal balanceado." << std::endl;
    }

    /*if (esHTMLBalanceado(htmlBalanceado)) {
        std::cout << "El HTML esta bien balanceado." << std::endl;
        //std::map<std::string, std::vector<std::string>> atributos = obtenerAtributos(htmlBalanceado);

        for (const auto& par : atributos) {
            std::cout << "Etiqueta: <" << par.first << ">" << std::endl;
              for (const auto& atributo : par.second) {
                  std::cout << "  Atributo: " << atributo << std::endl;
              }
        }
    }else {
        std::cout << "El HTML esta mal balanceado." << std::endl;
    }*/

    return 0;
}