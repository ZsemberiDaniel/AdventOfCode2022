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

typedef std::vector<std::stack<char>> Stacks;
struct Instruction {
  std::size_t from;
  std::size_t to;
  int amount;
};

std::istream& operator>>(std::istream& is, Instruction& obj) {
  std::regex rgx("move ([0-9]+) from ([0-9]+) to ([0-9]+)");
  std::smatch matches;
  std::string line;
  if (std::getline(is, line)) {
    if (std::regex_match(line, matches, rgx)) {
      obj.amount = std::stoi(matches[1]);
      obj.from = std::stoi(matches[2]);
      obj.to = std::stoi(matches[3]);
    } else {
      std::cout << "Regex didn't match " << line << std::endl;
    }
  }

  return is;
}

void readMixedLines(int day, Stacks& stacks, std::vector<Instruction>& out) {
  std::ifstream istream;

  istream.open(aoc_utils::getFileNameFromDay(day), std::ios::in);
  if (!istream.good()) {
    std::cerr << "Error while opening input file!" << std::endl;
    return;
  }

  std::string line = "non empty line";
  std::regex rgx("(\\[[A-Z]\\] |    )");
  std::smatch matches;

  std::vector<std::vector<char>> stacksReversed;
  stacksReversed.resize(9);
  while (std::getline(istream, line)) {
    if (!line.empty()) {
      line += " ";

      int index = 0;
      for (std::regex_iterator i =
               std::sregex_iterator(line.begin(), line.end(), rgx);
           i != std::sregex_iterator(); i++, index++) {
        std::string matchStr = (*i).str();

        if (matchStr[1] != ' ') {
          stacksReversed[index].push_back(matchStr[1]);
        }
      }
    } else {
      break;
    }
  }

  stacks.resize(stacksReversed.size());
  for (std::size_t i = 0; i < stacksReversed.size(); i++) {
    for (auto item = stacksReversed[i].rbegin();
         item != stacksReversed[i].rend(); item++) {
      stacks[i].push(*item);
    }
  }

  aoc_utils::readLines(day, istream, out);
}

void partOne(Stacks& stacks, const std::vector<Instruction>& instructions) {}

void partTwo(Stacks& stacks, const std::vector<Instruction>& instructions) {}

int main(int argc, char* argv[]) {
  std::vector<Instruction> instructions;
  Stacks stacks;
  // readMixedLines(5, stacks, instructions);

  if (argc > 1 && std::strcmp(argv[1], "submit")) {
    aoc_utils::submitAnswer(5, 1, "answer");
  } else {
    // TODO
  }

  return 0;
}
