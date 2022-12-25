#ifndef TESTBOOK_HPP
#define TESTBOOK_HPP

#include <iostream>
#include <string>
#include <vector>
#include "Book.hh"
#include "Criteria.hh"

using namespace std;

class TestBook {
	public:
		void launch();
	
	private:
		void initFromFile();

		void printAllBooks();
		void compareBooks();

    vector<Book*> bookVector;
};
#endif