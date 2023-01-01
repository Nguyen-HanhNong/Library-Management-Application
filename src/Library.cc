#include "Library.hh"

Library::Library(const string& name, const Address& address): address(address), name(name), bookVector(vector<Book*>()), nextBookID(0)
{
}

Library::~Library()
{
  emptyLibrary();
}

Library::Library(const Library &copyLibrary): address(copyLibrary.address), name(copyLibrary.name)
{
  for(long unsigned int i = 0; i < copyLibrary.bookVector.size(); ++i) {
    bookVector.push_back(new Book(*copyLibrary.bookVector[i]));
  }
}

const vector<Book *> &Library::getBooks() const {
  return this->bookVector;
}

const string& Library::getName() const {
  return this->name;
}

const int Library::getNextBookID() const {
  return this->nextBookID;
}

const int Library::getBookCount() const {
  return this->bookVector.size();
}

const Address& Library::getAddress() const {
  return this->address;
}

void Library::setName(const string& name) {
  this->name = name;
}

void Library::setAddress(const Address& address) {
  this->address = address;
}

bool Library::addBook(const string& title, const string& author, const string& genre, const string& subgenre, const string& publisher, int pageCount) {
  Book *book = new Book(title, author, genre, subgenre, publisher, pageCount, nextBookID);

  for(long unsigned int i = 0; i < bookVector.size(); ++i) {
    if(*bookVector[i] == *book) {
      delete book;
      cout << "Error: Book already exists in library." << endl;
      return false;
    }
  }

  bookVector.push_back(book);
  ++nextBookID;
  return true;
}

bool Library::addBook(Book *book) {
  for(long unsigned int i = 0; i < bookVector.size(); ++i) {
    if(*bookVector[i] == *book) {
      cout << "Error: Book already exists in library." << endl;
      return false;
    }
  }

  bookVector.push_back(book);
  ++nextBookID;
  return true;
}

bool Library::removeBook(Book *book, Book **removedBook) {
  for(long unsigned int i = 0; i < bookVector.size(); ++i) {
    if(*bookVector[i] == *book) {
      *removedBook = bookVector[i];
      bookVector.erase(bookVector.begin() + i);
      return true;
    }
  }

  *removedBook = NULL;
  cout << "Error: Book does not exist in the library." << endl;
  return false;
}

bool Library::removeBookByCriteria(const Criteria *criteria, Book **removedBook) {
  for(long unsigned int i = 0; i < bookVector.size(); ++i) {
    if(criteria->matches(*bookVector[i])) {
      *removedBook = bookVector[i];
      bookVector.erase(bookVector.begin() + i);
      return true;
    }
  }

  *removedBook = NULL;
  cout << "Error: Book does not exist in the library." << endl;
  return false;
}

bool Library::removeBookBySeveralCriteria(const vector<Criteria *> &criteria, Book **removedBook) {
  for(long unsigned int i = 0; i < bookVector.size(); ++i) {
    bool match = true;
    for(long unsigned int j = 0; j < criteria.size(); j++) {
      if(!criteria[j]->matches(*bookVector[i])) {
        match = false;
        break;
      }
    }

    if(match) {
      *removedBook = bookVector[i];
      bookVector.erase(bookVector.begin() + i);
      return true;
    }
  }

  *removedBook = NULL;
  cout << "Error: Book does not exist in the library." << endl;
  return false;
}

void Library::emptyLibrary() {
  while(bookVector.size() > 0) {
    delete bookVector.back();
    bookVector.pop_back();
  }
  bookVector.clear();
  nextBookID = 0;
}

void Library::defaultPrint(ostream &os) const {
  os << "The name of the library is: " << name << " and is at the following address: " << address << endl;
  os << "The books in the library: " << endl;
  for(long unsigned int i = 0; i < bookVector.size(); ++i) {
    os << *bookVector[i] << endl;
  }
}

void Library::printOnlyBooks(ostream &os) const {
  for(long unsigned int i = 0; i < bookVector.size(); ++i) {
    os << *bookVector[i] << endl;
  }
}

