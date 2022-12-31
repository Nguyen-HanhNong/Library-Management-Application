#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <algorithm> 
#include <cctype>
#include <locale>
#include <string>

class Algorithms {
	public:
        static void ltrim(std::string &s);
        static void rtrim(std::string &s);
        static void trim(std::string &s);
        static std::string ltrim_copy(std::string s);
        static std::string rtrim_copy(std::string s);
        static std::string trim_copy(std::string s);
};

#endif