#include "main.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <numeric>
#include <optional>
#include <regex>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include <cmath>

#include "utils/utils.hpp"

#define DAY 8

struct Inputs {
  std::vector<std::vector<int>> map;
};

void readInput(int day, Inputs& out) {
  std::ifstream istream;

  istream.open(aoc_utils::getFileNameFromDay(day), std::ios::in);
  if (!istream.good()) {
    std::cerr << "Error while opening input file!" << std::endl;
    return;
  }

  std::string line;
  while (std::getline(istream, line)) {
    out.map.push_back({});

    for (const auto c : line) {
      out.map.back().push_back(c - '0');
    }
  }

  std::cout << "Read map (n=" << out.map.size()
            << ", m=" << out.map.front().size() << ")" << std::endl;
}

void calculateFromSide(const std::vector<std::vector<int>>& map,
                       std::vector<std::vector<int>>& isVisible, bool row,
                       int delta) {
  for (std::size_t i = 0; i < map.size(); i++) {
    std::size_t index = delta == 1 ? 0 : map.size() - 1;
    int max = -1;

    std::size_t i1 = row ? i : index;
    std::size_t i2 = row ? index : i;

    while (i1 < map.size() && i2 < map.size() && map[i1][i2] != 9) {
      if (isVisible[i1][i2] != -1)
        isVisible[i1][i2] = map[i1][i2] > max ? -1 : -2;
      max = std::max(map[i1][i2], max);

      if (row)
        i2 += delta;
      else
        i1 += delta;
    }
    if (i1 < map.size() && i2 < map.size()) isVisible[i1][i2] = -1;
  }
}

std::string partOne(const Inputs& inputs) {
  std::vector<std::vector<int>> isVisible = inputs.map;
  calculateFromSide(inputs.map, isVisible, true, 1);
  calculateFromSide(inputs.map, isVisible, true, -1);
  calculateFromSide(inputs.map, isVisible, false, 1);
  calculateFromSide(inputs.map, isVisible, false, -1);

  int count = 0;
  for (std::size_t i = 0; i < isVisible.size(); i++) {
    for (std::size_t k = 0; k < isVisible[i].size(); k++) {
      count += isVisible[i][k] == -1;
    }
  }

  return std::to_string(count);
}

int calculateFromSide(const std::vector<std::vector<int>>& map, int dN, int dM,
                      int n, int m, int maxHeight) {
  int max = -1;
  int seen = 0;

  std::size_t i1 = n + dN;
  std::size_t i2 = m + dM;

  while (i1 > 0 && i2 > 0 && i1 < map.size() - 1 && i2 < map.size() - 1 &&
         map[i1][i2] < maxHeight) {
    if (map[i1][i2] >= max) {
      seen++;
      max = map[i1][i2];
    }

    i1 += dN;
    i2 += dM;
  }
  return std::abs((int)i1 - n) + std::abs((int)i2 - m);
}

int scenicValue(const std::vector<std::vector<int>>& map, int n, int m) {
  return calculateFromSide(map, 1, 0, n, m, map[n][m]) *
         calculateFromSide(map, -1, 0, n, m, map[n][m]) *
         calculateFromSide(map, 0, 1, n, m, map[n][m]) *
         calculateFromSide(map, 0, -1, n, m, map[n][m]);
}

std::string partTwo(const Inputs& inputs) {
  int maxVal = -1;

  for (std::size_t i = 1; i < inputs.map.size() - 1; i++) {
    for (std::size_t k = 1; k < inputs.map[i].size() - 1; k++) {
      maxVal = std::max(maxVal, scenicValue(inputs.map, i, k));
    }
  }

  return std::to_string(maxVal);
}

int main(int argc, char* argv[]) {
  Inputs inputs;
  readInput(DAY, inputs);

  std::string answer1 = partOne(inputs), answer2 = partTwo(inputs);
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
