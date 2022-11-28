#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> parse_line(std::string &line) {
  std::vector<std::string> res;
  size_t begin = 0, end = line.size() - 1;
  while ((end = line.find(',')) != std::string::npos) {
    res.push_back(line.substr(begin, end - begin));
    line = line.substr(end + 1);
  }
  res.push_back(line);
  return res;
}

int main(int argc, char const *argv[]) {
  std::ifstream file("./worldscene01.csv", std::ifstream::in);
  std::string line;
  std::getline(file, line);
  while (std::getline(file, line)) {
    std::cout << line << "\n";
    std::vector<std::string> vec = parse_line(line);
    for (auto s : vec)
      std::cout << s << "\n";
  }
  return 0;
}
