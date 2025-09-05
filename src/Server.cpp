#include <bits/stdc++.h>
using namespace std;

bool isDigit(const char &ch) { return isdigit(static_cast<unsigned char>(ch)); }
bool found(const string &input_line) {
  for (char ch : input_line) {
    if (isDigit(ch)) {
      return true;
    }
  }
  return false;
}
bool isAlpha(const char &ch) { return isalpha(static_cast<unsigned char>(ch)); }
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
bool foundNegativecharGroups(const string &input_line, const string &pattern) {
  unordered_map<char, int> mp;
  for (int i = 2; i < pattern.size() - 1; ++i) {
    mp[pattern[i]]++;
  }
  for (int i = 0; i < input_line.size(); ++i) {
    if (mp.find(input_line[i]) == mp.end()) {
      return true;
    }
  }
  return false;
}
bool findthem(const string &input_line, const string &pattern) {
  int ps = pattern.size();
  int i = 0, j = 0;
  while (j < input_line.size()) {
    if (i < ps && isDigit(input_line[j]) && pattern[i] == '\\' &&
        pattern[i + 1] == 'd') {
      i += 2;
      if (i == ps) {
        return true;
      }
    } else if (i < ps && isAlpha(input_line[j]) && pattern[i] == '\\' &&
               pattern[i + 1] == 'w') {
      i += 2;
      if (i == ps) {
        return true;
      }
    } else if (i < ps && input_line[j] == ' ' && pattern[i] == ' ') {
      i++;
      if (i == ps) {
        return true;
      }
    } else if (i < ps && input_line[j] == pattern[i]) {
      /*forgot this case*/
      i++;
      if (i == ps) {
        return true;
      }
    } else {
      i = 0;
    }
    j++;
  }
  return false;
}
bool containsThis(const string &pattern) {
  for (int i = 0; i < pattern.size(); ++i) {
    if (pattern[i] == '\\' && pattern[i + 1] == 'w') {
      return true;
    } else if (pattern[i] == '\\' && pattern[i + 1] == 'd') {
      return true;
    }
  }
  return false;
}
bool findAnchor(const string &pattern) {
  return pattern[0] == '^' && pattern.back() != '$';
}
bool onlystartofString(const string &input_line, const string &pattern) {
  int ps = pattern.size();
  if (input_line.size() < ps) {
    return false;
  }
  int i = 0, j = 1;
  while (j < ps && i < input_line.size()) {
    if (pattern[j] != input_line[i]) {
      return false;
    } else {
      i++;
      j++;
    }
  }
  return true;
}
bool findDollar(const string &pattern) {
  return pattern.back() == '$' && pattern[0] != '^';
}
bool onlyendofString(const string &input_line, const string &pattern) {
  int i = input_line.size() - 1, j = pattern.size() - 2;
  while (i >= 0 && j >= 0) {
    if (input_line[i] != pattern[j]) {
      return false;
    } else {
      i--;
      j--;
    }
  }
  return true;
}
bool foundDollarAnchor(const string &pattern) {
  return pattern[0] == '^' && pattern.back() == '$';
}
bool startandendofString(const string &input_line, const string &pattern) {
  string inter = pattern.substr(1, pattern.size() - 2);
  return input_line == inter;
}
bool foundPlus(const string &pattern) {
  for (const char ch : pattern) {
    if (ch == '+') {
      return true;
    }
  }
  return false;
}
bool handleMultiple(const string &input_line, const string &pattern) {
  int i = pattern.size() - 1, j = input_line.size() - 1;
  while (j >= 0) {
    if (input_line[j] == pattern[i]) {
      i--, j--;
    } else if (pattern[i] == '+') {
      i--;
      char req = pattern[i];
      while (input_line[j] == req && j >= 0) {
        j--;
      }
      i--;
      if (input_line[j] == pattern[i]) {
        i--, j--;
      } else {
        i = pattern.size() - 1, j--;
      }
    } else if (input_line[j] != pattern[i]) {
      i = pattern.size() - 1, j--;
    }
  }
  return i == -1;
}
bool foundQuestion(const string &pattern) {
  for (const char c : pattern) {
    if (c == '?') {
      return true;
    }
  }
  return false;
}
vector<int> zAlgo(string &g) {
  int gs = g.size();
  int l = 0, r = 0;
  vector<int> z(gs);
  for (int i = 1; i < gs; ++i) {
    if (i < r) {
      z[i] = min(z[i - l], r - i);
    }
    while (i + z[i] < gs && g[z[i]] == g[i + z[i]]) {
      z[i]++;
    }
    if (i + z[i] > r) {
      l = i;
      r = i + z[i];
    }
  }
  return z;
}
bool handleQuestionFromStart(const string &input_line, const string &pattern) {
  string F = "", S = "";
  int i = 0;
  while (i < pattern.size()) {
    if (i + 1 < pattern.size() && pattern[i + 1] == '?') {
      F += pattern[i];
      i += 2;
    } else {
      F += pattern[i];
      S += pattern[i];
      i++;
    }
  }
  int fs = F.size(), ss = S.size();
  /*goal is to find F in input_line, S in input_line.*/
  string newF = F + '$' + input_line;
  string newS = S + '$' + input_line;
  auto zF = zAlgo(newF), zS = zAlgo(newS);
  for (int e : zF) {
    if (e == fs) {
      return true;
    }
  }
  for (int e : zS) {
    if (e == ss) {
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
  } else if (pattern[0] == '[' && pattern.back() == ']' && pattern[1] != '^') {
    return foundBraces(input_line, pattern);
  } else if (pattern[0] == '[' && pattern.back() == ']' && pattern[1] == '^') {
    return foundNegativecharGroups(input_line, pattern);
  } else if (containsThis(pattern)) {
    return findthem(input_line, pattern);
  } else if (findAnchor(pattern)) {
    return onlystartofString(input_line, pattern);
  } else if (findDollar(pattern)) {
    return onlyendofString(input_line, pattern);
  } else if (foundDollarAnchor(pattern)) {
    return startandendofString(input_line, pattern);
  } else if (foundPlus(pattern)) {
    return handleMultiple(input_line, pattern);
  } else if (foundQuestion(pattern)) {
    return handleQuestionFromStart(input_line, pattern);
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
