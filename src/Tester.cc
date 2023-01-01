/* Tester.cc */
/* Author: Nguyen-Hanh Nong */
/* Revision: Revision 1.0 */
/* */
/* This is the source code file for the Tester class which contains the various classes involved with testing each of the component class including Book, Library and LibraryManager. */

/* Including the corresponding header file for the Tester class */
#include "Tester.hh"

/* Constructor for the Tester class */
Tester::Tester(): bookTester(new TestBook()), libraryTester(new TestLibrary()), libraryManagerTester(new TestLibraryManager())
{
}

/* Destructor for the Tester class */
Tester::~Tester() {
  delete bookTester;
  delete libraryTester;
  delete libraryManagerTester;
}

/* This function takes an integer and based on the integer, the tester class will choose a different functionality in the program to test */
void Tester::launch(int& choice) {
  switch(choice) {
    case 1:
      bookTester->printAllBooks();
      break;
    case 2: 
      bookTester->compareBooks();
      break;
    case 3:
      bookTester->testAllCriteria();
      break;
    case 4:
      libraryTester->testGetterFunctions();
      break;
    case 5: 
      libraryTester->testAddFunctions();
      break;
    case 6:
      libraryTester->testRemoveFunctions();
      break;
    case 7:
      libraryTester->testRetrievalFunctions();
      break;
    case 8:
      libraryTester->testSortFunctions();
      break;
    case 9:
      libraryManagerTester->testAddLibrary();
      break;
    case 10:
      libraryManagerTester->testRemoveLibrary();
      break;
    case 11:
      libraryManagerTester->testGetLibrary();
      break;
    case 12:
      libraryManagerTester->testAllPrintFunctions();
      break;
    case 13:
      libraryManagerTester->testMoveBook();
      break;
    case 14:
      bookTester->launch();
      libraryTester->launch();
      libraryManagerTester->launchAllTests();
      break;
    case 15:
      cout << "The program will now go back to the main menu." << endl;
      break;
  }
} 