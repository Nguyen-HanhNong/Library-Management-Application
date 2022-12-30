#include "TestLibrary.hh"

TestLibrary::TestLibrary(): library(Library("Test Library", Address("123 Test Street", "Test City", "Test Province", "12345"))) 
{
} 

TestLibrary::~TestLibrary()
{
}

void TestLibrary::launch(){
  testGetterFunctions();
  testAddFunctions();
  testRemoveFunctions();
  testGetFunctions();
  testSortFunctions();
}

void TestLibrary::testGetterFunctions() {
  testGetBooks();
  testGetNextBookID();
  testGetName();
  testGetAddress();

  cout << "SUCCESS: All getter functions passed" << endl;
}

void TestLibrary::testAddFunctions() {
  testMatchingBooks();
  testAddBooks();

  cout << "SUCCESS: All adder functions passed" << endl;
}

void TestLibrary::testRemoveFunctions() {
  testRemoveBook();

  for (int i = 0; i < MAX_ATTEMPTS_PER_TEST; ++i) {
    testRemoveBookByCriteria();
    testRemoveBookBySeveralCriteria();
  }

  cout << "SUCCESS: All remove functions passed" << endl;
}

void TestLibrary::testGetFunctions() {
  for (int i = 0; i < MAX_ATTEMPTS_PER_TEST; ++i) {
    testGetBookByCriteria();
    testGetBooksByCriteria();
    testGetBookBySeveralCriteria();
    testGetBooksBySeveralCriteria();
  }

  cout << "SUCCESS: All get books functions passed" << endl;
}

