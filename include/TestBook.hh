/* TestBook.hh */
/* Author: Nguyen-Hanh Nong */
/* Revision: Revision 1.0 */
/* */
/* This is the header file for the TestBook class which contains the functionality involving testing different functions in the Book class including testing operator overloading and how different books match different criteria. */

#ifndef TESTBOOK_HPP
#define TESTBOOK_HPP

// Including the necessary libraries and header files
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <random>

#include "Book.hh"
#include "Criteria.hh"

using namespace std;

// Constant for the number of attempts per test (used in tests that involve randomization)
#define NUM_ATTEMPTS_PER_TEST 25

/* TestBook class declaration */
class TestBook {
	public:
		/* Constructors and destructors */
		TestBook();
		~TestBook();

		void launchAllTests(); //Launches the all the tests

		void initFromFile(); //Initializes the book vector from a file

		void printAllBooks(); //Prints all the books in the book vector
		void compareBooks(); //Compares various books against each other

		/* Test all criteria for the books */
		void testAllCriteria();
		
		void testTitleCriteria() const; //Tests the title criteria
		void testAuthorCriteria() const; //Tests the author criteria
		void testGenreCriteria() const; //Tests the genre criteria
		void testSubgenreCriteria() const; //Tests the subgenre criteria
		void testPublisherCriteria() const; //Tests the publisher criteria
		void testPageCountCriteria() const; //Tests the page count criteria

		const int getRandomizedIndex() const; //Returns a randomized index for the book vector

		void emptyBookVector(); //Empties the book vector
	private:
		vector<Book*>* bookVector; //Vector of book pointers

};
#endif