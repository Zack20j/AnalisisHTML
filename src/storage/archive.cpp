#include "archive.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

FileManager::FileManager(const std::string& filename) {
    this->filename = filename;
}

bool FileManager::writeFile(const std::string& content) {
    std::ofstream file(filename, std::ios::out | std::ios::trunc);

    if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo para escritura." << std::endl;
        return false;
    }

    file << content;
    file.close();
    return true;
}

std::string FileManager::readFile() {
    std::ifstream file(filename, std::ios::in);
    std::stringstream buffer;

    if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo para lectura." << std::endl;
        return "";
    }

    buffer << file.rdbuf();
    file.close();

    return buffer.str();
}