#include <fstream>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <string>
#include <optional>
#include <numeric>
#include <unordered_set>
#include <algorithm>

struct Rucksack {
    std::string firstPart;
    std::string secondPart;
    std::string rucksack;
};

std::istream& operator>>(std::istream& is, Rucksack& obj)
{
    is >> obj.rucksack;

    obj.firstPart = obj.rucksack.substr(0, obj.rucksack.size() / 2);
    obj.secondPart = obj.rucksack.substr(obj.rucksack.size() / 2, obj.rucksack.size());

    return is;
}

void readIntegerLines(const std::string& fileName, std::vector<Rucksack>& out) {
    std::ifstream istream;

    istream.open(fileName, std::ios::in);
    if (!istream.good()) {
        std::cerr << "Error while opening input file!" << std::endl;
        return;
    }

    Rucksack currRucksack;
    while (istream >> currRucksack) {
        out.push_back(currRucksack);
    }

    std::cout << "Read " << out.size() << " lines." << std::endl;
}

void partOne(const std::vector<Rucksack>& rucksacks) {
    int solution = 0;
    std::unordered_map<char, int> seenItems;

    for (const auto& rucksack : rucksacks) {
        seenItems = {};
        for (const char item: rucksack.firstPart) {
            seenItems[item] = 1;
        }
        for (const char item : rucksack.secondPart) {
            if (seenItems[item] == 1) {
                seenItems[item]++;
                solution += (item <= 90) ? item - 38 : item - 96;
            }
        }
    }

    std::cout << solution << std::endl;
}

void partTwo(const std::vector<Rucksack>& rucksacks) {
    int solution = 0;
    std::unordered_map<char, int> seenItems;
    std::unordered_map<char, int> localSeenItems;

    for (size_t i = 0; i < rucksacks.size(); i += 1) {
        if (i % 3 == 0) {
            seenItems.clear();
        }
        for (const char item : rucksacks[i].rucksack) {
            if (localSeenItems[item]++ == 0 && seenItems[item]++ == 2) {
                solution += (item <= 90) ? item - 38 : item - 96;
            }
        }
        localSeenItems.clear();
    }

    std::cout << solution << std::endl;
}

int main() {
    std::vector<Rucksack> ints;
    readIntegerLines("day3/input", ints);

    partOne(ints);
    partTwo(ints);

    return 0;
}
