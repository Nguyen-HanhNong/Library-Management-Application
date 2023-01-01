/* TestLibrary.cc */
/* Author: Nguyen-Hanh Nong */
/* Revision: Revision 1.0 */
/* */
/* This is the source file for the TestLibrary class which contains the functionality involving testing different functions in the Library class including adding and removing books from the Library, sorting the books in a library and retrieving books from a Library. */

/* Include Including the corresponding header file for the TestLibrary class */
#include "TestLibrary.hh"

/* Constructor for the TestLibrary class */
TestLibrary::TestLibrary(): library(Library("Test Library", Address("123 Test Street", "Test City", "Test Province", "12345"))) 
{
} 

/* Destructor for the TestLibrary class */
TestLibrary::~TestLibrary() {
  library.emptyLibrary(); // empty the library before the class is destroyed
}

/* This function launches all the tests for the Library class */
void TestLibrary::launchAllTests(){
  testGetterFunctions();  // test the getter functionss
  testAddFunctions();     // test the add functions
  testRemoveFunctions();  // test the remove functions
  testRetrievalFunctions(); // test the retrieval functionss
  testSortFunctions(); // test the sort functions

  cout << "SUCCESS: All Library tests passed" << endl << endl;
}

/* This function tests all the getter functions in the Library class */
void TestLibrary::testGetterFunctions() {
  testGetBooks(); // test the getBooks() function
  testGetNextBookID(); // test the getNextBookID() function
  testGetName(); // test the getName() function
  testGetAddress(); // test the getAddress() function

  cout << "SUCCESS: All getter functions passed" << endl << endl;
}

/* This function tests the matching books function and the add books function */
void TestLibrary::testAddFunctions() {
  testMatchingBooks(); // test the matching books functionality
  testAddBooks();      // test the addBooks() function

  cout << "SUCCESS: All adder functions passed" << endl << endl;
}

/* This function tests the remove functions in the Library class */
void TestLibrary::testRemoveFunctions() {
  testRemoveBook(); // test the removeBook() function

  /* Repeat the remove functions multiple times to ensure that the functions work properly since the functions tests are randomized */
  for (long unsigned int i = 0; i < MAX_ATTEMPTS_PER_TEST; ++i) {
    testRemoveBookByCriteria(); // test the removeBookByCriteria() function
    testRemoveBookBySeveralCriteria(); // test the removeBookBySeveralCriteria() function
  }

  cout << "SUCCESS: All remove functions passed" << endl << endl;
}

/* This function tests the retrieval functions in the Library class */
void TestLibrary::testRetrievalFunctions() {
  /* Repeat the retrieval functions multiple times to ensure that the functions work properly since the functions tests are randomized */
  for (long unsigned int i = 0; i < MAX_ATTEMPTS_PER_TEST; ++i) {
    testGetBookByCriteria(); // test the getBookByCriteria() functions
    testGetBooksByCriteria(); // test the getBooksByCriteria() functions
    testGetBookBySeveralCriteria(); // test the getBookBySeveralCriteria() functions
    testGetBooksBySeveralCriteria(); // test the getBooksBySeveralCriteria() functions
  }

  cout << "SUCCESS: All get books functions passed" << endl << endl;
}

/* This function tests the sorting functions in the Library class */
void TestLibrary::testSortFunctions() {
  testSortByTitle(); // test the sortByTitle() function
  testSortByAuthor(); // test the sortByAuthor() function
  testSortByGenre(); // test the sortByGenre() function
  testSortBySubgenre(); // test the sortBySubgenre() function
  testSortByPublisher(); // test the sortByPublisher() function
  testSortByPageCount(); // test the sortByPageCount() function

  cout << "SUCCESS: All sorting functions passed" << endl << endl;
}

