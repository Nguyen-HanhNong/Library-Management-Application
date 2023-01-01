#include "TestLibraryManager.hh"

TestLibraryManager::TestLibraryManager(): libraryManager(new LibraryManager())
{
}

TestLibraryManager::~TestLibraryManager() {
  delete libraryManager;
}

void TestLibraryManager::launchAllTests() {
  testAddLibrary();
  testRemoveLibrary();
  testGetLibrary();

  testPrintLibraries();
  testPrintLibrary();
  testPrintLibraryBooks();

  testMoveBook();
}

void TestLibraryManager::testAllPrintFunctions() {
  testPrintLibraries();
  testPrintLibrary();
  testPrintLibraryBooks();
}

void TestLibraryManager::testAddLibrary() {
  cout << "Testing addLibrary()..." << endl;

  int attempts = 0;
  int success = 0;

  while(attempts < MAX_ATTEMPTS_PER_TEST) {
    Library *library = new Library("Library " + to_string(attempts));
    if(libraryManager->addLibrary(library)) {
      ++success;
    } else {
      cerr << "Error: Failed to add " << library->getName()  << " library when it should've been able to be added" << endl;
      exit(EXIT_FAILURE);
    }
    ++attempts;
  }

  if(success != MAX_ATTEMPTS_PER_TEST) {
    cerr << "Error: Number of successful attempts to add libraries is " << success << " when it should be " << MAX_ATTEMPTS_PER_TEST << endl;
    exit(EXIT_FAILURE);
  }

  libraryManager->clearAllLibraries();
  cout << "Test 1: Add Library function: PASSED" << endl;
}

void TestLibraryManager::testRemoveLibrary() {
  Library *library_1 = new Library("First Library");
  Library *library_2 = new Library("Second Library");
  Library *library_3 = new Library("Third Library");
  Library *library_4 = new Library("Fourth Library");

  if(libraryManager->removeLibrary(library_1)) {
    cerr << "Error: Attempted to remove " << library_1->getName() << " library when there are no libraries stored" << endl;
    exit(EXIT_FAILURE);
  }

  libraryManager->addLibrary(library_1);
  libraryManager->addLibrary(library_2);
  libraryManager->addLibrary(library_3);

  if(libraryManager->removeLibrary(library_4)) {
    cerr << "Error: Attempted to remove " << library_4->getName() << " library when it is not stored" << endl;
    exit(EXIT_FAILURE);
  }

  if(!libraryManager->removeLibrary(library_2)) {
    cerr << "Error: Failed to remove " << library_2->getName() << " library when it is stored" << endl;
    exit(EXIT_FAILURE);
  }

  if(libraryManager->getNumberOfLibraries() != 2) {
    cerr << "Error: Number of libraries stored is " << libraryManager->getNumberOfLibraries() << " when it should be 2" << endl;
    exit(EXIT_FAILURE);
  }

  if(!libraryManager->removeLibrary(library_1)) {
    cerr << "Error: Failed to remove " << library_1->getName() << " library when it is stored" << endl;
    exit(EXIT_FAILURE);
  }

  if(libraryManager->getNumberOfLibraries() != 1) {
    cerr << "Error: Number of libraries stored is " << libraryManager->getNumberOfLibraries() << " when it should be 1" << endl;
    exit(EXIT_FAILURE);
  }

  if(!libraryManager->removeLibrary(library_3)) {
    cerr << "Error: Failed to remove " << library_3->getName() << " library when it is stored" << endl;
    exit(EXIT_FAILURE);
  }

  if(libraryManager->getNumberOfLibraries() != 0) {
    cerr << "Error: Number of libraries stored is " << libraryManager->getNumberOfLibraries() << " when it should be 0" << endl;
    exit(EXIT_FAILURE);
  }

  delete library_4;
  libraryManager->clearAllLibraries();

  cout << "Test 2: Remove Library function: PASSED" << endl;
}

void TestLibraryManager::testGetLibrary() {
  Library *library_1 = new Library("First Library");
  Library *library_2 = new Library("Second Library");
  Library *library_3 = new Library("Third Library");

  Library *getLibrary;

  if(libraryManager->getLibrary("First Library", &getLibrary)) {
    cerr << "Error: Attempted to get " << library_1->getName() << " library when there are no libraries stored" << endl;
    exit(EXIT_FAILURE);
  }

  libraryManager->addLibrary(library_1);
  libraryManager->addLibrary(library_2);
  libraryManager->addLibrary(library_3);

  if(!libraryManager->getLibrary("First Library", &getLibrary)) {
    cerr << "Error: Failed to get " << library_1->getName() << " library when it is stored" << endl;
    exit(EXIT_FAILURE);
  }

  if(getLibrary->getName() != library_1->getName()) {
    cerr << "Error: Name of library returned is " << getLibrary->getName() << " when it should be " << library_1->getName() << endl;
    exit(EXIT_FAILURE);
  }

  if(!libraryManager->getLibrary("Second Library", &getLibrary)) {
    cerr << "Error: Failed to get " << library_2->getName() << " library when it is stored" << endl;
    exit(EXIT_FAILURE);
  }

  if(getLibrary->getName() != library_2->getName()) {
    cerr << "Error: Name of library returned is " << getLibrary->getName() << " when it should be " << library_2->getName() << endl;
    exit(EXIT_FAILURE);
  }

  libraryManager->removeLibrary(library_2);
  libraryManager->removeLibrary(library_1);

  if(libraryManager->getLibrary("First Library", &getLibrary)) {
    cerr << "Error: Attempted to get " << library_1->getName() << " library when it is not stored" << endl;
    exit(EXIT_FAILURE);
  }

  if(libraryManager->getLibrary("Second Library", &getLibrary)) {
    cerr << "Error: Attempted to get " << library_2->getName() << " library when it is not stored" << endl;
    exit(EXIT_FAILURE);
  }

  if(!libraryManager->getLibrary("Third Library", &getLibrary)) {
    cerr << "Error: Failed to get " << library_3->getName() << " library when it is stored" << endl;
    exit(EXIT_FAILURE);
  }

  libraryManager->clearAllLibraries();
  cout << "Test 3: Get Library function: PASSED" << endl;
}

