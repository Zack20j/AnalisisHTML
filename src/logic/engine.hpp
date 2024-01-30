#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <map>
#include <string>
#include <vector>

std::string obtenerPrimeraPalabra(const std::string& texto);
bool esHTMLBalanceado(const std::string& texto);
std::string obtenerUltimosDosCaracteres(const std::string& str);
std::map<std::string, std::vector<std::string>> obtenerAtributos(
    const std::string& match);

#endif  // ENGINE_HPP