/* This function initializes the library with books from a file */
void TestLibrary::initLibraryFromFile(Library& library) {
  library.emptyLibrary(); // empty the library before adding books

  string line; // line from the file
  string operatingSystem; // operating system of the computer
  string fileLocation; // file location of the file containing the books

  /* Get the operating system of the computer and depending on the operating system, set the file location to the correct file location */
  #ifdef _WIN32
    fileLocation = "..\save_files\tester\test_books.csv";
  #elif __linux__
    fileLocation = "../save_files/tester/test_books.csv";
  #elif __unix__
    fileLocation = "../save_files/tester/test_books.csv";
  #else
    cout << "Unidentified OS. This program does not currently handle this OS. The program will now exit";
    exit(EXIT_FAILURE);
  #endif

  ifstream file; // file stream
  file.open(fileLocation); // open the file

  /* If the file cannot be opened, print an error message and exit the program */
  if (!file.is_open()) {
    cerr << "The path given is incorrect for the tester file. Program will now exit" << endl;
    exit(EXIT_FAILURE);
  }

  getline(file, line); // skip the 1st line

  /* Read the file line by line and add the books to the library */
  while(getline(file,line)) {
    /* If the line is empty, skip it */
    if (line.empty()) {
      continue;
    }

    istringstream iss(line); // string stream
    string lineStream; // line from the file
    vector<string> currentLine; // current line from the file

    /* Read the line and add each of the properties of the book to the current line vector */
    while(getline(iss, lineStream, '|')) {
      currentLine.push_back(lineStream); 
    }
    
    /* If the current line does not have the correct number of properties, add the missing properties */
    if(currentLine.size() < NUM_BOOK_PROPERTIES) {
      currentLine.push_back("Unknown Publisher");
    }

    /* Add the book to the library */
    library.addBook(new Book(currentLine.at(0), currentLine.at(1), currentLine.at(2), currentLine.at(3), currentLine.at(5), stoi(currentLine.at(4)), library.getNextBookID()));
  }

  file.close(); // close the file
}

/* This function returns a random index from the library */
const int TestLibrary::getRandomizedIndex() const {
  std::random_device rd; // random number based on hardware
  std::mt19937 gen(rd()); // random number generator
  std::uniform_int_distribution<> distr(0, library.getBookCount() - 1); // random number distribution

  const int returnInteger = distr(gen); // random number within the indices of the library

  return returnInteger; // return the random number
}

/* This function tests the getBooks() function in the Library class */
void TestLibrary::testGetBooks() {
  initLibraryFromFile(library); // initialize the library with books from a file

  vector<Book *> books = library.getBooks(); // get the books from the library

  /* If the number of books in the library is not 10, print an error message and exit the program */
  if(books.size() != 10) {
    cerr << "Error: There should be 10 books in the library." << endl;
    exit(EXIT_FAILURE);
  }

  books.clear(); // clear the books vector
  cout << "Test 1: Get Books function: PASSED" << endl;
}

/* This function tests the getNextBookID() function in the Library class */
void TestLibrary::testGetNextBookID() {
  library.emptyLibrary(); // empty the library

  /* If the next book ID is not 0, print an error message and exit the program */
  if(library.getNextBookID() != 0) {
    cerr << "Error: The next book ID should be 0." << endl;
    exit(EXIT_FAILURE);
  }

  initLibraryFromFile(library); // initialize the library with books from a file

  int nextBookID = library.getNextBookID(); // get the next book ID
  int lastBookID = library.getBooks().back()->getID(); // get the last book ID in the library

  /* If the next book ID is not the last book ID + 1, print an error message and exit the program */
  if(nextBookID != lastBookID + 1) {
    cerr << "Error: The next book ID should be the last book ID + 1." << endl;
    exit(EXIT_FAILURE);
  }

  cout << "Test 2: Get Next Book ID function: Passed" << endl;
}

/* This function tests the getName() function in the Library class */
void TestLibrary::testGetName() {
  /* If the name of the current library is not "Test Library", print an error message and exit the program */
  if(library.getName() != "Test Library") {
    cerr << "Error: The name of the library should be Test Library." << endl;
    exit(EXIT_FAILURE);
  }

  /* Create one library and one default library */
  Library library2 = Library("Test Library 2", Address("123 Test Street", "Test City", "Test Province", "12345"));
  Library defaultLibrary = Library();

  /* If the name of the library is not "Test Library 2", print an error message and exit the program */
  if(library2.getName() != "Test Library 2") {
    cerr << "Error: The name of the library should be Test Library 2." << endl;
    exit(EXIT_FAILURE);
  }

  /* If the name of the default library is not "Unknown Library Name", print an error message and exit the program */
  if(defaultLibrary.getName() != "Unknown Library Name") {
    cerr << "Error: The name of the library should be Unknown Library." << endl;
    exit(EXIT_FAILURE);
  }

  cout << "Test 3: Get Name function: Passed" << endl;
}

