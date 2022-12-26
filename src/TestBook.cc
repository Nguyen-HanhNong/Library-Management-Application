#include "TestBook.hh"

std::random_device rd; 
std::mt19937 gen(rd());

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
    fileLocation = "..\books\test_books.csv";
  #elif __linux__
    fileLocation = "../books/test_books.csv";
  #elif __unix__
    fileLocation = "../books/test_books.csv";
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

    bookVector.push_back(new Book(currentLine.at(0), currentLine.at(1), currentLine.at(2), currentLine.at(3), currentLine.at(5), stoi(currentLine.at(4))));
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
  }

  cout << "Successfully passed all criteria tests!" << endl;
}

void TestBook::testTitleCriteria() const {
  std::uniform_int_distribution<> distr(0, bookVector.size() - 1);

  Criteria *matching_title = new Title_Criteria(bookVector.at(distr(gen))->getTitle());
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
}