void TestLibraryManager::testPrintLibraries() {
  cout << "Trying to print library manager with no libraries in them." << endl;
  libraryManager->printLibraries();

  Library *library_1 = new Library("First Library");
  Library *library_2 = new Library("Second Library");
  Library *library_3 = new Library("Third Library");

  libraryManager->addLibrary(library_1);
  libraryManager->addLibrary(library_2);
  libraryManager->addLibrary(library_3);

  cout << "Trying to print library manager with libraries in them." << endl;
  libraryManager->printLibraries();

  libraryManager->clearAllLibraries();
  cout << "Test 4: Print Libraries function: PASSED" << endl;
}

void TestLibraryManager::testPrintLibrary() {
  Library* library_1 = new Library("First Library");
  Library* library_2 = new Library("Second Library");

  cout << "Trying to print library that is not in the library manager." << endl;
  libraryManager->printLibrary(library_1->getName());

  libraryManager->addLibrary(library_1);

  cout << "Trying to print library that is in the library manager." << endl;
  libraryManager->printLibrary(library_1->getName());

  libraryManager->addLibrary(library_2);

  cout << "Trying to print the 2nd library that is in the library manager." << endl;
  libraryManager->printLibrary(library_2->getName());

  libraryManager->clearAllLibraries();

  cout << "Test 5: Print Library function: PASSED" << endl;
}

void TestLibraryManager::testPrintLibraryBooks() {
  Library *library_1 = new Library("First Library");

  cout << "Trying to print books in library that is not in the library manager." << endl;
  libraryManager->printLibraryBooks(library_1->getName());

  libraryManager->addLibrary(library_1);

  cout << "Trying to print books that do not exist in library that is in the library manager." << endl;
  libraryManager->printLibraryBooks(library_1->getName());

  Book *book_1 = new Book("First Book", "First Author");
  Book *book_2 = new Book("Second Book", "Second Author");
  Book *book_3 = new Book("Third Book", "Third Author");
  
  library_1->addBook(book_1);
  library_1->addBook(book_2);
  library_1->addBook(book_3);

  cout << "Trying to print books that exist in library that is in the library manager." << endl;
  libraryManager->printLibraryBooks(library_1->getName());

  libraryManager->clearAllLibraries();

  cout << "Test 6: Print Library Books function: PASSED" << endl;
}

void TestLibraryManager::testMoveBook() {
  Library *library_1 = new Library("First Library");
  Library *library_2 = new Library("Second Library");
  Library *library_3 = new Library("Third Library");

  Book *book_1 = new Book("First Book", "First Author");
  Book *book_2 = new Book("Second Book", "Second Author");
  Book *book_3 = new Book("Third Book", "Third Author");

  library_1->addBook(book_1);
  library_1->addBook(book_2);
  library_1->addBook(book_3);

  libraryManager->addLibrary(library_1);
  libraryManager->addLibrary(library_2);
  libraryManager->addLibrary(library_3);

  if(!libraryManager->moveBook("First Book", "First Library", "Second Library")) {
    cerr << "Error: Failed to move " << book_1->getTitle() << " book from " << library_1->getName() << " to " << library_2->getName() << endl;
    exit(EXIT_FAILURE);
  }

  if(!libraryManager->moveBook("Second Book", "First Library", "Second Library")) {
    cerr << "Error: Failed to move " << book_2->getTitle() << " book from " << library_1->getName() << " to " << library_2->getName() << endl;
    exit(EXIT_FAILURE);
  }

  if(!libraryManager->moveBook("Third Book", "First Library", "Second Library")) {
    cerr << "Error: Failed to move " << book_3->getTitle() << " book from " << library_1->getName() << " to " << library_2->getName() << endl;
    exit(EXIT_FAILURE);
  }

  library_2->printOnlyBooks(cout);

  if(libraryManager->moveBook("First Book", "First Library", "Second Library")) {
    cerr << "Error: Attempted to move " << book_1->getTitle() << " book from " << library_1->getName() << " to " << library_2->getName() << " when it is not in " << library_1->getName() << endl;
    exit(EXIT_FAILURE);
  }

  if(!libraryManager->moveBook("First Book", "Second Library", "Third Library")) {
    cerr << "Error: Failed to move " << book_1->getTitle() << " book from " << library_2->getName() << " to " << library_3->getName() << endl;
    exit(EXIT_FAILURE);
  }

  library_2->printOnlyBooks(cout);
  library_3->printOnlyBooks(cout);

  libraryManager->clearAllLibraries();

  cout << "Test 7: Move Book function: PASSED" << endl;
}