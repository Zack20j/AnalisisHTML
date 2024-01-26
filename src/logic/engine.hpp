#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <string>
#include <map>

std::string obtenerPrimeraPalabra(const std::string& texto);
bool esHTMLBalanceado(const std::string& texto,std::map<std::string, int>& contadorEtiquetas);


#endif  // ENGINE_HPP