#include "TestBook.hh"

TestBook::TestBook(): bookVector(vector<Book*>())
{
}

TestBook::~TestBook() {
  for (int i = 0; i < bookVector.size(); ++i) {
    delete bookVector[i];
  }
}

void TestBook::launch() {
  initFromFile();
  printAllBooks();
  compareBooks();
  testAllCriteria();
}

void TestBook::initFromFile() {
  string line;
  string operatingSystem;
  string fileLocation;
  int pageCount;

  #ifdef _WIN32
    fileLocation = "..\books\tester\test_books.csv";
  #elif __linux__
    fileLocation = "../books/tester/test_books.csv";
  #elif __unix__
    fileLocation = "../books/tester/test_books.csv";
  #else
    cout << "Unidentified OS. This program does not currently handle this OS. The program will now exit";
    exit(EXIT_FAILURE);
  #endif

  ifstream file;
  file.open(fileLocation);

  if (!file.is_open()) {
    cerr << "The path given is incorrect for the tester file. Program will now exit" << endl;
    exit(EXIT_FAILURE);
  }
  getline(file, line); // skip the 1st line

  while(getline(file,line)) {
    if (line.empty()) {
      continue;
    }

    istringstream iss(line);
    string lineStream;
    vector<string> currentLine;

    while(getline(iss, lineStream, '|')) {
      currentLine.push_back(lineStream); 
    }
    
    if(currentLine.size() < NUM_BOOK_PROPERTIES) {
      currentLine.push_back("Unknown Publisher");
    }

    bookVector.push_back(new Book(currentLine.at(0), currentLine.at(1), currentLine.at(2), currentLine.at(3), currentLine.at(5), stoi(currentLine.at(4)), 5));
  }

  file.close();
}

void TestBook::printAllBooks() const {
  for (int i = 0; i < bookVector.size(); ++i) {
    cout << *bookVector.at(i) << endl;
  }
  cout << "Test successfully printed all the books!" << endl;
}

void TestBook::compareBooks() const {
  /* Test 1: Two different books */
  Book *bookOne = bookVector.at(0);
  Book *bookTwo = bookVector.at(1);

  if((*bookOne == *bookTwo) == true) {
    cerr << "These two books should not be considered to be the same. Abort." << endl;
    exit(EXIT_FAILURE);
  }

  /* Test 2: Two same books */
  bookOne = bookVector.at(0);
  bookTwo = bookVector.at(0);

  if((*bookOne == *bookTwo) == false) {
    cerr << "These two books should be considered to be the same. Abort." << endl;
    exit(EXIT_FAILURE);
  }

  /* Test 3: Two default books */
  Book *bookThree = new Book();
  Book *bookFour = new Book();

  if((*bookThree == *bookFour) == false) {
    cerr << "These two default books should be considered to be the same since they're default books. Abort." << endl;
    exit(EXIT_FAILURE);
  }

  delete bookThree;
  delete bookFour;

  cout << "Test succesfully passed the matching functionality of the books!" << endl;
}

void TestBook::testAllCriteria() const {
  for (int i = 0; i < NUM_ATTEMPTS_PER_TEST; ++i) {
    testTitleCriteria();
    testAuthorCriteria();
    testGenreCriteria();
    testSubgenreCriteria();
    testPublisherCriteria();
    testPageCountCriteria();
  }

  cout << "Successfully passed all criteria tests!" << endl << endl;
}

const int TestBook::getRandomizedIndex() const {
  std::random_device rd; 
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distr(0, bookVector.size() - 1);

  const int returnInteger = distr(gen);

  return returnInteger;
}

void TestBook::testTitleCriteria() const {

  Criteria *matching_title = new Title_Criteria(bookVector.at(getRandomizedIndex())->getTitle());
  Criteria *non_matching_title = new Title_Criteria("This should not be a matching title");

  bool matching_title_boolean = false;
  bool non_matching_title_boolean = false;

  for (int i = 0; i < bookVector.size(); ++i) {
    if(matching_title->matches(*bookVector.at(i))) {
      matching_title_boolean = true;
    }
    if(non_matching_title->matches(*bookVector.at(i))) {
      non_matching_title_boolean = true;
    }
  }

  if(matching_title_boolean == false) {
    cerr << *matching_title << "This criteria was should have been matched " << endl;
    exit(EXIT_FAILURE);
  }

  if(non_matching_title_boolean == true) {
    cerr << *non_matching_title << "This criteria was should not have been matched. " << endl;
    exit(EXIT_FAILURE);
  }

  delete matching_title;
  delete non_matching_title;

  return;
}

void TestBook::testAuthorCriteria() const {

  Criteria *matching_author = new Author_Criteria(bookVector.at(getRandomizedIndex())->getAuthor());
  Criteria *non_matching_author = new Author_Criteria("This should not be a matching author");

  bool matching_author_boolean = false;
  bool non_matching_author_boolean = false;

  for (int i = 0; i < bookVector.size(); ++i) {
    if(matching_author->matches(*bookVector.at(i))) {
      matching_author_boolean = true;
    }
    if(non_matching_author->matches(*bookVector.at(i))) {
      non_matching_author_boolean = true;
    }
  }

  if(matching_author_boolean == false) {
    cerr << *matching_author << "This criteria was should have been matched " << endl;
    exit(EXIT_FAILURE);
  }

  if(non_matching_author_boolean == true) {
    cerr << *non_matching_author << "This criteria was should not have been matched. " << endl;
    exit(EXIT_FAILURE);
  }

  delete matching_author;
  delete non_matching_author;
}

