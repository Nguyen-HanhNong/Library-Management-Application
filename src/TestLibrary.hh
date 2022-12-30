#ifndef TESTLIBRARY_HPP
#define TESTLIBRARY_HPP

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <random>

#include "Library.hh"

#define MAX_ATTEMPTS_PER_TEST 25

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

		/* Tester get functions */
		void testGetFunctions();

		void testGetBookByCriteria();
		void testGetBooksByCriteria();
		void testGetBookBySeveralCriteria();
		void testGetBooksBySeveralCriteria();


		/* Test sorting functions */
		void testSortFunctions();

		void testSortByOrderAdded();
		void testSortByTitle();
		void testSortByAuthor();
		void testSortByGenre();
		void testSortBySubgenre();
		void testSortByPublisher();
		void testSortByPageCount();


		Library library;
		vector<Criteria> criteriaVector;
};
#endif