/* This function tests the getAddress() function in the Library class */
void TestLibrary::testGetAddress() {
  /* Create an address and a default address */
  Address address = Address("123 Test Street", "Test City", "Test Province", "12345");
  Address defaultAddress = Address();

  /* Check if the address of the library is the same as the address, if not, print an error message and exit the program */
  if(library.getAddress() != address) {
    cerr << "Error: The address of the library should be 123 Test Street, Test City, Test Province, 12345." << endl;
    exit(EXIT_FAILURE);
  }
  /* Check if the street number of the default library is the same as the default address, if not, print an error message and exit the program */
  if(defaultAddress.getStreetNumber() != "Unknown Street Number") {
    cerr << "Error: The street number of the address should be Unknown Street Number." << endl;
    exit(EXIT_FAILURE);
  }
  /* Check if the street name of the default library is the same as the default address, if not, print an error message and exit the program */
  if(defaultAddress.getStreetName() != "Unknown Street") {
    cerr << "Error: The street of the address should be Unknown Street." << endl;
    exit(EXIT_FAILURE);
  }
  /* Check if the city name of the default library is the same as the default address, if not, print an error message and exit the program */
  if(defaultAddress.getCityName() != "Unknown City") {
    cerr << "Error: The city of the address should be Unknown City." << endl;
    exit(EXIT_FAILURE);
  }
  /* Check if the province name of the default library is the same as the default address, if not, print an error message and exit the program */
  if(defaultAddress.getProvinceName() != "Unknown Province") {
    cerr << "Error: The province of the address should be Unknown Province." << endl;
    exit(EXIT_FAILURE);
  }
  /* Check if the postal code of the default library is the same as the default address, if not, print an error message and exit the program */
  if(defaultAddress.getPostalCode() != "Unknown Postal Code") {
    cerr << "Error: The postal code of the address should be Unknown Postal Code." << endl;
    exit(EXIT_FAILURE);
  }

  cout << "Test 4: Get Address function: Passed" << endl;
}

/* This function tests the matching books behaviour in the addBook function in the Library class on various test cases */
void TestLibrary::testMatchingBooks() {
  library.emptyLibrary(); // empty the library

  /* Create two books which are different */
  Book *book1 = new Book("Book 1", "Author 1", "Genre 1", "Subgenre 1", "Publisher 1", 100);
  Book *book2 = new Book("Book 2", "Author 2", "Genre 2", "Subgenre 2", "Publisher 2", 200);

  /* Try and add the first book to the library, if it fails, print an error message and exit the program */
  if(library.addBook(book1) == false) {
    cerr << "Error: Book 1 should be able to be added to the library." << endl;
    exit(EXIT_FAILURE);
  }
  /* Try and add the second book to the library, if it fails, print an error message and exit the program */
  if(library.addBook(book2) == false) {
    cerr << "Error: Book 2 should be able to be added to the library." << endl;
    exit(EXIT_FAILURE);
  }
  /* Try and add the first book to the library again, if it succeeds, print an error message and exit the program */
  if(library.addBook(book1) == true) {
    cerr << "Error: Book 1 should not be able to be added to the library." << endl;
    exit(EXIT_FAILURE);
  }

  cout << "Test 5: Matching Books Cannot Be Added: Passed" << endl;
}

/* This function tests the addBook function in the Library class on various test cases */
void TestLibrary::testAddBooks() {
  library.emptyLibrary(); // empty the library

  /* Create two books */
  Book *book1 = new Book("Book 1", "Author 1", "Genre 1", "Subgenre 1", "Publisher 1", 100);
  Book *book2 = new Book("Book 2", "Author 2", "Genre 2", "Subgenre 2", "Publisher 2", 200);

  /* Try and add the first book to the library, if it fails, print an error message and exit the program */
  if(library.addBook(book1) == false) {
    cerr << "Error: Book 1 should be able to be added to the library." << endl;
    exit(EXIT_FAILURE);
  }
  /* Try and add the second book to the library, if it fails, print an error message and exit the program */
  if(library.addBook(book2) == false) {
    cerr << "Error: Book 2 should be able to be added to the library." << endl;
    exit(EXIT_FAILURE);
  }

  vector<Book *> books = library.getBooks(); // get the books in the library  

  /* Check if there are two books in the library, if not, print an error message and exit the program */
  if(books.size() != 2) {
    cerr << "Error: There should be 2 books in the library." << endl;
    exit(EXIT_FAILURE);
  }
  /* Check if the first book in the library is the same as the first book, if not, print an error message and exit the program */
  if(*books.at(0) != *book1) {
    cerr << "Error: The first book in the library should be Book 1." << endl;
    exit(EXIT_FAILURE);
  }
  /* Check if the second book in the library is the same as the second book, if not, print an error message and exit the program */
  if(*books.at(1) != *book2) {
    cerr << "Error: The second book in the library should be Book 2." << endl;
    exit(EXIT_FAILURE);
  }

  cout << "Test 6: Add Books function: Passed" << endl;
}

