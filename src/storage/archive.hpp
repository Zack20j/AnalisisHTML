#ifndef ARCHIVE_HPP
#define ARCHIVE_HPP

#include <string>

class FileManager {
public:
    FileManager(const std::string& filename);
    bool writeFile(const std::string& content);
    std::string readFile();

private:
    std::string filename;
};

#endif // ARCHIVE_HPP