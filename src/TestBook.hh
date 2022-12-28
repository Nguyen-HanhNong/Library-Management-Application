#ifndef TESTBOOK_HPP
#define TESTBOOK_HPP

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <random>

#include "Book.hh"
#include "Criteria.hh"

using namespace std;

#define NUM_ATTEMPTS_PER_TEST 5

class TestBook {
	public:
		TestBook();
		~TestBook();
		void launch();

	private:
		void initFromFile();

		void printAllBooks() const;
		void compareBooks() const;

		/* Test all criteria for the books */
		void testAllCriteria() const;
		
		void testTitleCriteria() const;
		void testAuthorCriteria() const;
		void testGenreCriteria() const;
		void testSubgenreCriteria() const;
		void testPublisherCriteria() const;
		void testPageCountCriteria() const;

		const int getRandomizedIndex() const;

		vector<Book*> bookVector;

};
#endif