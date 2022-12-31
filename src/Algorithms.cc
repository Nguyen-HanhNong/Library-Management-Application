#include "Algorithms.hh"

// trim from start (in place)
void Algorithms::ltrim(std::string &s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
      return !std::isspace(ch);
  }));
}

// trim from end (in place)
void Algorithms::rtrim(std::string &s) {
  s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
      return !std::isspace(ch);
  }).base(), s.end());
}

// trim from both ends (in place)
void Algorithms::trim(std::string &s) {
  Algorithms::rtrim(s);
  Algorithms::ltrim(s);
}

// trim from start (copying)
std::string Algorithms::ltrim_copy(std::string s) {
  Algorithms::ltrim(s);
  return s;
}

// trim from end (copying)
std::string Algorithms::rtrim_copy(std::string s) {
  Algorithms::rtrim(s);
  return s;
}

// trim from both ends (copying)
std::string trim_copy(std::string s) {
  Algorithms::trim(s);
  return s;
}
