#include "Algorithms.hh"

// trim from start (in place)
void Algorithms::ltrim(string &s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
      return !std::isspace(ch);
  }));
}

// trim from end (in place)
void Algorithms::rtrim(string &s) {
  s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
      return !std::isspace(ch);
  }).base(), s.end());
}

// trim from both ends (in place)
void Algorithms::trim(string &s) {
  Algorithms::rtrim(s);
  Algorithms::ltrim(s);
}

// trim from start (copying)
string Algorithms::ltrim_copy(string s) {
  Algorithms::ltrim(s);
  return s;
}

// trim from end (copying)
string Algorithms::rtrim_copy(string s) {
  Algorithms::rtrim(s);
  return s;
}

// trim from both ends (copying)
string Algorithms::trim_copy(string s) {
  Algorithms::trim(s);
  return s;
}

void Algorithms::sanitized_input(const string& question, string &response) {
  if(!question.empty()) {
    cout << question << endl;
  }

  while(true) {
    getline(cin, response);

    if (cin.fail()) {
      cerr << "Sorry, the input is invalid. Try again." << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      continue;
    }

    if(response.empty()) {
      cerr << "Sorry, your input has to have a value. Try again." << endl;
      continue;
    }

    Algorithms::trim(response);
    break;
  }
}