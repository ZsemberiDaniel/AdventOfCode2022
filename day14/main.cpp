#include "main.h"

#include <algorithm>
#include <cmath>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <limits>
#include <memory>
#include <numeric>
#include <optional>
#include <queue>
#include <regex>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "utils/utils.hpp"

#define DAY 14

struct SandLine {
  std::vector<std::pair<int, int>> coords;
};

struct Inputs {
  std::vector<SandLine> sandLines;
  std::pair<int, int> minCoords;
  std::pair<int, int> maxCoords;
  std::vector<std::vector<int>> map;
};

std::istream& operator>>(std::istream& istream, SandLine& sandLine) {
  std::string line;
  std::getline(istream, line);

  if (line.size() > 0) {
    std::stringstream sstream(line);
    std::string coords;
    while (std::getline(sstream, coords, ' ')) {
      std::size_t commaAt = coords.find(",");
      sandLine.coords.push_back(std::make_pair(
          std::stoi(coords.substr(0, commaAt)),
          std::stoi(coords.substr(commaAt + 1, coords.size() - commaAt))));
      std::getline(sstream, coords, ' ');
    }
  }

  return istream;
}

void readInput(int day, Inputs& out) {
  std::ifstream istream;

  istream.open(aoc_utils::getFileNameFromDay(day), std::ios::in);
  if (!istream.good()) {
    std::cerr << "Error while opening input file!" << std::endl;
    return;
  }

  SandLine sl;
  while (istream >> sl) {
    out.sandLines.push_back(sl);
    sl.coords.clear();
  }

  out.minCoords.first = std::numeric_limits<int>::max();
  out.minCoords.second = 0;
  out.maxCoords.first = std::numeric_limits<int>::min();
  out.maxCoords.second = std::numeric_limits<int>::min();

  for (std::size_t i = 0; i < out.sandLines.size(); i++) {
    for (const auto& p : out.sandLines[i].coords) {
      if (p.first < out.minCoords.first) out.minCoords.first = p.first;
      if (p.first > out.maxCoords.first) out.maxCoords.first = p.first;

      if (p.second > out.maxCoords.second) out.maxCoords.second = p.second;
    }
  }

  out.map = std::vector<std::vector<int>>(
      out.maxCoords.first - out.minCoords.first + 1,
      std::vector<int>(out.maxCoords.second - out.minCoords.second + 1, 0));

  for (std::size_t i = 0; i < out.sandLines.size(); i++) {
    for (std::size_t k = 1; k < out.sandLines[i].coords.size(); k++) {
      int c1 = out.sandLines[i].coords[k].first - out.minCoords.first;
      int c2 = out.sandLines[i].coords[k].second - out.minCoords.second;

      int b1 = out.sandLines[i].coords[k - 1].first - out.minCoords.first;
      int b2 = out.sandLines[i].coords[k - 1].second - out.minCoords.second;

      int d1 = c1 > b1 ? 1 : -1;
      int d2 = c2 > b2 ? 1 : -1;

      for (int j = b1; (c1 > b1 && j <= c1) || (c1 < b1 && j >= c1) ||
                       (c1 == b1 && j == c1);
           j += d1) {
        for (int l = b2; (c2 > b2 && l <= c2) || (c2 < b2 && l >= c2) ||
                         (c2 == b2 && l == c2);
             l += d2) {
          out.map[j][l] = 5;
        }
      }
    }
  }

  for (std::size_t i = 0; i < out.map[0].size(); i++) {
    for (std::size_t k = 0; k < out.map.size(); k++) {
      std::cout << (out.map[k][i] == 5 ? "#" : " ");
    }

    std::cout << std::endl;
  }
}

