#include "FileOperations.h"
#include <fstream>


void saveGameResults(const std::string& filename, int score) {
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << "Score: " << score << "\n";
        outFile.close();
    }
}

std::vector<std::string> loadGameResults(const std::string& filename) {
    std::vector<std::string> results;
    std::ifstream inFile(filename);
    if (inFile.is_open()) {
        std::string line;
        while (std::getline(inFile, line)) {
            results.push_back(line);
        }
        inFile.close();
    }
    return results;
}

