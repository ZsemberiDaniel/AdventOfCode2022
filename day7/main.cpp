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

#include "utils/utils.hpp"

#define DAY 7

struct FolderNode {
  std::string name;
  std::unordered_map<std::string, std::unique_ptr<struct FolderNode>> folders;
  int size;
  std::vector<std::pair<std::string, int>> files;
};

struct Inputs {
  FolderNode topFolder;
};

void readInput(int day, Inputs& out) {
  std::ifstream istream;

  istream.open(aoc_utils::getFileNameFromDay(day), std::ios::in);
  if (!istream.good()) {
    std::cerr << "Error while opening input file!" << std::endl;
    return;
  }

  out.topFolder.name = "/";
  out.topFolder.size = 0;
  std::vector<std::reference_wrapper<FolderNode>> folders;
  folders.push_back(out.topFolder);

  std::string line;
  std::getline(istream, line);

  bool lsOutput = false;

  while (std::getline(istream, line)) {
    // is a command
    if (line[0] == '$') {
      lsOutput = false;

      if (line[2] == 'l' && line[3] == 's') {
        // ls
        lsOutput = true;
        continue;
      } else if (line[2] == 'c' && line[3] == 'd') {
        // cd
        std::string folder = line.substr(5, line.size() - 5);
        if (folder == "..") {
          std::reference_wrapper<FolderNode> lastNode = folders.back();
          folders.pop_back();

          folders.back().get().size += lastNode.get().size;
        } else if (folder == "/") {
          throw "Cannot handle case where / is in an inner line";
        } else {
          folders.push_back(*folders.back().get().folders[folder]);
        }

        continue;
      }
    }

    // we are in lines that are the ls outputs
    if (lsOutput) {
      // dir is the prefix for the line
      if (line.rfind("dir", 0) == 0) {
        std::string folderName = line.substr(4, line.size() - 4);
        folders.back().get().folders[folderName] =
            std::make_unique<FolderNode>();
        folders.back().get().folders[folderName]->name = folderName;
      } else {
        size_t posOfSpace = line.find(" ");
        folders.back().get().files.push_back(std::make_pair(
            line.substr(posOfSpace + 1, line.size() - posOfSpace),
            std::stoi(line.substr(0, posOfSpace))));

        folders.back().get().size += folders.back().get().files.back().second;
      }
    }
  }

  while (folders.size() > 1) {
    std::reference_wrapper<FolderNode> lastNode = folders.back();
    folders.pop_back();

    folders.back().get().size += lastNode.get().size;
  }
}

int recurseInFilesystem(const FolderNode& currNode) {
  int size = currNode.size <= 100000 ? currNode.size : 0;

  for (const auto& folder: currNode.folders) {
    size += recurseInFilesystem(*folder.second);
  }

  return size;
}

std::string partOne(const Inputs& inputs) {
  return std::to_string(recurseInFilesystem(inputs.topFolder));
}

int recurseFindSmallestDir(int minSize, const FolderNode& currNode) {
  int min = currNode.size >= minSize ? currNode.size : 70000000;

  for (const auto& folder: currNode.folders) {
    min = std::min(min, recurseFindSmallestDir(minSize, *folder.second));
  }

  return min;
}

std::string partTwo(const Inputs& inputs) {
  int neededSpace = 30000000 - (70000000 - inputs.topFolder.size);
  return std::to_string(recurseFindSmallestDir(neededSpace, inputs.topFolder));
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
