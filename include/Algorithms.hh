#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <algorithm> 
#include <cctype>
#include <locale>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

class Algorithms {
	public:
    static void ltrim(string &s);
    static void rtrim(string &s);
    static void trim(string &s);
    static string ltrim_copy(string s);
    static string rtrim_copy(string s);
    static string trim_copy(string s);
    static void sanitized_input(const string& question, string &response);
};

#endif