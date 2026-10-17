#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>


template <typename T>
std::vector<T> loadFromFile(const std::string& path,
                            T (*createObject)(const std::string& line, int lineNumber)) {
    std::ifstream file(path);
    if (!file) {
        throw std::runtime_error("Could not open file: " + path);
    }

    std::vector<T> objects;
    std::string line;
    int lineNumber = 0;
    while (std::getline(file, line)) {
        lineNumber++;
        if (line.empty()) continue; // Skip empty lines
        try {
            objects.push_back(createObject(line, lineNumber));
        } catch (const std::exception& e) {
            throw std::runtime_error("Error in file " + path + " at line " + std::to_string(lineNumber) + ": " + e.what());
        }
    }
    return objects;
}

template <typename T>
void saveToFile(const std::string& path, const std::vector<T>& objects,
                std::string (*toLine)(const T& obj)) {
    std::ofstream file(path);
    if (!file) {
        throw std::runtime_error("Could not open file for writing: " + path);
    }

    for (const T& obj : objects) {
        file << toLine(obj) << "\n";
    }
    file.close();
}

#endif // FILEUTILS_H