void TestBook::testGenreCriteria() const {

  Criteria *matching_genre = new Genre_Criteria(bookVector.at(getRandomizedIndex())->getGenre());
  Criteria *non_matching_genre = new Genre_Criteria("This should not be a matching genre");

  bool matching_genre_boolean = false;
  bool non_matching_genre_boolean = false;

  for (int i = 0; i < bookVector.size(); ++i) {
    if(matching_genre->matches(*bookVector.at(i))) {
      matching_genre_boolean = true;
    }
    if(non_matching_genre->matches(*bookVector.at(i))) {
      non_matching_genre_boolean = true;
    }
  }

  if(matching_genre_boolean == false) {
    cerr << *matching_genre << "This criteria was should have been matched " << endl;
    exit(EXIT_FAILURE);
  }

  if(non_matching_genre_boolean == true) {
    cerr << *non_matching_genre << "This criteria was should not have been matched. " << endl;
    exit(EXIT_FAILURE);
  }

  delete matching_genre;
  delete non_matching_genre;
}

void TestBook::testSubgenreCriteria() const {

  Criteria *matching_subgenre = new Subgenre_Criteria(bookVector.at(getRandomizedIndex())->getSubgenre());
  Criteria *non_matching_subgenre = new Subgenre_Criteria("This should not be a matching subgenre");

  bool matching_subgenre_boolean = false;
  bool non_matching_subgenre_boolean = false;

  for (int i = 0; i < bookVector.size(); ++i) {
    if(matching_subgenre->matches(*bookVector.at(i))) {
      matching_subgenre_boolean = true;
    }
    if(non_matching_subgenre->matches(*bookVector.at(i))) {
      non_matching_subgenre_boolean = true;
    }
  }

  if(matching_subgenre_boolean == false) {
    cerr << *matching_subgenre << "This criteria was should have been matched " << endl;
    exit(EXIT_FAILURE);
  }

  if(non_matching_subgenre_boolean == true) {
    cerr << *non_matching_subgenre << "This criteria was should not have been matched. " << endl;
    exit(EXIT_FAILURE);
  }

  delete matching_subgenre;
  delete non_matching_subgenre;
}

void TestBook::testPublisherCriteria() const {

  Criteria *matching_publisher = new Publisher_Criteria(bookVector.at(getRandomizedIndex())->getPublisher());
  Criteria *non_matching_publisher = new Publisher_Criteria("This should not be a matching publisher");

  bool matching_publisher_boolean = false;
  bool non_matching_publisher_boolean = false;

  for (int i = 0; i < bookVector.size(); ++i) {
    if(matching_publisher->matches(*bookVector.at(i))) {
      matching_publisher_boolean = true;
    }
    if(non_matching_publisher->matches(*bookVector.at(i))) {
      non_matching_publisher_boolean = true;
    }
  }

  if(matching_publisher_boolean == false) {
    cerr << *matching_publisher << "This criteria was should have been matched " << endl;
    exit(EXIT_FAILURE);
  }

  if(non_matching_publisher_boolean == true) {
    cerr << *non_matching_publisher << "This criteria was should not have been matched. " << endl;
    exit(EXIT_FAILURE);
  }

  delete matching_publisher;
  delete non_matching_publisher;
}

void TestBook::testPageCountCriteria() const {

  Page_Criteria *matching_pagecount = new Page_Criteria(bookVector.at(getRandomizedIndex())->getPageCount());
  Page_Criteria *non_matching_pagecount = new Page_Criteria(-1);
  Page_Criteria *less_than_pagecount = new Page_Criteria(1000000);
  Page_Criteria *more_than_pagecount = new Page_Criteria(-500);

  bool matching_pagecount_boolean = false;
  bool non_matching_pagecount_boolean = false;
  int less_than_pagecount_counter = 0;
  int more_than_pagecount_counter = 0;

  for (int i = 0; i < bookVector.size(); ++i) {
    if(matching_pagecount->matches(*bookVector.at(i))) {
      matching_pagecount_boolean = true;
    }
    if(non_matching_pagecount->matches(*bookVector.at(i))) {
      non_matching_pagecount_boolean = true;
    }
    if(less_than_pagecount->lessThan(*bookVector.at(i))) {
      ++less_than_pagecount_counter;
    }
    if(more_than_pagecount->moreThan(*bookVector.at(i))) {
      ++more_than_pagecount_counter;
    }
  }

  if(matching_pagecount_boolean == false) {
    cerr << *matching_pagecount << "This criteria was should have been matched " << endl;
    exit(EXIT_FAILURE);
  }

  if(non_matching_pagecount_boolean == true) {
    cerr << *non_matching_pagecount << "This criteria was should not have been matched. " << endl;
    exit(EXIT_FAILURE);
  }
  if(less_than_pagecount_counter != bookVector.size()) {
    cerr << "ERROR: The less than function is returning an incorrect amount of valid books. " << endl;
    exit(EXIT_FAILURE);
  }
  if(more_than_pagecount_counter != bookVector.size()) {
    cerr << "ERROR: The more than function is returning an incorrect amount of valid books. " << endl;
    exit(EXIT_FAILURE);
  }

  delete matching_pagecount;
  delete non_matching_pagecount;
  delete less_than_pagecount;
  delete more_than_pagecount;
}