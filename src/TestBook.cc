/* TestBook.cc */
/* Author: Nguyen-Hanh Nong */
/* Revision: Revision 1.0 */
/* */
/* This is the source code file for the TestBook class which contains the functionality involving testing different functions in the Book class including testing operator overloading and how different books match different criteria. */

/* Including the corresponding header file for the TestBook class */
#include "TestBook.hh"

/* Constructor for the Tester class */
TestBook::TestBook(): bookVector(new vector<Book*>())
{
}

/* Destructor for the Tester class */
TestBook::~TestBook() {
  /* Deleting all the elements in the bookVector */
  while(bookVector->size() > 0) {
    delete bookVector->back();
    bookVector->pop_back();
  }
  /* Clearing the vector, shrinking it and then deleting vector*/
  bookVector->clear();
  bookVector->shrink_to_fit();
  delete bookVector;
}

/* This function runs all the functions in the TestBook class */
void TestBook::launchAllTests() {
  printAllBooks(); // Printing all the books in the test file
  compareBooks(); // Comparing different books
  testAllCriteria(); //Testing all the criteria with various books

  cout << "SUCCESS: All Book tests passed" << endl << endl;
}

/* This function deletes all the books in the bookVector vector */
void TestBook::emptyBookVector() {
  /* Deleting all the elements in the bookVector */
  while(bookVector->size() > 0) {
    delete bookVector->back();
    bookVector->pop_back();
  }
  /* Clearing the vector and then shrinking it to the new size r*/
  bookVector->clear();
  bookVector->shrink_to_fit();
}

/* This function initializes the book vector with a series of books stored in a text file */
void TestBook::initFromFile() {
  emptyBookVector(); // Emptying the bookVector just in case it has elements inside it

  string line; // The current line being read from the file
  string operatingSystem; // The operating system the program is running on
  string fileLocation; // The location of the file containing the books

  /* Setting the fileLocation variable and changing the string depending on what OS you're on */
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

  ifstream file; // The file stream object
  file.open(fileLocation); // Opening the file

  /* Check if the file is open or not, if it isn't then print an error message and then quit the program */
  if (!file.is_open()) {
    cerr << "The path given is incorrect for the tester file. Program will now exit" << endl;
    exit(EXIT_FAILURE);
  }
  getline(file, line); // skip the 1st line

  /* Iterate through every line in the program */
  while(getline(file,line)) {
    /* If there is nothing at the line, then skip the line */
    if (line.empty()) {
      continue;
    }

    istringstream iss(line); // The string stream object
    string lineStream; // The current line being read from the string stream
    vector<string> currentLine; // The current line being read from the file

    /* Split the line being read by the | character and add it to the currentLine vector */
    while(getline(iss, lineStream, '|')) {
      currentLine.push_back(lineStream); 
    }
    
    /* If the amount of entries in the line is less than needed to create a book, then we have to add a publisher name to the line*/
    if(currentLine.size() < NUM_BOOK_PROPERTIES) {
      currentLine.push_back("Unknown Publisher");
    }

    // Creating and adding the book to the bookVector
    bookVector->push_back(new Book(currentLine.at(0), currentLine.at(1), currentLine.at(2), currentLine.at(3), currentLine.at(5), stoi(currentLine.at(4)), 5));
  }

  file.close(); // Closing the file
}

/* This funciton prints all the books in the bookVector vector */
void TestBook::printAllBooks() {
  /* If the bookVector is empty, then we have to initialize it with the books from the file */
  if(bookVector->size() <= 0) {
    initFromFile();
  }

  /* Iterating through the bookVector and printing out all the books */
  for (long unsigned int i = 0; i < bookVector->size(); ++i) {
    cout << *bookVector->at(i) << endl;
  }

  cout << "Test 1: Print all books: PASSED" << endl;
}