/* This function tests the removeBook function in the Library class on various test cases */
void TestLibrary::testRemoveBook() {
  library.emptyLibrary(); // empty the library

  /* Create two books */
  Book *book1 = new Book("Book 1", "Author 1", "Genre 1", "Subgenre 1", "Publisher 1", 100);
  Book *book2 = new Book("Book 2", "Author 2", "Genre 2", "Subgenre 2", "Publisher 2", 200);
  Book *removedBook1; // create a pointer to the book that will be removed

  /* Try and add the first book to the library, if it fails, print an error message and exit the program */
  if(library.addBook(book1) == false) {
    cerr << "Error: Book 1 should be able to be added to the library." << endl;
    exit(EXIT_FAILURE);
  }
  /* Try and add the second book to the library, if it fails, print an error message and exit the program */
  if(library.addBook(book2) == false) {
    cerr << "Error: Book 2 should be able to be added to the library." << endl;
    exit(EXIT_FAILURE);
  }

  /* Try and remove the first book from the library, if it fails, print an error message and exit the program */
  if(library.removeBook(book1, &removedBook1) == false) {
    cerr << "Error: Book 1 should be able to be removed from the library." << endl;
    exit(EXIT_FAILURE);
  }

  /* Try and remove the first book from the library again, if it succeeds, print an error message and exit the program */
  if(library.removeBook(book1, &removedBook1) == true) {
    cerr << "Error: Book 1 should not be able to be removed from the library." << endl;
    exit(EXIT_FAILURE);
  }

  /* Check if there is one book in the library, if not, print an error message and exit the program */
  if(library.getBookCount() != 1) {
    cerr << "Error: There should be 1 book in the library." << endl;
    exit(EXIT_FAILURE);
  }

  /* Check if the first book in the library is the same as the second book, if not, print an error message and exit the program */
  if(*library.getBooks().at(0) != *book2) {
    cerr << "Error: The first book in the library should be Book 2." << endl;
    exit(EXIT_FAILURE);
  }

  delete book1; // delete the first book
  initLibraryFromFile(library); // reinitialize the library with the books from the file

  /* Iterate through the books in the library and remove all of them */
  for(long unsigned int i = 0; i < 10; ++i) {
    Book *removedBook; // create a pointer to the book that will be removed

    /* Try and remove the first book from the library, if it fails, print an error message and exit the program */
    if (library.removeBook(library.getBooks().at(0), &removedBook) == false) {
      cerr << "Error: Book " << "0" << " should be able to be removed from the library." << endl;
      exit(EXIT_FAILURE);
    }

    delete removedBook; // delete the removed book
  }

  /* Check if there are no books in the library, if not, print an error message and exit the program */
  if(library.getBookCount() != 0) {
    cerr << "Error: There should be 0 books in the library." << endl;
    exit(EXIT_FAILURE);
  }

  cout << "Test 7: Remove Book function: Passed" << endl;
}