void TestLibrary::testSortFunctions() {
  testSortByTitle();
  testSortByAuthor();
  testSortByGenre();
  testSortBySubgenre();
  testSortByPublisher();
  testSortByPageCount();

  cout << "SUCCESS: All sorting functions passed" << endl;
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

const int TestLibrary::getRandomizedIndex() const {
  std::random_device rd; 
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distr(0, library.getBookCount() - 1);

  const int returnInteger = distr(gen);

  return returnInteger;
}

void TestLibrary::testGetBooks() {
  initLibraryFromFile(library);

  vector<Book *> books = library.getBooks();

  if(books.size() != 10) {
    cerr << "Error: There should be 10 books in the library." << endl;
    exit(EXIT_FAILURE);
  }

  books.clear();
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

void TestLibrary::testAddBooks() {
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

  vector<Book *> books = library.getBooks();

  if(books.size() != 2) {
    cerr << "Error: There should be 2 books in the library." << endl;
    exit(EXIT_FAILURE);
  }
  if(*books.at(0) != *book1) {
    cerr << "Error: The first book in the library should be Book 1." << endl;
    exit(EXIT_FAILURE);
  }
  if(*books.at(1) != *book2) {
    cerr << "Error: The second book in the library should be Book 2." << endl;
    exit(EXIT_FAILURE);
  }

  cout << "Test 6: Add Books function: Passed" << endl;
}

void TestLibrary::testRemoveBook() {
  library.emptyLibrary();

  Book *book1 = new Book("Book 1", "Author 1", "Genre 1", "Subgenre 1", "Publisher 1", 100);
  Book *book2 = new Book("Book 2", "Author 2", "Genre 2", "Subgenre 2", "Publisher 2", 200);
  Book *removedBook1;

  if(library.addBook(book1) == false) {
    cerr << "Error: Book 1 should be able to be added to the library." << endl;
    exit(EXIT_FAILURE);
  }
  if(library.addBook(book2) == false) {
    cerr << "Error: Book 2 should be able to be added to the library." << endl;
    exit(EXIT_FAILURE);
  }

  if(library.removeBook(book1, &removedBook1) == false) {
    cerr << "Error: Book 1 should be able to be removed from the library." << endl;
    exit(EXIT_FAILURE);
  }

  if(library.removeBook(book1, &removedBook1) == true) {
    cerr << "Error: Book 1 should not be able to be removed from the library." << endl;
    exit(EXIT_FAILURE);
  }

  if(library.getBookCount() != 1) {
    cerr << "Error: There should be 1 book in the library." << endl;
    exit(EXIT_FAILURE);
  }
  if(*library.getBooks().at(0) != *book2) {
    cerr << "Error: The first book in the library should be Book 2." << endl;
    exit(EXIT_FAILURE);
  }

  delete book1;
  initLibraryFromFile(library);

  for(int i = 0; i < 10; ++i) {
    Book *removedBook;
    if (library.removeBook(library.getBooks().at(0), &removedBook) == false) {
      cerr << "Error: Book " << "0" << " should be able to be removed from the library." << endl;
      exit(EXIT_FAILURE);
    }
    delete removedBook;
  }

  if(library.getBookCount() != 0) {
    cerr << "Error: There should be 0 books in the library." << endl;
    exit(EXIT_FAILURE);
  }

  cout << "Test 7: Remove Book function: Passed" << endl;
}

void TestLibrary::testRemoveBookByCriteria() {
  initLibraryFromFile(library);

  int startingSize = library.getBookCount();
  Book *removedTitleBook;
  Book *removedAuthorBook;
  Book *removedGenreBook;
  Book *removedSubgenreBook;
  Book *removedPublisherBook;
  Book *removedPageCountBook;

  int randomTitleIndex = getRandomizedIndex();
  Book *titleBook = library.getBooks().at(randomTitleIndex);
  Criteria *titleCriteria = new Title_Criteria(titleBook->getTitle());

  if(library.removeBookByCriteria(titleCriteria, &removedTitleBook) == false) {
    cerr << "Error: Book " << titleBook->getTitle() << " should be able to be removed from the library." << endl;
    exit(EXIT_FAILURE);
  }

  int randomAuthorIndex = getRandomizedIndex();
  Book *authorBook = library.getBooks().at(randomAuthorIndex);
  Criteria *authorCriteria = new Author_Criteria(authorBook->getAuthor());

  if(library.removeBookByCriteria(authorCriteria, &removedAuthorBook) == false) {
    cerr << "Error: Book " << authorBook->getTitle() << " should be able to be removed from the library." << endl;
    exit(EXIT_FAILURE);
  }

  int randomGenreIndex = getRandomizedIndex();
  Book *genreBook = library.getBooks().at(randomGenreIndex);
  Criteria *genreCriteria = new Genre_Criteria(genreBook->getGenre());

  if(library.removeBookByCriteria(genreCriteria, &removedGenreBook) == false) {
    cerr << "Error: Book " << genreBook->getTitle() << " should be able to be removed from the library." << endl;
    exit(EXIT_FAILURE);
  }

  int randomSubgenreIndex = getRandomizedIndex();
  Book *subgenreBook = library.getBooks().at(randomSubgenreIndex);
  Criteria *subgenreCriteria = new Subgenre_Criteria(subgenreBook->getSubgenre());

  if(library.removeBookByCriteria(subgenreCriteria, &removedSubgenreBook) == false) {
    cerr << "Error: Book " << subgenreBook->getTitle() << " should be able to be removed from the library." << endl;
    exit(EXIT_FAILURE);
  }

  int randomPublisherIndex = getRandomizedIndex();
  Book *publisherBook = library.getBooks().at(randomPublisherIndex);
  Criteria *publisherCriteria = new Publisher_Criteria(publisherBook->getPublisher());

  if(library.removeBookByCriteria(publisherCriteria, &removedPublisherBook) == false) {
    cerr << "Error: Book " << publisherBook->getTitle() << " should be able to be removed from the library." << endl;
    exit(EXIT_FAILURE);
  }

  int randomPagesIndex = getRandomizedIndex();
  Book *pagesBook = library.getBooks().at(randomPagesIndex);
  Criteria *pagesCriteria = new Page_Criteria(pagesBook->getPageCount());

  if(library.removeBookByCriteria(pagesCriteria, &removedPageCountBook) == false) {
    cerr << "Error: Book " << pagesBook->getTitle() << " should be able to be removed from the library." << endl;
    exit(EXIT_FAILURE);
  }

  if(library.getBookCount() != startingSize - 6) {
    cerr << "Error: There should be " << startingSize - 6 << " books in the library." << endl;
    exit(EXIT_FAILURE);
  }

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

  for (int i = 0; i < library.getBooks().size(); ++i) {
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

  for (int i = 0; i < foundBooks.size(); ++i) {
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

  for(int i = 0; i < foundBooks.size(); ++i) {
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

  for(int i = 0; i < library.getBooks().size() - 1; ++i) {
    if(library.getBooks().at(i)->getID() > library.getBooks().at(i + 1)->getID()) {
      cerr << "Error: Books are not sorted by order added." << endl;
      exit(EXIT_FAILURE);
    }
  }

  cout << "Test 14: Sort Books by Order Added function: Passed" << endl;
}

void TestLibrary::testSortByTitle() {
  initLibraryFromFile(library);

  library.sortBooksByTitle();

  for(int i = 0; i < library.getBooks().size() - 1; ++i) {
    if(library.getBooks().at(i)->getTitle() > library.getBooks().at(i + 1)->getTitle()) {
      cerr << "Error: Books are not sorted by title." << endl;
      exit(EXIT_FAILURE);
    }
  }

  cout << "Test 15: Sort Books by Title function: Passed" << endl;
}

void TestLibrary::testSortByAuthor() {
  initLibraryFromFile(library);

  library.sortBooksByAuthor();

  for(int i = 0; i < library.getBooks().size() - 1; ++i) {
    if(library.getBooks().at(i)->getAuthor() > library.getBooks().at(i + 1)->getAuthor()) {
      cerr << "Error: Books are not sorted by author." << endl;
      exit(EXIT_FAILURE);
    }
  }

  cout << "Test 16: Sort Books by Author function: Passed" << endl;
}

void TestLibrary::testSortByGenre() {
  initLibraryFromFile(library);

  library.sortBooksByGenre();

  for(int i = 0; i < library.getBooks().size() - 1; ++i) {
    if(library.getBooks().at(i)->getGenre() > library.getBooks().at(i + 1)->getGenre()) {
      cerr << "Error: Books are not sorted by genre." << endl;
      exit(EXIT_FAILURE);
    }
  }

  cout << "Test 17: Sort Books by Genre function: Passed" << endl;
}

void TestLibrary::testSortBySubgenre() {
  initLibraryFromFile(library);

  library.sortBooksBySubgenre();

  for(int i = 0; i < library.getBooks().size() - 1; ++i) {
    if(library.getBooks().at(i)->getSubgenre() > library.getBooks().at(i + 1)->getSubgenre()) {
      cerr << "Error: Books are not sorted by subgenre." << endl;
      exit(EXIT_FAILURE);
    }
  }

  cout << "Test 18: Sort Books by Subgenre function: Passed" << endl;
}

void TestLibrary::testSortByPublisher() {
  initLibraryFromFile(library);

  library.sortBooksByPublisher();

  for(int i = 0; i < library.getBooks().size() - 1; ++i) {
    if(library.getBooks().at(i)->getPublisher() > library.getBooks().at(i + 1)->getPublisher()) {
      cerr << "Error: Books are not sorted by publisher." << endl;
      exit(EXIT_FAILURE);
    }
  }

  cout << "Test 19: Sort Books by Publisher function: Passed" << endl;
}

void TestLibrary::testSortByPageCount() {
  initLibraryFromFile(library);

  library.sortBooksByPageCount();

  for(int i = 0; i < library.getBooks().size() - 1; ++i) {
    if(library.getBooks().at(i)->getPageCount() > library.getBooks().at(i + 1)->getPageCount()) {
      cerr << "Error: Books are not sorted by pages." << endl;
      exit(EXIT_FAILURE);
    }
  }

  cout << "Test 20: Sort Books by Pages function: Passed" << endl;
}

