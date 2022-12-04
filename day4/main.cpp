#include <fstream>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <string>
#include <optional>
#include <numeric>
#include <unordered_set>
#include <algorithm>
#include <utility>
#include <regex>

struct ElfPair {
    std::pair<int, int> firstElf;
    std::pair<int, int> secondElf;
};

std::istream& operator>>(std::istream& is, ElfPair& obj)
{
    std::regex rgx("([0-9]+)-([0-9]+),([0-9]+)-([0-9]+)");
    std::smatch matches;
    std::string line;
    is >> line;

    if (std::regex_match(line, matches, rgx)) {
        obj.firstElf = std::make_pair<int, int>(std::stoi(matches[1]), std::stoi(matches[2]));
        obj.secondElf = std::make_pair<int, int>(std::stoi(matches[3]), std::stoi(matches[4]));
    } else {
        std::cout << "Regex didn't match " << line << std::endl;
    }

    return is;
}

void readIntegerLines(const std::string& fileName, std::vector<ElfPair>& out) {
    std::ifstream istream;

    istream.open(fileName, std::ios::in);
    if (!istream.good()) {
        std::cerr << "Error while opening input file!" << std::endl;
        return;
    }

    ElfPair currElfPair;
    while (istream >> currElfPair) {
        out.push_back(currElfPair);
    }

    std::cout << "Read " << out.size() << " lines." << std::endl;
}

void partOne(const std::vector<ElfPair>& elfPairs) {
    int count = 0;
    for (const auto& elfPair: elfPairs) {
        if ((elfPair.firstElf.first >= elfPair.secondElf.first && elfPair.firstElf.second <= elfPair.secondElf.second) ||
            (elfPair.secondElf.first >= elfPair.firstElf.first && elfPair.secondElf.second <= elfPair.firstElf.second)) {
            count += 1;
        }
    }

    std::cout << count << std::endl;
}

void partTwo(const std::vector<ElfPair>& elfPairs) {
    int count = 0;
    for (const auto& elfPair: elfPairs) {
        if ((elfPair.firstElf.first >= elfPair.secondElf.first && elfPair.firstElf.first <= elfPair.secondElf.second) ||
            (elfPair.firstElf.second >= elfPair.secondElf.first && elfPair.firstElf.second <= elfPair.secondElf.second) ||
            (elfPair.secondElf.first >= elfPair.firstElf.first && elfPair.secondElf.first <= elfPair.firstElf.second) ||
            (elfPair.secondElf.second >= elfPair.firstElf.first && elfPair.secondElf.second <= elfPair.firstElf.second)) {
            count += 1;
        }
    }

    std::cout << count << std::endl;
}

int main() {
    std::vector<ElfPair> elfPairs;
    readIntegerLines("day4/input", elfPairs);

    partOne(elfPairs);
    partTwo(elfPairs);

    return 0;
}
