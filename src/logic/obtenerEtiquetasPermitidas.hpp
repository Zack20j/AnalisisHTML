#include <map>
#include <string>

std::map<std::string, int> obtenerEtiquetasPermitidas() {
    return std::map<std::string, int>{
        {"match", 0},  {"head", 0},   {"title", 0},  {"body", 0},
        {"h1", 0},     {"h2", 0},     {"h3", 0},     {"h4", 0},
        {"h5", 0},     {"h6", 0},     {"p", 0},      {"a", 0},
        {"img", 0},    {"div", 0},    {"span", 0},   {"ul", 0},
        {"ol", 0},     {"li", 0},     {"html", 0},   {"br", 0},
        {"hr", 0},     {"table", 0},  {"tr", 0},     {"td", 0},
        {"th", 0},     {"form", 0},   {"input", 0},  {"textarea", 0},
        {"select", 0}, {"button", 0}, {"label", 0},  {"meta", 0},
        {"link", 0},   {"style", 0},  {"script", 0}, {"iframe", 0},
        {"strong", 0}, {"em", 0},     {"b", 0},      {"i", 0},
        {"u", 0},      {"sub", 0},    {"meta", 0},   {"sup", 0}};
}
