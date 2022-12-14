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

#define DAY 13

struct Inputs {
};

void readInput(int day, Inputs& out) {
  std::ifstream istream;

  istream.open(aoc_utils::getFileNameFromDay(day), std::ios::in);
  if (!istream.good()) {
    std::cerr << "Error while opening input file!" << std::endl;
    return;
  }
}

std::string partOne(Inputs& inputs) {
  return "";
}

std::string partTwo(Inputs& inputs) {
  return "";
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
