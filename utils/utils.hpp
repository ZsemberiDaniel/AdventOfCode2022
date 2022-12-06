#pragma once
#include <json/json.h>

#include <fstream>
#include <string>
#include <vector>

namespace aoc_utils {

void submitAnswer(const int day, const int subExercise,
                  const std::string& answer) {
  std::ifstream file("secrets/config.json");
  Json::Value secretJson;
  if (!file.good()) {
    std::cout << "Cannot find secrets/config.json file" << std::endl;
    return;
  } else {
    file >> secretJson;
  }
  try {
    const std::string url =
        "https://adventofcode.com/2022/day/" + std::to_string(day) + "/answer";
    const std::string body =
        "level=" + std::to_string(subExercise) + "&answer=" + answer;
    const std::string cookie =
        "cookie: session=" + secretJson["session"].asString();
    const std::string command =
        R"(curl -o "day_response.json" -d ")" + body +
        R"(" -H "Content-Type: application/x-www-form-urlencoded" -H ")" +
        cookie + R"(" -X POST )" + url +
        R"( && (cat day_response.json | grep --silent "That's not the right answer." && echo 'Incorrect Answer!') && cat day_response.json | grep --silent "That's not the right answer." || echo 'Congratulations! Correct Answer!')";

    system(command.c_str());
  } catch (const std::exception& e) {
    std::cerr << "Request failed, error: " << e.what() << '\n';
  }
}

inline std::string getFileNameFromDay(const int day) {
  return "day" + std::to_string(day) + "/input";
}

template <typename T>
void readLines(const int day, std::ifstream& istream, std::vector<T>& out) {
  T currLine;
  while (istream >> currLine) {
    out.push_back(currLine);
  }

  std::cout << "Read " << out.size() << " lines." << std::endl;
}

template <typename T>
void readLines(const int day, std::vector<T>& out) {
  std::ifstream istream;

  istream.open(getFileNameFromDay(day), std::ios::in);
  if (!istream.good()) {
    std::cerr << "Error while opening input file!" << std::endl;
    return;
  }
  readLines(day, istream, out);
}
}  // namespace aoc_utils