/* This function tests the removeBookByCriteria function in the Library class on various test cases */
void TestLibrary::testRemoveBookByCriteria() {
  initLibraryFromFile(library); // reinitialize the library with the books from the file

  int startingSize = library.getBookCount(); // get the starting size of the library

  /* Create a pointer to a book for each criteria */
  Book *removedTitleBook;
  Book *removedAuthorBook;
  Book *removedGenreBook;
  Book *removedSubgenreBook;
  Book *removedPublisherBook;
  Book *removedPageCountBook;

  int randomTitleIndex = getRandomizedIndex(); // get a random index for the title criteria
  Book *titleBook = library.getBooks().at(randomTitleIndex); // get the book at the random index
  Criteria *titleCriteria = new Title_Criteria(titleBook->getTitle()); // create a title criteria with that book's title

  /* Try and remove the book from the library by the title criteria, if it fails, print an error message and exit the program */
  if(library.removeBookByCriteria(titleCriteria, &removedTitleBook) == false) {
    cerr << "Error: Book " << titleBook->getTitle() << " should be able to be removed from the library." << endl;
    exit(EXIT_FAILURE);
  }

  /* Get a random index for the author criteria, get the book at that index, and create an author criteria with that book's author */
  int randomAuthorIndex = getRandomizedIndex();
  Book *authorBook = library.getBooks().at(randomAuthorIndex);
  Criteria *authorCriteria = new Author_Criteria(authorBook->getAuthor());

  /* Try and remove the book from the library by the author criteria, if it fails, print an error message and exit the program */
  if(library.removeBookByCriteria(authorCriteria, &removedAuthorBook) == false) {
    cerr << "Error: Book " << authorBook->getTitle() << " should be able to be removed from the library." << endl;
    exit(EXIT_FAILURE);
  }

  /* Get a random index for the genre criteria, get the book at that index, and create a genre criteria with that book's genre */
  int randomGenreIndex = getRandomizedIndex();
  Book *genreBook = library.getBooks().at(randomGenreIndex);
  Criteria *genreCriteria = new Genre_Criteria(genreBook->getGenre());

  /* Try and remove the book from the library by the genre criteria, if it fails, print an error message and exit the program */
  if(library.removeBookByCriteria(genreCriteria, &removedGenreBook) == false) {
    cerr << "Error: Book " << genreBook->getTitle() << " should be able to be removed from the library." << endl;
    exit(EXIT_FAILURE);
  }

  /* Get a random index for the subgenre criteria, get the book at that index, and create a subgenre criteria with that book's subgenre */
  int randomSubgenreIndex = getRandomizedIndex();
  Book *subgenreBook = library.getBooks().at(randomSubgenreIndex);
  Criteria *subgenreCriteria = new Subgenre_Criteria(subgenreBook->getSubgenre());

  /* Try and remove the book from the library by the subgenre criteria, if it fails, print an error message and exit the program */
  if(library.removeBookByCriteria(subgenreCriteria, &removedSubgenreBook) == false) {
    cerr << "Error: Book " << subgenreBook->getTitle() << " should be able to be removed from the library." << endl;
    exit(EXIT_FAILURE);
  }

  /* Get a random index for the publisher criteria, get the book at that index, and create a publisher criteria with that book's publisher */
  int randomPublisherIndex = getRandomizedIndex();
  Book *publisherBook = library.getBooks().at(randomPublisherIndex);
  Criteria *publisherCriteria = new Publisher_Criteria(publisherBook->getPublisher());

  /* Try and remove the book from the library by the publisher criteria, if it fails, print an error message and exit the program */
  if(library.removeBookByCriteria(publisherCriteria, &removedPublisherBook) == false) {
    cerr << "Error: Book " << publisherBook->getTitle() << " should be able to be removed from the library." << endl;
    exit(EXIT_FAILURE);
  }

  /* Get a random index for the pages criteria, get the book at that index, and create a pages criteria with that book's page count */
  int randomPagesIndex = getRandomizedIndex();
  Book *pagesBook = library.getBooks().at(randomPagesIndex);
  Criteria *pagesCriteria = new Page_Criteria(pagesBook->getPageCount());
  
  /* Try and remove the book from the library by the pages criteria, if it fails, print an error message and exit the program */
  if(library.removeBookByCriteria(pagesCriteria, &removedPageCountBook) == false) {
    cerr << "Error: Book " << pagesBook->getTitle() << " should be able to be removed from the library." << endl;
    exit(EXIT_FAILURE);
  }

  /* If the library size is not equal to the starting size minus 6, print an error message and exit the program */
  if(library.getBookCount() != startingSize - 6) {
    cerr << "Error: There should be " << startingSize - 6 << " books in the library." << endl;
    exit(EXIT_FAILURE);
  }

  /* Delete all the criteria and removed books */
  delete titleCriteria;
  delete authorCriteria;
  delete genreCriteria;
  delete subgenreCriteria;
  delete publisherCriteria;
  delete pagesCriteria;

  delete removedTitleBook;
  delete removedAuthorBook;
  delete removedGenreBook;
  delete removedSubgenreBook;
  delete removedPublisherBook;
  delete removedPageCountBook;

  cout << "Test 8: Remove Book by Criteria function: Passed" << endl;
}

void TestLibrary::testRemoveBookBySeveralCriteria() {
  initLibraryFromFile(library);

  int oldNumberOfBooks = library.getBookCount();
  int randomBookIndex = getRandomizedIndex();
  Book *book = library.getBooks().at(randomBookIndex);
  Book *removedBook;

  Criteria *titleCriteria = new Title_Criteria(book->getTitle());
  Criteria *authorCriteria = new Author_Criteria(book->getAuthor());
  Criteria *genreCriteria = new Genre_Criteria(book->getGenre());
  Criteria *subgenreCriteria = new Subgenre_Criteria(book->getSubgenre());
  Criteria *publisherCriteria = new Publisher_Criteria(book->getPublisher());
  Criteria *pagesCriteria = new Page_Criteria(book->getPageCount());

  vector<Criteria *> criteriaVector;
  criteriaVector.push_back(titleCriteria);
  criteriaVector.push_back(authorCriteria);
  criteriaVector.push_back(genreCriteria);
  criteriaVector.push_back(subgenreCriteria);
  criteriaVector.push_back(publisherCriteria);
  criteriaVector.push_back(pagesCriteria);

  if(library.removeBookBySeveralCriteria(criteriaVector, &removedBook) == false) {
    cerr << "Error: Book " << book->getTitle() << " should be able to be removed from the library." << endl;
    exit(EXIT_FAILURE);
  }

  if(library.getBookCount() != oldNumberOfBooks - 1) {
    cerr << "Error: Book removal operation did remove the proper number of books. " << endl;
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < library.getBookCount(); ++i) {
    if(library.getBooks().at(i) == book) {
      cerr << "Error: Book should not be in the library." << endl;
      exit(EXIT_FAILURE);
    }
  }

  delete titleCriteria;
  delete authorCriteria;
  delete genreCriteria;
  delete subgenreCriteria;
  delete publisherCriteria;
  delete pagesCriteria;

  delete removedBook;

  cout << "Test 9: Remove Book by Several Criteria function: Passed" << endl;
}