/* This function compares several books and checks if they are the same or not and whether the equality operator in the Book class is correctly matching or not matching them */
void TestBook::compareBooks() {
  /* If the bookVector is empty, then we have to initialize it with the books from the file */
  if(bookVector->size() <= 0) {
    initFromFile();
  }

  /* Test 1: Two different books */
  Book *bookOne = bookVector->at(0);
  Book *bookTwo = bookVector->at(1);

  /* If the two books are considered to be the same, then print an error message and then quit the program */
  if((*bookOne == *bookTwo) == true) {
    cerr << "These two books should not be considered to be the same. Abort." << endl;
    exit(EXIT_FAILURE);
  }

  /* Test 2: Two same books */
  bookOne = bookVector->at(0);
  bookTwo = bookVector->at(0);

  /* If the two books are considered to be different, then print an error message and then quit the program */
  if((*bookOne == *bookTwo) == false) {
    cerr << "These two books should be considered to be the same. Abort." << endl;
    exit(EXIT_FAILURE);
  }

  /* Test 3: Two default books */
  Book *bookThree = new Book();
  Book *bookFour = new Book();

  /* If the two books are considered to be different, then print an error message and then quit the program */
  if((*bookThree == *bookFour) == false) {
    cerr << "These two default books should be considered to be the same since they're default books. Abort." << endl;
    exit(EXIT_FAILURE);
  }

  /* Deleting the newly created books */
  delete bookThree;
  delete bookFour;

  cout << "Test 2: Compare books: PASSED" << endl;
}

/* This function tests all the criteria classes */
void TestBook::testAllCriteria() {
  /* If the bookVector is empty, then we have to initialize it with the books from the file */
  if(bookVector->size() <= 0) {
    initFromFile();
  }

  /* Testing all the criteria several times as they are randomized */
  for (long unsigned int i = 0; i < NUM_ATTEMPTS_PER_TEST; ++i) {
    testTitleCriteria();
    testAuthorCriteria();
    testGenreCriteria();
    testSubgenreCriteria();
    testPublisherCriteria();
    testPageCountCriteria();
  }

  cout << "Test 3: Test all criteria: PASSED" << endl;
}

/* This function returns a random index from the bookVector vector by using the hardware and a random number generator */
const int TestBook::getRandomizedIndex() const {
  std::random_device rd; // obtain a random number from hardware
  std::mt19937 gen(rd()); // seed the generator
  std::uniform_int_distribution<> distr(0, bookVector->size() - 1); // define the range

  const int returnInteger = distr(gen); // generate random number 

  return returnInteger; // return the random number
}

/* This function tests the Title_Criteria class */
void TestBook::testTitleCriteria() const {

  /* Create two Title_Criteria objects, one that should match and one that should not match */
  Criteria *matching_title = new Title_Criteria(bookVector->at(getRandomizedIndex())->getTitle());
  Criteria *non_matching_title = new Title_Criteria("This should not be a matching title");

  /* Creating two boolean variables that will be used to check if the criteria is matching or not */
  bool matching_title_boolean = false;
  bool non_matching_title_boolean = false;

  /* Iterating through the bookVector and checking if the criteria is matching or not for every book */
  for (long unsigned int i = 0; i < bookVector->size(); ++i) {
    if(matching_title->matches(*bookVector->at(i))) {
      matching_title_boolean = true;
    }
    if(non_matching_title->matches(*bookVector->at(i))) {
      non_matching_title_boolean = true;
    }
  }

  /* If the criteria is not matching when it should be, then print an error message and then quit the program */
  if(matching_title_boolean == false) {
    cerr << *matching_title << "This criteria was should have been matched " << endl;
    exit(EXIT_FAILURE);
  }

  /* If the criteria is matching when it should not be, then print an error message and then quit the program */
  if(non_matching_title_boolean == true) {
    cerr << *non_matching_title << "This criteria was should not have been matched. " << endl;
    exit(EXIT_FAILURE);
  }

  /* Deleting the criteria pointers */
  delete matching_title;
  delete non_matching_title;
}

