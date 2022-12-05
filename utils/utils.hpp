#pragma once
#include <vector>
#include <string>
#include <fstream>

namespace aoc_utils {
inline std::string getFileNameFromDay(const int day) {
  return "day" + std::to_string(day) + "/input";
}

template <typename T>
void readLines(const int day, std::ifstream& istream, std::vector<T>& out) {
    T currLine;
    while (istream >> currLine) {
        out.push_back(currLine);
    }

    std::cout << "Read " << out.size() << " lines." << std::endl;
}

template<typename T>
void readLines(const int day, std::vector<T>& out) {
    std::ifstream istream;

    istream.open(getFileNameFromDay(day), std::ios::in);
    if (!istream.good()) {
        std::cerr << "Error while opening input file!" << std::endl;
        return;
    }
    readLines(day, istream, out);
}
} // namespace aoc_utils