void TestLibrary::testGetBookByCriteria() {
  initLibraryFromFile(library);

  int randomTitleIndex = getRandomizedIndex();
  int randomAuthorIndex = getRandomizedIndex();
  int randomGenreIndex = getRandomizedIndex();
  int randomSubgenreIndex = getRandomizedIndex();
  int randomPublisherIndex = getRandomizedIndex();
  int randomPagesIndex = getRandomizedIndex();

  Book *titleBook = library.getBooks().at(randomTitleIndex);
  Book *authorBook = library.getBooks().at(randomAuthorIndex);
  Book *genreBook = library.getBooks().at(randomGenreIndex);
  Book *subgenreBook = library.getBooks().at(randomSubgenreIndex);
  Book *publisherBook = library.getBooks().at(randomPublisherIndex);
  Book *pagesBook = library.getBooks().at(randomPagesIndex);

  Book *foundTitleBook;
  Book *foundAuthorBook;
  Book *foundGenreBook;
  Book *foundSubgenreBook;
  Book *foundPublisherBook;
  Book *foundPageCountBook;

  Criteria *titleCriteria = new Title_Criteria(titleBook->getTitle());
  Criteria *authorCriteria = new Author_Criteria(authorBook->getAuthor());
  Criteria *genreCriteria = new Genre_Criteria(genreBook->getGenre());
  Criteria *subgenreCriteria = new Subgenre_Criteria(subgenreBook->getSubgenre());
  Criteria *publisherCriteria = new Publisher_Criteria(publisherBook->getPublisher());
  Criteria *pagesCriteria = new Page_Criteria(pagesBook->getPageCount());

  if(library.getBookByCriteria(*titleCriteria, &foundTitleBook) == false) {
    cerr << "Error: Book " << titleBook->getTitle() << " should be able to be found in the library." << endl;
    exit(EXIT_FAILURE);
  }

  if(library.getBookByCriteria(*authorCriteria, &foundAuthorBook) == false) {
    cerr << "Error: Book " << authorBook->getTitle() << " should be able to be found in the library." << endl;
    exit(EXIT_FAILURE);
  }

  if(library.getBookByCriteria(*genreCriteria, &foundGenreBook) == false) {
    cerr << "Error: Book " << genreBook->getTitle() << " should be able to be found in the library." << endl;
    exit(EXIT_FAILURE);
  }

  if(library.getBookByCriteria(*subgenreCriteria, &foundSubgenreBook) == false) {
    cerr << "Error: Book " << subgenreBook->getTitle() << " should be able to be found in the library." << endl;
    exit(EXIT_FAILURE);
  }

  if(library.getBookByCriteria(*publisherCriteria, &foundPublisherBook) == false) {
    cerr << "Error: Book " << publisherBook->getTitle() << " should be able to be found in the library." << endl;
    exit(EXIT_FAILURE);
  }

  if(library.getBookByCriteria(*pagesCriteria, &foundPageCountBook) == false) {
    cerr << "Error: Book " << pagesBook->getTitle() << " should be able to be found in the library." << endl;
    exit(EXIT_FAILURE);
  }

  delete titleCriteria;
  delete authorCriteria;
  delete genreCriteria;
  delete subgenreCriteria;
  delete publisherCriteria;
  delete pagesCriteria;

  cout << "Test 10: Get Book by Criteria function: Passed" << endl;
}

void TestLibrary::testGetBooksByCriteria() {
  initLibraryFromFile(library);

  string testCriteria = "tech";
  vector<Book *> foundBooks;

  Criteria *criteria = new Genre_Criteria(testCriteria);

  if(library.getBooksByCriteria(*criteria, foundBooks) == false) {
    cerr << "Error: Books with genre " << testCriteria << " should be able to be found in the library." << endl;
    exit(EXIT_FAILURE);
  }

  if(foundBooks.size() != 5) {
    cerr << "Error: There should be five books that have the tech genre." << endl;
    exit(EXIT_FAILURE);
  }

  for (long unsigned int i = 0; i < foundBooks.size(); ++i) {
    if(foundBooks.at(i)->getGenre() != testCriteria) {
      cerr << "Error: Book " << foundBooks.at(i)->getTitle() << " should not be in the found books." << endl;
      exit(EXIT_FAILURE);
    }
  }

  delete criteria;

  cout << "Test 11: Get Books by Criteria function: Passed" << endl;
}

