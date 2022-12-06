#include "main.h"

#include <algorithm>
#include <fstream>
#include <iostream>
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

#define DAY 6

struct Inputs {
  std::string code;
};

void readInput(int day, Inputs& out) {
  std::ifstream istream;

  istream.open(aoc_utils::getFileNameFromDay(day), std::ios::in);
  if (!istream.good()) {
    std::cerr << "Error while opening input file!" << std::endl;
    return;
  }

  istream >> out.code;
}

std::string partOne(const Inputs& inputs) {
  const std::string& code = inputs.code;
  std::unordered_map<char, int> charCount;
  for (std::size_t i = 0; i < 4; i++) {
    if (charCount.contains(code[i])) {
      charCount[code[i]] += 1;
    } else {
      charCount[code[i]] = 1;
    }
  }

  for (std::size_t i = 4; i < code.size(); i++) {
    if (charCount.size() == 4) {
      return std::to_string(i);
    }

    if (charCount.contains(code[i])) {
      charCount[code[i]] += 1;
    } else {
      charCount[code[i]] = 1;
    }

    if (--charCount[code[i - 4]] == 0) {
      charCount.erase(code[i - 4]);
    }
  }

  return charCount.size() == 4 ? std::to_string(code.size() - 1)
                               : "NO SOLUTION";
}

std::string partTwo(const Inputs& inputs) {
  const std::string& code = inputs.code;
  std::unordered_map<char, int> charCount;
  const int distinct_size = 14;
  for (std::size_t i = 0; i < distinct_size; i++) {
    if (charCount.contains(code[i])) {
      charCount[code[i]] += 1;
    } else {
      charCount[code[i]] = 1;
    }
  }

  for (std::size_t i = distinct_size; i < code.size(); i++) {
    if (charCount.size() == distinct_size) {
      return std::to_string(i);
    }

    if (charCount.contains(code[i])) {
      charCount[code[i]] += 1;
    } else {
      charCount[code[i]] = 1;
    }

    if (--charCount[code[i - distinct_size]] == 0) {
      charCount.erase(code[i - distinct_size]);
    }
  }

  return charCount.size() == distinct_size ? std::to_string(code.size() - 1)
                               : "NO SOLUTION";
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
