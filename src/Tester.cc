#include "Tester.hh"

void Tester::launch(int& choice) {
  switch(choice) {
    case 1:
      bookTester.printAllBooks();
      break;
    case 2: 
      bookTester.compareBooks();
      break;
    case 3:
      bookTester.testAllCriteria();
      break;
    case 4:
      libraryTester.testGetterFunctions();
      break;
    case 5: 
      libraryTester.testAddFunctions();
      break;
    case 6:
      libraryTester.testRemoveFunctions();
      break;
    case 7:
      libraryTester.testRetrievalFunctions();
      break;
    case 8:
      libraryTester.testSortFunctions();
      break;
    case 9:
      bookTester.launch();
      libraryTester.launch();
      break;
    case 10:
      cout << "You have selected to exit the tester. You will be redirected to the main menu." << endl;
      break;
  }
} 