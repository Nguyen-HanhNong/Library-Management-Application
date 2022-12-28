#include "TestLibrary.hh"

TestLibrary::TestLibrary(): library(Library("Test Library", Address("123 Test Street", "Test City", "Test Province", "12345"))) 
{
} 

TestLibrary::~TestLibrary()
{
}

void TestLibrary::launch(){
  testGetterFunctions();
}

void TestLibrary::testGetterFunctions() {
  testGetBooks();
  testGetNextBookID();
  testGetName();
  testGetAddress();

  cout << "SUCCESS: All getter functions passed" << endl;
}

void TestLibrary::initLibraryFromFile(Library& library) {
  library.emptyLibrary();

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

    library.addBook(new Book(currentLine.at(0), currentLine.at(1), currentLine.at(2), currentLine.at(3), currentLine.at(5), stoi(currentLine.at(4)), library.getNextBookID()));
  }

  file.close();
}

void TestLibrary::testGetBooks() {
  initLibraryFromFile(library);

  vector<Book *> books = library.getBooks();

  if(books.size() != 10) {
    cerr << "Error: There should be 10 books in the library." << endl;
    exit(EXIT_FAILURE);
  }

  cout << "Test 1: Get Books function: Passed" << endl;
}

void TestLibrary::testGetNextBookID() {
  library.emptyLibrary();

  if(library.getNextBookID() != 0) {
    cerr << "Error: The next book ID should be 0." << endl;
    exit(EXIT_FAILURE);
  }

  initLibraryFromFile(library);

  int nextBookID = library.getNextBookID();
  int lastBookID = library.getBooks().back()->getID();

  if(nextBookID != lastBookID + 1) {
    cerr << "Error: The next book ID should be the last book ID + 1." << endl;
    exit(EXIT_FAILURE);
  }

  cout << "Test 2: Get Next Book ID function: Passed" << endl;
}

void TestLibrary::testGetName() {
  if(library.getName() != "Test Library") {
    cerr << "Error: The name of the library should be Test Library." << endl;
    exit(EXIT_FAILURE);
  }

  Library library2 = Library("Test Library 2", Address("123 Test Street", "Test City", "Test Province", "12345"));
  Library defaultLibrary = Library();

  if(library2.getName() != "Test Library 2") {
    cerr << "Error: The name of the library should be Test Library 2." << endl;
    exit(EXIT_FAILURE);
  }
  if(defaultLibrary.getName() != "Unknown Library Name") {
    cerr << "Error: The name of the library should be Unknown Library." << endl;
    exit(EXIT_FAILURE);
  }

  cout << "Test 3: Get Name function: Passed" << endl;
}

void TestLibrary::testGetAddress() {
  Address address = Address("123 Test Street", "Test City", "Test Province", "12345");
  Address defaultAddress = Address();

  if(library.getAddress() != address) {
    cerr << "Error: The address of the library should be 123 Test Street, Test City, Test Province, 12345." << endl;
    exit(EXIT_FAILURE);
  }
  if(defaultAddress.getStreetNumber() != "Unknown Street Number") {
    cerr << "Error: The street number of the address should be Unknown Street Number." << endl;
    exit(EXIT_FAILURE);
  }
  if(defaultAddress.getStreetName() != "Unknown Street") {
    cerr << "Error: The street of the address should be Unknown Street." << endl;
    exit(EXIT_FAILURE);
  }
  if(defaultAddress.getCityName() != "Unknown City") {
    cerr << "Error: The city of the address should be Unknown City." << endl;
    exit(EXIT_FAILURE);
  }
  if(defaultAddress.getProvinceName() != "Unknown Province") {
    cerr << "Error: The province of the address should be Unknown Province." << endl;
    exit(EXIT_FAILURE);
  }
  if(defaultAddress.getPostalCode() != "Unknown Postal Code") {
    cerr << "Error: The postal code of the address should be Unknown Postal Code." << endl;
    exit(EXIT_FAILURE);
  }

  cout << "Test 4: Get Address function: Passed" << endl;
}

void TestLibrary::testMatchingBooks() {
  library.emptyLibrary();

  Book *book1 = new Book("Book 1", "Author 1", "Genre 1", "Subgenre 1", "Publisher 1", 100);
  Book *book2 = new Book("Book 2", "Author 2", "Genre 2", "Subgenre 2", "Publisher 2", 200);

  if(library.addBook(book1) == false) {
    cerr << "Error: Book 1 should be able to be added to the library." << endl;
    exit(EXIT_FAILURE);
  }
  if(library.addBook(book2) == false) {
    cerr << "Error: Book 2 should be able to be added to the library." << endl;
    exit(EXIT_FAILURE);
  }
  if(library.addBook(book1) == true) {
    cerr << "Error: Book 1 should not be able to be added to the library." << endl;
    exit(EXIT_FAILURE);
  }

  cout << "Test 5: Matching Books Cannot Be Added: Passed" << endl;
}





