#ifndef TESTLIBRARY_HPP
#define TESTLIBRARY_HPP

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <random>

#include "Library.hh"

using namespace std;

class TestLibrary {
	public:
		TestLibrary();
		~TestLibrary();
		void launch();

	private:
		void initLibraryFromFile(Library& library);

		void printAllBooks() const;
		void compareBooks() const;

		void testAllCriteria() const;
		void testTitleCriteria() const;
		void testAuthorCriteria() const;
		void testGenreCriteria() const;
		void testSubgenreCriteria() const;
		void testPublisherCriteria() const;
		void testPageCountCriteria() const;

		const int getRandomizedIndex() const;

		vector<Book*> bookVector;
    Library library;
};
#endif