std::string partOne(Inputs& inputs) {
  int n = inputs.map.size(), m = inputs.map[0].size();
  std::pair<int, int> initialSandPos =
      std::make_pair(500 - inputs.minCoords.first, 0);
  std::pair<int, int> currentSandPos = initialSandPos;
  int answer = 0;
  while (true) {
    const std::pair<int, int> newSandPos1 =
        std::make_pair(currentSandPos.first, currentSandPos.second + 1);
    const bool outOfBounds1 = newSandPos1.first < 0 || newSandPos1.second < 0 ||
                              newSandPos1.first >= n || newSandPos1.second >= m;
    const std::pair<int, int> newSandPos2 =
        std::make_pair(currentSandPos.first - 1, currentSandPos.second + 1);
    const bool outOfBounds2 = newSandPos2.first < 0 || newSandPos2.second < 0 ||
                              newSandPos2.first >= n || newSandPos2.second >= m;
    const std::pair<int, int> newSandPos3 =
        std::make_pair(currentSandPos.first + 1, currentSandPos.second + 1);
    const bool outOfBounds3 = newSandPos3.first < 0 || newSandPos3.second < 0 ||
                              newSandPos3.first >= n || newSandPos3.second >= m;

    if (!outOfBounds1 &&
        inputs.map[newSandPos1.first][newSandPos1.second] == 0) {
      currentSandPos = newSandPos1;
    } else if (!outOfBounds2 &&
               inputs.map[newSandPos2.first][newSandPos2.second] == 0) {
      currentSandPos = newSandPos2;
    } else if (!outOfBounds3 &&
               inputs.map[newSandPos3.first][newSandPos3.second] == 0) {
      currentSandPos = newSandPos3;
    } else if (outOfBounds1 || outOfBounds2 || outOfBounds3) {
      break;
    } else {
      inputs.map[currentSandPos.first][currentSandPos.second] = 3;
      currentSandPos = initialSandPos;
      answer++;
    }
  }

  return std::to_string(answer);
}

std::string partTwo(Inputs& inputs) {
  for (std::size_t i = 0; i < inputs.map.size(); i++) {
    inputs.map[i].push_back(0);
    inputs.map[i].push_back(5);
  }
  inputs.maxCoords.second += 2;

  int newSandCount = (inputs.maxCoords.second - inputs.minCoords.second + 1);
  for (int i = 0; i < newSandCount; i++) {
    inputs.map.push_back(std::vector<int>(inputs.map[0].size()));
    inputs.map.back().back() = 5;

    inputs.map.insert(inputs.map.begin(), std::vector<int>(inputs.map[0].size()));
    inputs.map.front().back() = 5;

    inputs.minCoords.first--;
    inputs.maxCoords.first++;
  }

  int n = inputs.map.size(), m = inputs.map[0].size();
  std::pair<int, int> initialSandPos =
      std::make_pair(500 - inputs.minCoords.first, 0);
  std::pair<int, int> currentSandPos = initialSandPos;
  int answer = 0;

  while (inputs.map[initialSandPos.first][initialSandPos.second] == 0) {
    const std::pair<int, int> newSandPos1 =
        std::make_pair(currentSandPos.first, currentSandPos.second + 1);
    const bool outOfBounds1 = newSandPos1.first < 0 || newSandPos1.second < 0 ||
                              newSandPos1.first >= n || newSandPos1.second >= m;
    const std::pair<int, int> newSandPos2 =
        std::make_pair(currentSandPos.first - 1, currentSandPos.second + 1);
    const bool outOfBounds2 = newSandPos2.first < 0 || newSandPos2.second < 0 ||
                              newSandPos2.first >= n || newSandPos2.second >= m;
    const std::pair<int, int> newSandPos3 =
        std::make_pair(currentSandPos.first + 1, currentSandPos.second + 1);
    const bool outOfBounds3 = newSandPos3.first < 0 || newSandPos3.second < 0 ||
                              newSandPos3.first >= n || newSandPos3.second >= m;

    if (!outOfBounds1 &&
        inputs.map[newSandPos1.first][newSandPos1.second] == 0) {
      currentSandPos = newSandPos1;
    } else if (!outOfBounds2 &&
               inputs.map[newSandPos2.first][newSandPos2.second] == 0) {
      currentSandPos = newSandPos2;
    } else if (!outOfBounds3 &&
               inputs.map[newSandPos3.first][newSandPos3.second] == 0) {
      currentSandPos = newSandPos3;
    } else {
      inputs.map[currentSandPos.first][currentSandPos.second] = 3;
      currentSandPos = initialSandPos;
      answer++;
    }
  }

  return std::to_string(answer);
}

int main(int argc, char* argv[]) {
  Inputs inputs;
  readInput(DAY, inputs);
  Inputs inputs2 = inputs;

  std::string answer1 = partOne(inputs), answer2 = partTwo(inputs2);
  if (argc > 1 && std::strcmp(argv[1], "submit1") == 0) {
    if (answer1.size() != 0) aoc_utils::submitAnswer(DAY, 1, answer1);
  } else if (argc > 1 && std::strcmp(argv[1], "submit2") == 0) {
    if (answer2.size() != 0) aoc_utils::submitAnswer(DAY, 2, answer2);
  } else {
    std::cout << "Answer 1: " << answer1 << std::endl;
    std::cout << "Answer 2: " << answer2 << std::endl;
  }

  return 0;
}