void TestLibrary::testGetBookBySeveralCriteria() {
  initLibraryFromFile(library);

  int randomBookIndex = getRandomizedIndex();
  Book *book = library.getBooks().at(randomBookIndex);
  Book *foundBook;

  Criteria *titleCriteria = new Title_Criteria(book->getTitle());
  Criteria *authorCriteria = new Author_Criteria(book->getAuthor());
  Criteria *genreCriteria = new Genre_Criteria(book->getGenre());
  Criteria *subgenreCriteria = new Subgenre_Criteria(book->getSubgenre());
  Criteria *publisherCriteria = new Publisher_Criteria(book->getPublisher());
  Criteria *pagesCriteria = new Page_Criteria(book->getPageCount());

  vector<Criteria *> criteriaVector;

  criteriaVector.push_back(titleCriteria);
  criteriaVector.push_back(authorCriteria);
  criteriaVector.push_back(genreCriteria);
  criteriaVector.push_back(subgenreCriteria);
  criteriaVector.push_back(publisherCriteria);
  criteriaVector.push_back(pagesCriteria);

  if(library.getBookBySeveralCriteria(criteriaVector, &foundBook) == false) {
    cerr << "Error: Book " << book->getTitle() << " should be able to be found in the library." << endl;
    exit(EXIT_FAILURE);
  }
  if(*foundBook != *book) {
    cerr << "Error: Original/Model book should be the same as the found book." << endl;
    exit(EXIT_FAILURE);
  }

  delete titleCriteria;
  delete authorCriteria;
  delete genreCriteria;
  delete subgenreCriteria;
  delete publisherCriteria;
  delete pagesCriteria;

  cout << "Test 12: Get Book by Several Criteria function: Passed" << endl;
}

void TestLibrary::testGetBooksBySeveralCriteria() {
  Library testLibrary = Library();

  Book *book1 = new Book("The Hobbit", "J.R.R. Tolkien", "Fantasy", "Epic", "Houghton Mifflin Harcourt", 295);
  Book *book2 = new Book("The Lord of the Rings", "J.R.R. Tolkien", "Fantasy", "Epic", "Houghton Mifflin Harcourt", 1216);
  Book *book3 = new Book("The Silmarillion", "J.R.R. Tolkien", "Fantasy", "Epic", "Houghton Mifflin Harcourt", 432);
  Book *book5 = new Book("1984", "George Orwell", "Dystopian", "Political", "Houghton Mifflin Harcourt", 328);
  Book *book6 = new Book("Animal Farm", "George Orwell", "Dystopian", "Political", "Houghton Mifflin Harcourt", 112);

  testLibrary.addBook(book1);
  testLibrary.addBook(book2);
  testLibrary.addBook(book3);
  testLibrary.addBook(book5);
  testLibrary.addBook(book6);

  Criteria* genreCriteria = new Genre_Criteria("Fantasy");
  Criteria* authorCriteria = new Author_Criteria("J.R.R. Tolkien");
  Criteria* subgenreCriteria = new Subgenre_Criteria("Epic");
  Criteria *publisherCriteria = new Publisher_Criteria("Houghton Mifflin Harcourt");

  vector <Criteria *> criteriaVector;
  criteriaVector.push_back(genreCriteria);
  criteriaVector.push_back(authorCriteria);
  criteriaVector.push_back(subgenreCriteria);
  criteriaVector.push_back(publisherCriteria);

  vector<Book *> foundBooks;

  if(testLibrary.getBooksBySeveralCriteria(criteriaVector, foundBooks) == false) {
    cerr << "Error: Books with the fantasy genre, J.R.R. Tolkien as author, Epic subgenre and Houghton Mifflin Harcourt as publisher" << " should be able to be found in the library." << endl;
    exit(EXIT_FAILURE);
  }

  for(long unsigned int i = 0; i < foundBooks.size(); ++i) {
    if(*(foundBooks.at(i)) != *book1 && *(foundBooks.at(i)) != *book2 && *(foundBooks.at(i)) == *book3 && *(foundBooks.at(i)) == *book5 && *(foundBooks.at(i)) == *book6) {
      cerr << "Error: Book found was not one of the books that should have been found." << endl;
      exit(EXIT_FAILURE);
    }
  }

  delete genreCriteria;
  delete authorCriteria;
  delete subgenreCriteria;
  delete publisherCriteria;

  cout << "Test 13: Get Books by Several Criteria function: Passed" << endl;
}

