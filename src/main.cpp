#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
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

    AnalisisHTML analisisHTML = AnalisisHTML();
    analisisHTML.init(contenidoHTML,"htmlInfo.txt"); 

    return 0;
}
