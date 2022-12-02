#include <fstream>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <string>
#include <optional>
#include <numeric>

struct Round {
    char opponentPlay;
    char myPlay;
};

std::istream& operator>>(std::istream& is, Round& obj)
{
    is >> obj.opponentPlay >> obj.myPlay;

    return is;
}

void readIntegerLines(const std::string& fileName, std::vector<Round>& out) {
    std::ifstream istream;

    istream.open(fileName, std::ios::in);
    if (!istream.good()) {
        std::cerr << "Error while opening input file!" << std::endl;
        return;
    }

    Round currRound;
    while (istream >> currRound) {
        out.push_back(currRound);
    }

    std::cout << "Read " << out.size() << " lines." << std::endl;
}

void partOne(const std::vector<Round>& rounds) {
    int score = 0;
    std::unordered_map<char, std::unordered_map<char, int>> scores;
    // mine is rock
    scores['X']['A'] = 1 + 3;
    scores['X']['B'] = 1 + 0;
    scores['X']['C'] = 1 + 6;

    // mine is paper
    scores['Y']['A'] = 2 + 6;
    scores['Y']['B'] = 2 + 3;
    scores['Y']['C'] = 2 + 0;

    // mine is scissors
    scores['Z']['A'] = 3 + 0;
    scores['Z']['B'] = 3 + 6;
    scores['Z']['C'] = 3 + 3;

    for (const auto& round: rounds) {
        score += scores[round.myPlay][round.opponentPlay];
    }

    std::cout << score << std::endl;
}

void partTwo(const std::vector<Round>& rounds) {
    int score = 0;
    std::unordered_map<char, std::unordered_map<char, int>> scores;
    // theirs is rock
    scores['A']['X'] = 3 + 0;
    scores['A']['Y'] = 1 + 3;
    scores['A']['Z'] = 2 + 6;

    // theirs is paper
    scores['B']['X'] = 1 + 0;
    scores['B']['Y'] = 2 + 3;
    scores['B']['Z'] = 3 + 6;

    // theirs is scissors
    scores['C']['X'] = 2 + 0;
    scores['C']['Y'] = 3 + 3;
    scores['C']['Z'] = 1 + 6;

    for (const auto& round: rounds) {
        score += scores[round.opponentPlay][round.myPlay];
    }

    std::cout << score << std::endl;
}

int main() {
    std::vector<Round> ints;
    readIntegerLines("day2/input.txt", ints);

    partOne(ints);
    partTwo(ints);

    return 0;
}
