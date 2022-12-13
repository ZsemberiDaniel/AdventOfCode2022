#include "main.h"

#include <algorithm>
#include <cmath>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
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

#define DAY 12

struct Inputs {
  std::vector<std::vector<int>> heightMap;
  std::pair<int, int> startPos;
  std::pair<int, int> endPos;
};

void readInput(int day, Inputs& out) {
  std::ifstream istream;

  istream.open(aoc_utils::getFileNameFromDay(day), std::ios::in);
  if (!istream.good()) {
    std::cerr << "Error while opening input file!" << std::endl;
    return;
  }

  std::string line;
  int i = 0;
  while (std::getline(istream, line)) {
    out.heightMap.push_back({});
    int k = 0;

    for (char c : line) {
      if (c == 'E') {
        out.heightMap.back().push_back('z' - 'a');
        out.endPos = std::make_pair(i, k);
      } else if (c == 'S') {
        out.heightMap.back().push_back('a' - 'a');
        out.startPos = std::make_pair(i, k);
      } else {
        out.heightMap.back().push_back(c - 'a');
      }

      k++;
    }

    i++;
  }
}

using ListItem = std::tuple<int, int, int>;

std::string partOne(Inputs& inputs) {
  auto compare = [](ListItem a, ListItem b) {
    return std::get<0>(a) > std::get<0>(b);
  };
  std::vector<std::vector<bool>> isClosed(
      inputs.heightMap.size(),
      std::vector<bool>(inputs.heightMap[0].size(), false));

  std::priority_queue<ListItem, std::vector<ListItem>, decltype(compare)> queue(
      compare);
  queue.push(std::make_tuple(0, inputs.startPos.first, inputs.startPos.second));

  const int deltas[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
  int i = 0;
  while (!queue.empty()) {
    auto current = queue.top();
    queue.pop();
    if (std::get<1>(current) == inputs.endPos.first &&
        std::get<2>(current) == inputs.endPos.second) {
      return std::to_string(std::get<0>(current));
    }
    if (isClosed[std::get<1>(current)][std::get<2>(current)]) continue;

    isClosed[std::get<1>(current)][std::get<2>(current)] = true;
    int currentDist = std::get<0>(current);

    for (int dirI = 0; dirI < 4; dirI++) {
      std::size_t i = std::get<1>(current) + deltas[dirI][0],
                  k = std::get<2>(current) + deltas[dirI][1];

      if (i < 0 || i >= inputs.heightMap.size() || k < 0 ||
          k >= inputs.heightMap[0].size() || isClosed[i][k] ||
          inputs.heightMap[i][k] -
                  inputs.heightMap[std::get<1>(current)][std::get<2>(current)] >
              1) {
        continue;
      }

      queue.push(std::make_tuple(currentDist + 1, i, k));
    }
  }
  return "";
}

std::string partTwo(Inputs& inputs) {
  auto compare = [](ListItem a, ListItem b) {
    return std::get<0>(a) > std::get<0>(b);
  };
  std::vector<std::vector<int>> isClosed(
      inputs.heightMap.size(),
      std::vector<int>(inputs.heightMap[0].size(), -1));

  std::priority_queue<ListItem, std::vector<ListItem>, decltype(compare)> queue(
      compare);
  queue.push(std::make_tuple(0, inputs.endPos.first, inputs.endPos.second));

  const int deltas[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
  int i = 0;
  while (!queue.empty()) {
    auto current = queue.top();
    queue.pop();
    if (isClosed[std::get<1>(current)][std::get<2>(current)] != -1) continue;

    isClosed[std::get<1>(current)][std::get<2>(current)] = std::get<0>(current);
    int currentDist = std::get<0>(current);

    for (int dirI = 0; dirI < 4; dirI++) {
      std::size_t i = std::get<1>(current) + deltas[dirI][0],
                  k = std::get<2>(current) + deltas[dirI][1];

      if (i < 0 || i >= inputs.heightMap.size() || k < 0 ||
          k >= inputs.heightMap[0].size() || isClosed[i][k] != -1 ||
          inputs.heightMap[i][k] -
                  inputs.heightMap[std::get<1>(current)][std::get<2>(current)] <
              -1) {
        continue;
      }

      queue.push(std::make_tuple(currentDist + 1, i, k));
    }
  }

  int minForA = inputs.heightMap.size() * inputs.heightMap[0].size() + 1;
  for (std::size_t i = 0; i < isClosed.size(); i++) {
    for (std::size_t k = 0; k < isClosed[i].size(); k++) {
      if (inputs.heightMap[i][k] == 0 && isClosed[i][k] != -1 &&
          isClosed[i][k] < minForA) {
        minForA = isClosed[i][k];
      }
    }
  }

  return std::to_string(minForA);
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