void TestLibrary::testSortByOrderAdded() {
  initLibraryFromFile(library);

  library.sortBooksByOrderAdded();

  for(int i = 0; i < library.getBookCount() - 1; ++i) {
    if(library.getBooks().at(i)->getID() > library.getBooks().at(i + 1)->getID()) {
      cerr << "Error: Books are not sorted by order added." << endl;
      exit(EXIT_FAILURE);
    }
  }

  cout << "Test 14: Sort Books by Order Added function: Passed" << endl;
}

void TestLibrary::testSortByTitle() {
  initLibraryFromFile(library);

  cout << "Library before sorting: " << endl;
  library.printOnlyBooks(cout);
  library.sortBooksByTitle();

  for(int i = 0; i < library.getBookCount() - 1; ++i) {
    if(library.getBooks().at(i)->getTitle() > library.getBooks().at(i + 1)->getTitle()) {
      cerr << "Error: Books are not sorted by title." << endl;
      exit(EXIT_FAILURE);
    }
  }

  cout << "Library after sorting: " << endl;
  library.printOnlyBooks(cout);

  cout << "Test 15: Sort Books by Title function: Passed" << endl;
}

void TestLibrary::testSortByAuthor() {
  initLibraryFromFile(library);

  cout << "Library before sorting: " << endl;
  library.printOnlyBooks(cout);
  library.sortBooksByAuthor();

  for(int i = 0; i < library.getBookCount() - 1; ++i) {
    if(library.getBooks().at(i)->getAuthor() > library.getBooks().at(i + 1)->getAuthor()) {
      cerr << "Error: Books are not sorted by author." << endl;
      exit(EXIT_FAILURE);
    }
  }

  cout << "Library after sorting: " << endl;
  library.printOnlyBooks(cout);

  cout << "Test 16: Sort Books by Author function: Passed" << endl;
}

void TestLibrary::testSortByGenre() {
  initLibraryFromFile(library);

  cout << "Library before sorting: " << endl;
  library.printOnlyBooks(cout);
  library.sortBooksByGenre();

  for(int i = 0; i < library.getBookCount() - 1; ++i) {
    if(library.getBooks().at(i)->getGenre() > library.getBooks().at(i + 1)->getGenre()) {
      cerr << "Error: Books are not sorted by genre." << endl;
      exit(EXIT_FAILURE);
    }
  }

  cout << "Library after sorting: " << endl;
  library.printOnlyBooks(cout);

  cout << "Test 17: Sort Books by Genre function: Passed" << endl;
}

void TestLibrary::testSortBySubgenre() {
  initLibraryFromFile(library);

  cout << "Library before sorting: " << endl;
  library.printOnlyBooks(cout);
  library.sortBooksBySubgenre();

  for(int i = 0; i < library.getBookCount() - 1; ++i) {
    if(library.getBooks().at(i)->getSubgenre() > library.getBooks().at(i + 1)->getSubgenre()) {
      cerr << "Error: Books are not sorted by subgenre." << endl;
      exit(EXIT_FAILURE);
    }
  }

  cout << "Library after sorting: " << endl;
  library.printOnlyBooks(cout);

  cout << "Test 18: Sort Books by Subgenre function: Passed" << endl;
}

void TestLibrary::testSortByPublisher() {
  initLibraryFromFile(library);

  cout << "Library before sorting: " << endl;
  library.printOnlyBooks(cout);
  library.sortBooksByPublisher();

  for(int i = 0; i < library.getBookCount() - 1; ++i) {
    if(library.getBooks().at(i)->getPublisher() > library.getBooks().at(i + 1)->getPublisher()) {
      cerr << "Error: Books are not sorted by publisher." << endl;
      exit(EXIT_FAILURE);
    }
  }

  cout << "Library after sorting: " << endl;
  library.printOnlyBooks(cout);

  cout << "Test 19: Sort Books by Publisher function: Passed" << endl;
}

void TestLibrary::testSortByPageCount() {
  initLibraryFromFile(library);

  cout << "Library before sorting: " << endl;
  library.printOnlyBooks(cout);
  library.sortBooksByPageCount();

  for(int i = 0; i < library.getBookCount() - 1; ++i) {
    if(library.getBooks().at(i)->getPageCount() > library.getBooks().at(i + 1)->getPageCount()) {
      cerr << "Error: Books are not sorted by pages." << endl;
      exit(EXIT_FAILURE);
    }
  }

  cout << "Library after sorting: " << endl;
  library.printOnlyBooks(cout);

  cout << "Test 20: Sort Books by Pages function: Passed" << endl;
}

