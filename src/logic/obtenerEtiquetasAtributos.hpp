#include <string>
#include <map>
#include <vector>


std::map<std::string, std::vector<std::string>> obtenerEtiquetasAtributos( ) {
    
    return std::map<std::string, std::vector<std::string>> {
    {"match", {}},
    {"html", {}},
    {"head", {}},
    {"title", {}},
    {"body", {}},
    {"h1", {}},
    {"h2", {}},
    {"h3", {}},
    {"h4", {}},
    {"h5", {}},
    {"h6", {}},
    {"p", {}},
    {"a", {}},
    {"img", {}},
    {"div", {}},
    {"span", {}},
    {"ul", {}},
    {"ol", {}},
    {"li", {}},
    {"table", {}},
    {"tr", {}},
    {"br", {}},
    {"hr", {}},
    {"td", {}},
    {"th", {}},
    {"form", {}},
    {"input", {}},
    {"textarea", {}},
    {"select",  {}},
    {"button", {}},
    {"label", {}},
    {"meta", {}},
    {"link", {}},
    {"style", {}},
    {"script", {}},
    {"iframe",  {}},
    {"strong", {}},
    {"em", {}},
    {"b", {}},
    {"i", {}},
    {"u", {}},
    {"sub", {}},
    {"sup", {}}
    };
}