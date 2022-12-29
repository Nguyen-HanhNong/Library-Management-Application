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
		const int getRandomizedIndex() const;

		/* Testing getter functions in Library class */
		void testGetterFunctions();
		
		void testGetBooks();
		void testGetNextBookID();
		void testGetName();
		void testGetAddress();

		/* Testing add functions */
		void testAddFunctions();

		void testMatchingBooks();
		void testAddBooks();

		/* Testing remove functions */
		void testRemoveFunctions();

		void testRemoveBook();
		void testRemoveBookByCriteria();
		void testRemoveBookBySeveralCriteria();

		Library library;
		vector<Criteria> criteriaVector;
};
#endif