bool Library::getBookByCriteria(const Criteria &criteria, Book **book) const {
  for(long unsigned int i = 0; i < bookVector.size(); ++i) {
    if(criteria.matches(*bookVector[i])) {
      *book = bookVector[i];
      return true;
    }
  }

  *book = NULL;
  cout << "Error: Cannot find book as book does not exist in the library." << endl;
  return false;
}

bool Library::getBookBySeveralCriteria(const vector<Criteria *> &criteria, Book **book) const {
  for(long unsigned int i = 0; i < bookVector.size(); ++i) {
    bool match = true;
    for(long unsigned int j = 0; j < criteria.size(); j++) {
      if(!criteria[j]->matches(*bookVector[i])) {
        match = false;
        break;
      }
    }

    if(match) {
      *book = bookVector[i];
      return true;
    }
  }

  *book = NULL;
  cout << "Error: Cannot find book as book does not exist in the library." << endl;
  return false;
}

bool Library::getBooksByCriteria(const Criteria &criteria, vector<Book *> &books) const {
  for(long unsigned int i = 0; i < bookVector.size(); ++i) {
    if(criteria.matches(*bookVector[i])) {
      books.push_back(bookVector[i]);
    }
  }

  if(books.size() == 0) {
    cout << "Error: Cannot find books as books do not exist in the library." << endl;
    return false;
  }

  return true;
}

bool Library::getBooksBySeveralCriteria(const vector<Criteria *> &criteria, vector<Book *> &books) const {
  for(long unsigned int i = 0; i < bookVector.size(); ++i) {
    bool match = true;
    for(long unsigned int j = 0; j < criteria.size(); j++) {
      if(!criteria[j]->matches(*bookVector[i])) {
        match = false;
        break;
      }
    }

    if(match) {
      books.push_back(bookVector[i]);
    }
  }

  if(books.size() == 0) {
    cout << "Error: Cannot find books as books do not exist in the library." << endl;
    return false;
  }

  return true;
}

void Library::sortBooksByOrderAdded() {
  sort(bookVector.begin(), bookVector.end(), Book::compareOrderAdded);
}
void Library::sortBooksByTitle() {
  sort(bookVector.begin(), bookVector.end(), Book::compareTitle);
}
void Library::sortBooksByAuthor() {
  sort(bookVector.begin(), bookVector.end(), Book::compareAuthor);
}
void Library::sortBooksByGenre() {
  sort(bookVector.begin(), bookVector.end(), Book::compareGenre);
}
void Library::sortBooksBySubgenre() {
  sort(bookVector.begin(), bookVector.end(), Book::compareSubgenre);
}
void Library::sortBooksByPublisher() {
  sort(bookVector.begin(), bookVector.end(), Book::comparePublisher);
}
void Library::sortBooksByPageCount() {
  sort(bookVector.begin(), bookVector.end(), Book::comparePageCount);
}

bool Library::matches(const Library &library) const {
  if(address != library.address) {
    return false;
  }
  if(name != library.name) {
    return false;
  }
  if(bookVector.size() != library.bookVector.size()) {
    return false;
  }
  for(long unsigned int i = 0; i < bookVector.size(); ++i) {
    if(*bookVector[i] != *library.bookVector[i]) {
      return false;
    }
  }
  return true;
}

ostream& operator<<(ostream &os, const Library &library) {
  library.defaultPrint(os);
  return os;
}

bool Library::operator==(const Library &library) const {
  return matches(library);
}

bool Library::operator!=(const Library &library) const {
  return !matches(library);
}

void Library::operator=(const Library &library) {
  address = library.address;
  name = library.name;
  for(long unsigned int i = 0; i < bookVector.size(); ++i) {
    delete bookVector[i];
  }
  bookVector.clear();
  for(long unsigned int i = 0; i < library.bookVector.size(); ++i) {
    bookVector.push_back(new Book(*library.bookVector[i]));
  }
}

