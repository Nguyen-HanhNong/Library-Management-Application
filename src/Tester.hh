#ifndef TESTER_HPP
#define TESTER_HPP

#include <iostream>
#include <string>
#include "TestBook.hh"
#include "TestLibrary.hh"

using namespace std;

class Tester {
		
	public:
		void launch();
	
	private:
		TestBook bookTester;
		TestLibrary libraryTester;
};
#endif