/* This function tests the Author_Criteria class */
void TestBook::testAuthorCriteria() const {

  /* Create two Author_Criteria objects, one that should match and one that should not match */
  Criteria *matching_author = new Author_Criteria(bookVector->at(getRandomizedIndex())->getAuthor());
  Criteria *non_matching_author = new Author_Criteria("This should not be a matching author");

  /* Creating two boolean variables that will be used to check if the criteria is matching or not */
  bool matching_author_boolean = false;
  bool non_matching_author_boolean = false;

  /* Iterating through the bookVector and checking if the criteria is matching or not for every book */
  for (long unsigned int i = 0; i < bookVector->size(); ++i) {
    if(matching_author->matches(*bookVector->at(i))) {
      matching_author_boolean = true;
    }
    if(non_matching_author->matches(*bookVector->at(i))) {
      non_matching_author_boolean = true;
    }
  }

  /* If the criteria is not matching when it should be, then print an error message and then quit the program */
  if(matching_author_boolean == false) {
    cerr << *matching_author << "This criteria was should have been matched " << endl;
    exit(EXIT_FAILURE);
  }

  /* If the criteria is matching when it should not be, then print an error message and then quit the program */
  if(non_matching_author_boolean == true) {
    cerr << *non_matching_author << "This criteria was should not have been matched. " << endl;
    exit(EXIT_FAILURE);
  }

  /* Deleting the criteria pointers */
  delete matching_author;
  delete non_matching_author;
}

/* This function tests the Genre_Criteria class */
void TestBook::testGenreCriteria() const {

  /* Create two Genre_Criteria objects, one that should match and one that should not match */
  Criteria *matching_genre = new Genre_Criteria(bookVector->at(getRandomizedIndex())->getGenre());
  Criteria *non_matching_genre = new Genre_Criteria("This should not be a matching genre");

  /* Creating two boolean variables that will be used to check if the criteria is matching or not */
  bool matching_genre_boolean = false;
  bool non_matching_genre_boolean = false;

  /* Iterating through the bookVector and checking if the criteria is matching or not for every book */
  for (long unsigned int i = 0; i < bookVector->size(); ++i) {
    if(matching_genre->matches(*bookVector->at(i))) {
      matching_genre_boolean = true;
    }
    if(non_matching_genre->matches(*bookVector->at(i))) {
      non_matching_genre_boolean = true;
    }
  }

  /* If the criteria is not matching when it should be, then print an error message and then quit the program */
  if(matching_genre_boolean == false) {
    cerr << *matching_genre << "This criteria was should have been matched " << endl;
    exit(EXIT_FAILURE);
  }

  /* If the criteria is matching when it should not be, then print an error message and then quit the program */
  if(non_matching_genre_boolean == true) {
    cerr << *non_matching_genre << "This criteria was should not have been matched. " << endl;
    exit(EXIT_FAILURE);
  }

  /* Deleting the criteria pointers */
  delete matching_genre;
  delete non_matching_genre;
}

/* This function tests the Subgenre_Criteria class */
void TestBook::testSubgenreCriteria() const {

  /* Create two Subgenre_Criteria objects, one that should match and one that should not match */
  Criteria *matching_subgenre = new Subgenre_Criteria(bookVector->at(getRandomizedIndex())->getSubgenre());
  Criteria *non_matching_subgenre = new Subgenre_Criteria("This should not be a matching subgenre");

  /* Creating two boolean variables that will be used to check if the criteria is matching or not */
  bool matching_subgenre_boolean = false;
  bool non_matching_subgenre_boolean = false;

  /* Iterating through the bookVector and checking if the criteria is matching or not for every book */
  for (long unsigned int i = 0; i < bookVector->size(); ++i) {
    if(matching_subgenre->matches(*bookVector->at(i))) {
      matching_subgenre_boolean = true;
    }
    if(non_matching_subgenre->matches(*bookVector->at(i))) {
      non_matching_subgenre_boolean = true;
    }
  }

  /* If the criteria is not matching when it should be, then print an error message and then quit the program */
  if(matching_subgenre_boolean == false) {
    cerr << *matching_subgenre << "This criteria was should have been matched " << endl;
    exit(EXIT_FAILURE);
  }

  /* If the criteria is matching when it should not be, then print an error message and then quit the program */
  if(non_matching_subgenre_boolean == true) {
    cerr << *non_matching_subgenre << "This criteria was should not have been matched. " << endl;
    exit(EXIT_FAILURE);
  }

  /* Deleting the criteria pointers */
  delete matching_subgenre;
  delete non_matching_subgenre;
}

