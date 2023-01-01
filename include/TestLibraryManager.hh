/* TestLibraryManager.hh */
/* Author: Nguyen-Hanh Nong */
/* Revision: Revision 1.0 */
/* */
/* This is the header file for the TestLibraryManager class which contains the functionality involving testing different functions in the LibraryManager class including adding and removing libraries and moving books between the libraries */

#ifndef TESTLIBRARYMANAGER_HPP
#define TESTLIBRARYMANAGER_HPP

// Including the necessary libraries and header files
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <random>

#include "LibraryManager.hh"
#include "Book.hh"

// Constant for the number of attempts per test (used in tests that involve randomization)
#define MAX_ATTEMPTS_PER_TEST 25

using namespace std;

/* TestLibraryManager class declaration */
class TestLibraryManager {
	public:
    /* Constructors and destructors */
		TestLibraryManager();
    ~TestLibraryManager();
    
    void launchAllTests(); //Launches all the tests

    void testAddLibrary(); //Tests the addLibrary() function
    void testRemoveLibrary(); //Tests the removeLibrary() function
    void testGetLibrary(); //Tests the getLibrary() function

    /* Test the print functions */
    void testAllPrintFunctions(); //Tests all the print functions in the LibraryManager class

    void testPrintLibraries(); //Tests the printLibraries() function
    void testPrintLibrary(); //Tests the printLibrary() function
    void testPrintLibraryBooks(); //Tests the printLibraryBooks() function

    void testMoveBook(); //Tests the moveBook() function

  private:
    LibraryManager* libraryManager; //Pointer to the LibraryManager object
};
#endif