#include <bits/stdc++.h>

using namespace std;

bool isDigit(char &ch) { return isdigit(static_cast<unsigned char>(ch)); }
bool found(const string &input_line) {
  for (char ch : input_line) {
    if (isDigit(ch)) {
      return true;
    }
  }
  return false;
}
bool findWord(const string &input_line) {
  for (char ch : input_line) {
    if (isalnum(ch) || ch == '_') {
      return true;
    }
  }
  return false;
}
bool foundBraces(const string &input_line, const string &pattern) {
  unordered_map<char, int> mp;
  for (int i = 1; i < pattern.size() - 1; ++i) {
    mp[pattern[i]]++;
  }
  for (int j = 0; j < input_line.size(); ++j) {
    if (mp.find(input_line[j]) != mp.end()) {
      return true;
    }
  }
  return false;
}
bool match_pattern(const std::string &input_line, const std::string &pattern) {
  if (pattern.length() == 1) {
    return input_line.find(pattern) != std::string::npos;
  } else if (pattern == "\\d") {
    return found(input_line);
  } else if (pattern == "\\w") {
    return findWord(input_line);
  } else if (pattern[0] == '[' && pattern.back() == ']') {
    return foundBraces(input_line, pattern);
  } else {
    throw std::runtime_error("Unhandled pattern " + pattern);
  }
}

int main(int argc, char *argv[]) {
  // Flush after every std::cout / std::cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  // You can use print statements as follows for debugging, they'll be visible
  // when running tests.
  std::cerr << "Logs from your program will appear here" << std::endl;

  if (argc != 3) {
    std::cerr << "Expected two arguments" << std::endl;
    return 1;
  }

  std::string flag = argv[1];
  std::string pattern = argv[2];
  if (flag != "-E") {
    std::cerr << "Expected first argument to be '-E'" << std::endl;
    return 1;
  }

  /*Uncomment this block to pass the first stage*/

  std::string input_line;
  std::getline(std::cin, input_line);

  try {
    if (match_pattern(input_line, pattern)) {
      return 0;
    } else {
      return 1;
    }
  } catch (const std::runtime_error &e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
}
