#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <optional>
#include <numeric>

void readIntegerLines(const std::string& fileName, std::vector<std::optional<int>>& out) {
    std::string output;
    std::ifstream istream;

    istream.open(fileName, std::ios::in);
    if (!istream.good()) {
        std::cerr << "Error while opening input file!" << std::endl;
        return;
    }

    while (getline(istream, output)) {
        if (output.empty()) {
            out.push_back(std::nullopt);
        } else {
            int number = std::stoi(output);
            out.push_back(number);
        }
    }

    std::cout << "Read " << out.size() << " lines." << std::endl;
}

void partOne(const std::vector<std::optional<int>>& ints) {
    int currentVal = 0;
    int maxVal = -1;
    for (const auto& i : ints) {
        if (i) {
            currentVal += *i;
        } else {
            if (currentVal > maxVal) {
                maxVal = currentVal;
            }
            currentVal = 0;
        }
    }

    std::cout << maxVal << std::endl;
}

void partTwo(const std::vector<std::optional<int>>& ints) {
    std::vector<int> topN(3, 0);
    int currentVal = 0;
    
    // maybe better to sort
    for (const auto& i : ints) {
        if (i) {
            currentVal += *i;
        } else {
            std::size_t k = 0;
            for (; topN[k] > currentVal && k < topN.size(); k++);

            if (k != topN.size()) {
                for (int j = topN.size() - 1; j > k; j--) topN[j] = topN[j - 1];
                topN[k] = currentVal;
            }

            currentVal = 0;
        }
    }

    std::cout << std::reduce(topN.begin(), topN.end()) << std::endl;
}

int main() {
    std::vector<std::optional<int>> ints;
    readIntegerLines("day1/input.txt", ints);
    if (ints[ints.size() - 1])
        ints.push_back(std::nullopt);
    partOne(ints);
    partTwo(ints);
    
    return 0;
}
