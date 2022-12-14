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
#include <variant>
#include <vector>

#include "utils/utils.hpp"

#define DAY 13

struct Element {
  std::shared_ptr<struct Element> next;
  std::shared_ptr<struct Element> first;

  int value;
};

struct Inputs {
  std::shared_ptr<Element> first;
  std::shared_ptr<Element> second;
};

void printElement(const std::shared_ptr<Element>& e) {
  if (e == nullptr) {
    std::cout << "]";
    return;
  }

  if (e->value != -1) std::cout << e->value;
  if (e->first != nullptr) {
    std::cout << "[";
    printElement(e->first);
  }

  std::cout << ",";
  printElement(e->next);
}

void readInput(int day, Inputs& out) {
  std::ifstream istream;

  istream.open(aoc_utils::getFileNameFromDay(day), std::ios::in);
  if (!istream.good()) {
    std::cerr << "Error while opening input file!" << std::endl;
    return;
  }

  std::string line;
  int i = 0;

  while (istream >> line) {
    std::stringstream sstream(line);

    i++;
    std::shared_ptr<Element> currElement =
        std::make_shared<Element>(nullptr, nullptr, -1);
    std::stack<std::shared_ptr<Element>> es;
    int number = 0;
    for (char c; (c = sstream.get()) != EOF;) {
      if (c == ',') {
        currElement->value = number;
        currElement->next = std::make_shared<Element>(nullptr, nullptr, -1);
        currElement = currElement->next;
      } else if (c == '[') {
        currElement->first = std::make_shared<Element>(nullptr, nullptr, -1);
        es.push(currElement);
        currElement = currElement->first;
      } else if (c == ']') {
        es.pop();
        if (es.empty()) break;
        currElement = es.top();
      }

      if (c >= '0' && c <= '9') {
        number = number * 10 + (c - '0');
      } else {
        number = 0;
      }
    }

    printElement(currElement);
    std::cout << std::endl;
  }
}

std::string partOne(Inputs& inputs) { return ""; }

std::string partTwo(Inputs& inputs) { return ""; }

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
