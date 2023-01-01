/* TestLibrary.hh */
/* Author: Nguyen-Hanh Nong */
/* Revision: Revision 1.0 */
/* */
/* This is the header file for the TestLibrary class which contains the functionality involving testing different functions in the Library class including adding and removing books from the Library, sorting the books in a library and retrieving books from a Library. */

#ifndef TESTLIBRARY_HPP
#define TESTLIBRARY_HPP

// Including the necessary libraries and header files
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <random>

#include "Library.hh"

// Constant for the number of attempts per test (used in tests that involve randomization)
#define MAX_ATTEMPTS_PER_TEST 25

using namespace std;

/* TestLibrary class declaration */
class TestLibrary {
	public:
		/* Constructors and destructors */
		TestLibrary();
		~TestLibrary();

		void launchAllTests(); //Launches the all the tests

		void initLibraryFromFile(Library& library); //Initializes the library from a file
		const int getRandomizedIndex() const; //Returns a randomized index for the books stored in the library

		/* Testing getter functions in Library class */
		void testGetterFunctions(); //Tests all the getter functions in the Library class
	
		void testGetBooks(); //Tests the getBooks() function
		void testGetNextBookID(); //Tests the getNextBookID() function
		void testGetName(); //Tests the getName() function
		void testGetAddress(); //Tests the getAddress() function

		/* Testing add functions */
		void testAddFunctions(); //Test the add functions and matchibngBooks() function in the Library class

		void testMatchingBooks(); //Tests the matching books behaviour in the addBooks function
		void testAddBooks(); //Tests the addBooks() function

		/* Testing remove functions */
		void testRemoveFunctions(); //Tests all the remove functions in the Library class

		void testRemoveBook(); //Tests the removeBook() function
		void testRemoveBookByCriteria(); //Tests the removeBookByCriteria() function
		void testRemoveBookBySeveralCriteria(); //Tests the removeBookBySeveralCriteria() function

		/* Tester book retrieval functions */
		void testRetrievalFunctions(); //Tests all the retrieval functions in the Library class

		void testGetBookByCriteria(); //Tests the getBookByCriteria() function
		void testGetBooksByCriteria(); //Tests the getBooksByCriteria() function
		void testGetBookBySeveralCriteria(); //Tests the getBookBySeveralCriteria() function
		void testGetBooksBySeveralCriteria(); //Tests the getBooksBySeveralCriteria() function

		/* Test sorting functions */
		void testSortFunctions(); //Tests all the sorting functions in the Library class

		void testSortByOrderAdded(); //Tests the sortByOrderAdded() function
		void testSortByTitle(); //Tests the sortByTitle() function
		void testSortByAuthor(); //Tests the sortByAuthor() function
		void testSortByGenre(); //Tests the sortByGenre() function
		void testSortBySubgenre(); //Tests the sortBySubgenre() function
		void testSortByPublisher(); //Tests the sortByPublisher() function
		void testSortByPageCount(); //Tests the sortByPageCount() function

	private:
		Library library; //Library object
		vector<Criteria> criteriaVector; //Vector of criteria objects
};
#endif