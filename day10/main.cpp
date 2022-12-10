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

#define DAY 10

enum class InstructionType { ADDX, NOOP };

struct Instruction {
  InstructionType type;
  int parameter;
};

struct Inputs {
  std::vector<Instruction> insts;
};

std::istream& operator>>(std::istream& istream, Instruction& i) {
  std::string s;
  istream >> s;

  if (s == "noop")
    i.type = InstructionType::NOOP;
  else
    i.type = InstructionType::ADDX;

  if (i.type == InstructionType::ADDX) {
    istream >> s;
    if (s.size() > 0) i.parameter = std::stoi(s);
  } else {
    i.parameter = 0;
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

  Instruction i;
  while (istream >> i) {
    out.insts.push_back(i);
  }
}

std::string partOne(const Inputs& inputs) {
  int x = 1;
  int i = 1;
  int sum = 0;
  for (const auto& ins : inputs.insts) {
    // start
    // mid
    if (i % 40 == 20) {
      sum += i * x;
    }
    if (ins.type == InstructionType::ADDX && (i + 1) % 40 == 20) {
      sum += (i + 1) * x;
    }

    // end
    x += ins.parameter;
    i += ins.type == InstructionType::ADDX ? 2 : 1;
  }

  return std::to_string(sum);
}

std::string partTwo(const Inputs& inputs) {
  int x = 1;
  int i = 1;
  std::stringstream sstream;
  sstream << "\n";
  for (const auto& ins : inputs.insts) {
    for (int k = 0; k < (ins.type == InstructionType::NOOP ? 1 : 2); k++) {
      // mid
      if (i - x <= 2 && i - x >= 0) {
        sstream << "#";
      } else {
        sstream << ".";
      }
      if (i == 40) {
        sstream << "\n";
        i = 1;
      } else {
        i++;
      }
    }

    // end
    x += ins.parameter;
  }

  return sstream.str();
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
