#ifndef FILEOPERATIONS_H
#define FILEOPERATIONS_H

#include <string>
#include <vector>

void saveGameResults(const std::string& filename, int score);

std::vector<std::string> loadGameResults(const std::string& filename);

#endif // FILEOPERATIONS_H

