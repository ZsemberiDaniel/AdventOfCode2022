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
#include <regex>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "utils/utils.hpp"

#define DAY 11

struct Monkey {
  int index;
  std::deque<std::uint64_t> items;
  int divisor;
  int whenTrue;
  int whenFalse;
  std::function<std::uint64_t(std::uint64_t)> inspect;
};

struct Inputs {
  std::vector<Monkey> monkeys;
};

std::istream& operator>>(std::istream& istream, Monkey& monkey) {
  if (istream.peek() == EOF) {
    istream.setstate(std::ios::failbit);
    return istream;
  }

  std::string line;
  do {
    std::getline(istream, line);
  } while (line.find("Monkey") == std::string::npos);
  monkey.index = line[line.size() - 2] - '0';

  std::getline(istream, line);
  std::stringstream sstream(line.substr(18, line.size() - 18));
  std::string segment;
  monkey.items.clear();
  while (std::getline(sstream, segment, ',')) {
    monkey.items.push_back(std::stoi(segment));
  }

  std::getline(istream, line);
  std::string otherParticipant = line.substr(25, line.size() - 25);
  if (otherParticipant == "old") {
    if (line.find("*") != std::string::npos) {
      monkey.inspect = [](std::uint64_t old) { return old * old; };
    } else {
      monkey.inspect = [](std::uint64_t old) { return old + old; };
    }

  } else {
    std::uint64_t operationNmb = std::stoi(otherParticipant);
    if (line.find("*") != std::string::npos) {
      monkey.inspect = [operationNmb](std::uint64_t old) {
        return old * operationNmb;
      };
    } else {
      monkey.inspect = [operationNmb](std::uint64_t old) {
        return old + operationNmb;
      };
    }
  }

  std::getline(istream, line);
  monkey.divisor = std::stoi(line.substr(21, line.size() - 21));

  std::getline(istream, line);
  monkey.whenTrue = std::stoi(line.substr(29, line.size() - 29));

  std::getline(istream, line);
  monkey.whenFalse = std::stoi(line.substr(30, line.size() - 30));

  return istream;
}

void readInput(int day, Inputs& out) {
  std::ifstream istream;

  istream.open(aoc_utils::getFileNameFromDay(day), std::ios::in);
  if (!istream.good()) {
    std::cerr << "Error while opening input file!" << std::endl;
    return;
  }

  Monkey m;
  while (istream >> m) {
    out.monkeys.push_back(m);
  }
}

std::string partOne(Inputs& inputs) {
  std::vector<int> inspections;
  inspections.resize(inputs.monkeys.size(), 0);

  for (int round = 1; round <= 20; round++) {
    for (auto& monkey : inputs.monkeys) {
      while (!monkey.items.empty()) {
        inspections[monkey.index]++;

        int item = monkey.items.front();
        monkey.items.pop_front();

        int newItem = monkey.inspect(item) / 3;
        int throwTo;
        if (newItem % monkey.divisor == 0) {
          throwTo = monkey.whenTrue;
        } else {
          throwTo = monkey.whenFalse;
        }

        inputs.monkeys[throwTo].items.push_back(newItem);
      }
    }
  }

  int maxE = inspections[0], secondMaxE = inspections[1];
  for (std::size_t i = 2; i < inspections.size(); i++) {
    if (inspections[i] > maxE) {
      secondMaxE = maxE;
      maxE = inspections[i];
    } else if (inspections[i] > secondMaxE) {
      secondMaxE = inspections[i];
    }
  }
  return std::to_string(maxE * secondMaxE);
}

std::string partTwo(Inputs& inputs) {
  std::vector<int> inspections;
  inspections.resize(inputs.monkeys.size(), 0);
  std::uint64_t divisor = 1;
  for (const auto& monkey : inputs.monkeys) {
    divisor *= monkey.divisor;
  }

  for (int round = 1; round <= 10000; round++) {
    for (auto& monkey : inputs.monkeys) {
      inspections[monkey.index] += monkey.items.size();

      while (!monkey.items.empty()) {
        std::uint64_t item = monkey.items.front();
        monkey.items.pop_front();

        std::uint64_t newItem = monkey.inspect(item) % divisor;
        int throwTo;
        if (newItem % monkey.divisor == 0) {
          throwTo = monkey.whenTrue;
        } else {
          throwTo = monkey.whenFalse;
        }

        inputs.monkeys[throwTo].items.push_back(newItem);
      }
    }
  }

  std::uint64_t maxE = inspections[0], secondMaxE = inspections[1];
  for (std::size_t i = 2; i < inspections.size(); i++) {
    if (inspections[i] > maxE) {
      secondMaxE = maxE;
      maxE = inspections[i];
    } else if (inspections[i] > secondMaxE) {
      secondMaxE = inspections[i];
    }
  }
  return std::to_string(maxE * secondMaxE);
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
