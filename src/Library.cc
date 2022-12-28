#include "Library.hh"

static int nextBookID = 0;

Library::Library(const string& name, const Address& address): address(address), name(name), bookVector(bookVector)
{
}

Library::~Library()
{
  for(int i = 0; i < bookVector.size(); i++) {
    delete bookVector[i];
  }
}

Library::Library(const Library &copyLibrary): address(copyLibrary.address), name(copyLibrary.name)
{
  for(int i = 0; i < copyLibrary.bookVector.size(); i++) {
    bookVector.push_back(new Book(*copyLibrary.bookVector[i]));
  }
}

const vector<Book *> &Library::getBooks() const {
  return this->bookVector;
}

const string& Library::getName() const {
  return this->name;
}

int Library::getNextBookID() const {
  return nextBookID;
}

const Address& Library::getAddress() const {
  return this->address;
}

bool Library::addBook(const string& title, const string& author, const string& genre, const string& subgenre, const string& publisher, int pageCount) {
  Book *book = new Book(title, author, genre, subgenre, publisher, pageCount, nextBookID);

  for(int i = 0; i < bookVector.size(); i++) {
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
  for(int i = 0; i < bookVector.size(); i++) {
    if(*bookVector[i] == *book) {
      cout << "Error: Book already exists in library." << endl;
      return false;
    }
  }

  bookVector.push_back(book);
  ++nextBookID;
  return true;
}

bool Library::removeBook(Book *book) {
  for(int i = 0; i < bookVector.size(); i++) {
    if(*bookVector[i] == *book) {
      bookVector.erase(bookVector.begin() + i);
      return true;
    }
  }

  cout << "Error: Book does not exist in the library." << endl;
  return false;
}

bool Library::removeBookByCriteria(const Criteria &criteria) {
  for(int i = 0; i < bookVector.size(); i++) {
    if(criteria.matches(*bookVector[i])) {
      bookVector.erase(bookVector.begin() + i);
      return true;
    }
  }

  cout << "Error: Book does not exist in the library." << endl;
  return false;
}

bool Library::removeBooks(Book *book) {
  bool removed = false;
  for(int i = 0; i < bookVector.size(); i++) {
    if(*bookVector[i] == *book) {
      bookVector.erase(bookVector.begin() + i);
      removed = true;
    }
  }

  if(!removed) {
    cout << "Error: No books matching the book passed in were able to be removed. " << endl;
  }

  return removed;
}

bool Library::removeBooksByCriteria(const Criteria &criteria) {
  bool removed = false;
  for(int i = 0; i < bookVector.size(); i++) {
    if(criteria.matches(*bookVector[i])) {
      bookVector.erase(bookVector.begin() + i);
      removed = true;
    }
  }

  if(!removed) {
    cout << "Error: No books matching the criteria were able to be removed. " << endl;
  }

  return removed;
}

bool Library::removeBooksBySeveralCriteria(const vector<Criteria> &criteriaVector) {
  bool removed = false;
  bool matchAllCriteria = true;

  for(int i = 0; i < bookVector.size(); i++) {
    int matchingCriteriaCount = 0;
    for(int j = 0; j < criteriaVector.size(); j++) {
      if(criteriaVector[j].matches(*bookVector[i])) {
        ++matchingCriteriaCount;
      }
    }

    if(matchingCriteriaCount == criteriaVector.size()) {
      bookVector.erase(bookVector.begin() + i);
      removed = true;
    }
  }

  if(!removed) {
    cout << "Error: No books matching the criteria were able to be removed. " << endl;
  }

  return removed;
}

void Library::defaultPrint(ostream &os) const {
  os << "The name of the library is: " << name << " and is at the following address: " << address << endl;
  os << "The books in the library: " << endl;
  for(int i = 0; i < bookVector.size(); i++) {
    os << *bookVector[i] << endl;
  }
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
  for(int i = 0; i < bookVector.size(); i++) {
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
  for(int i = 0; i < bookVector.size(); i++) {
    delete bookVector[i];
  }
  bookVector.clear();
  for(int i = 0; i < library.bookVector.size(); i++) {
    bookVector.push_back(new Book(*library.bookVector[i]));
  }
}