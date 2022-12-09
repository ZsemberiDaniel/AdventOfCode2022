#include "main.h"

#include <algorithm>
#include <cmath>
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

#include "utils/utils.hpp"

#define DAY 9

enum class MoveType { UP, LEFT, RIGHT, DOWN };

struct Move {
  MoveType type;
  int amount;
};

struct Inputs {
  std::vector<Move> moves;
};

std::istream& operator>>(std::istream& istream, Move& move) {
  std::string s;
  istream >> s;
  if (s == "U")
    move.type = MoveType::UP;
  else if (s == "R")
    move.type = MoveType::RIGHT;
  else if (s == "L")
    move.type = MoveType::LEFT;
  else if (s == "D")
    move.type = MoveType::DOWN;

  istream >> s;
  if (s.size() > 0) move.amount = std::stoi(s);
  return istream;
}

void readInput(int day, Inputs& out) {
  std::ifstream istream;

  istream.open(aoc_utils::getFileNameFromDay(day), std::ios::in);
  if (!istream.good()) {
    std::cerr << "Error while opening input file!" << std::endl;
    return;
  }

  Move m;
  while (istream >> m) {
    out.moves.push_back(m);
  }
}

struct SimpleHash {
  size_t operator()(const std::pair<int, int>& p) const {
    return p.first * 10000 + p.second;
  }
};

std::string partOne(const Inputs& inputs) {
  std::pair<int, int> headPos(0, 0);
  std::pair<int, int> tailPos(0, 0);
  std::unordered_set<std::pair<int, int>, SimpleHash> visited;

  const int followMoves[5][5][2] = {
      {{0, 0}, {-1, -1}, {-1, 0}, {-1, 1}, {0, 0}},
      {{-1, -1}, {0, 0}, {0, 0}, {0, 0}, {-1, 1}},
      {{0, -1}, {0, 0}, {0, 0}, {0, 0}, {0, 1}},
      {{1, -1}, {0, 0}, {0, 0}, {0, 0}, {1, 1}},
      {{0, 0}, {1, -1}, {1, 0}, {1, 1}, {0, 0}},
  };

  for (const auto& move : inputs.moves) {
    for (int i = 0; i < move.amount; i++) {
      switch (move.type) {
        case MoveType::UP:
          headPos.first -= 1;
          break;
        case MoveType::DOWN:
          headPos.first += 1;
          break;
        case MoveType::LEFT:
          headPos.second -= 1;
          break;
        case MoveType::RIGHT:
          headPos.second += 1;
          break;
      }

      int d1 = headPos.first - tailPos.first + 2,
          d2 = headPos.second - tailPos.second + 2;
      tailPos.first += followMoves[d1][d2][0];
      tailPos.second += followMoves[d1][d2][1];
      visited.insert(tailPos);
    }
  }

  return std::to_string(visited.size());
}

std::string partTwo(const Inputs& inputs) {
  std::pair<int, int> headPos(0, 0);
  std::vector<std::pair<int, int>> tailPos(9);
  for (int i = 0; i < 9; i++) tailPos.push_back({0, 0});
  std::unordered_set<std::pair<int, int>, SimpleHash> visited;

  const int followMoves[5][5][2] = {
      {{-1, -1}, {-1, -1}, {-1, 0}, {-1, 1}, {-1, 1}},
      {{-1, -1}, {0, 0}, {0, 0}, {0, 0}, {-1, 1}},
      {{0, -1}, {0, 0}, {0, 0}, {0, 0}, {0, 1}},
      {{1, -1}, {0, 0}, {0, 0}, {0, 0}, {1, 1}},
      {{1, -1}, {1, -1}, {1, 0}, {1, 1}, {1, 1}},
  };

  for (const auto& move : inputs.moves) {
    for (int i = 0; i < move.amount; i++) {
      switch (move.type) {
        case MoveType::UP:
          headPos.first -= 1;
          break;
        case MoveType::DOWN:
          headPos.first += 1;
          break;
        case MoveType::LEFT:
          headPos.second -= 1;
          break;
        case MoveType::RIGHT:
          headPos.second += 1;
          break;
      }

      auto prev = headPos;
      for (int k = 0; k < 9; k++) {
        int d1 = prev.first - tailPos[k].first + 2,
            d2 = prev.second - tailPos[k].second + 2;
        tailPos[k].first += followMoves[d1][d2][0];
        tailPos[k].second += followMoves[d1][d2][1];

        prev = tailPos[k];
      }
      visited.insert(tailPos[8]);
    }
  }

  return std::to_string(visited.size());
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