/* This function tests the Publisher_Criteria class */
void TestBook::testPublisherCriteria() const {

  /* Create two Publisher_Criteria objects, one that should match and one that should not match */
  Criteria *matching_publisher = new Publisher_Criteria(bookVector->at(getRandomizedIndex())->getPublisher());
  Criteria *non_matching_publisher = new Publisher_Criteria("This should not be a matching publisher");

  /* Creating two boolean variables that will be used to check if the criteria is matching or not */
  bool matching_publisher_boolean = false;
  bool non_matching_publisher_boolean = false;

  /* Iterating through the bookVector and checking if the criteria is matching or not for every book */
  for (long unsigned int i = 0; i < bookVector->size(); ++i) {
    if(matching_publisher->matches(*bookVector->at(i))) {
      matching_publisher_boolean = true;
    }
    if(non_matching_publisher->matches(*bookVector->at(i))) {
      non_matching_publisher_boolean = true;
    }
  }

  /* If the criteria is not matching when it should be, then print an error message and then quit the program */
  if(matching_publisher_boolean == false) {
    cerr << *matching_publisher << "This criteria was should have been matched " << endl;
    exit(EXIT_FAILURE);
  }

  /* If the criteria is matching when it should not be, then print an error message and then quit the program */
  if(non_matching_publisher_boolean == true) {
    cerr << *non_matching_publisher << "This criteria was should not have been matched. " << endl;
    exit(EXIT_FAILURE);
  }

  /* Deleting the criteria pointers */
  delete matching_publisher;
  delete non_matching_publisher;
}

/* This function tests the Author_Criteria class */
void TestBook::testPageCountCriteria() const {

  /* Create four Page_Criteria objects, one that should match, one that should not match, one that should be less than the page count, and one that should be more than the page count */
  Page_Criteria *matching_pagecount = new Page_Criteria(bookVector->at(getRandomizedIndex())->getPageCount());
  Page_Criteria *non_matching_pagecount = new Page_Criteria(-1);
  Page_Criteria *less_than_pagecount = new Page_Criteria(1000000);
  Page_Criteria *more_than_pagecount = new Page_Criteria(-500);

  /* Creating two boolean variables that will be used to check if the criteria is matching or not */
  bool matching_pagecount_boolean = false;
  bool non_matching_pagecount_boolean = false;

  /* Creating two counters that will be used to count how many books have the criteria that is less than or more than the page count */
  long unsigned int less_than_pagecount_counter = 0;
  long unsigned int more_than_pagecount_counter = 0;

  /* Iterating through the bookVector and checking if the criteria is matching or not, is less than or more than for every book */
  for (long unsigned int i = 0; i < bookVector->size(); ++i) {
    if(matching_pagecount->matches(*bookVector->at(i))) {
      matching_pagecount_boolean = true;
    }
    if(non_matching_pagecount->matches(*bookVector->at(i))) {
      non_matching_pagecount_boolean = true;
    }
    if(less_than_pagecount->lessThan(*bookVector->at(i))) {
      ++less_than_pagecount_counter;
    }
    if(more_than_pagecount->moreThan(*bookVector->at(i))) {
      ++more_than_pagecount_counter;
    }
  }

  /* If the criteria is not matching when it should be, then print an error message and then quit the program */
  if(matching_pagecount_boolean == false) {
    cerr << *matching_pagecount << "This criteria was should have been matched " << endl;
    exit(EXIT_FAILURE);
  }

  /* If the criteria is matching when it should not be, then print an error message and then quit the program */
  if(non_matching_pagecount_boolean == true) {
    cerr << *non_matching_pagecount << "This criteria was should not have been matched. " << endl;
    exit(EXIT_FAILURE);
  }

  /* If the less than counter does not match the correct amount of valid books, then print an error message and then quit the program */
  if(less_than_pagecount_counter != bookVector->size()) {
    cerr << "ERROR: The less than function is returning an incorrect amount of valid books. " << endl;
    exit(EXIT_FAILURE);
  }

  /* If the more than counter does not match the correct amount of valid books, then print an error message and then quit the program */
  if(more_than_pagecount_counter != bookVector->size()) {
    cerr << "ERROR: The more than function is returning an incorrect amount of valid books. " << endl;
    exit(EXIT_FAILURE);
  }

  /* Deleting the criteria pointers */
  delete matching_pagecount;
  delete non_matching_pagecount;
  delete less_than_pagecount;
  delete more_than_pagecount;
}