#include "Library.hh"

static int nextBookID = 0;

Library::Library(vector <Book *> bookVector, const Address& address): bookVector(bookVector), address(address) 
{ 
}

Library::~Library()
{
  for(int i = 0; i < bookVector.size(); i++) {
    delete bookVector[i];
  }
}

Library::Library(const Library &copyLibrary): address(copyLibrary.address)
{
  for(int i = 0; i < copyLibrary.bookVector.size(); i++) {
    bookVector.push_back(new Book(*copyLibrary.bookVector[i]));
  }
}

const vector<Book *> &Library::getBooks() const {
  return this->bookVector;
}

const Address& Library::getAddress() const {
  return this->address;
}

bool Library::addBook(Book *book) {
  for(int i = 0; i < bookVector.size(); i++) {
    if(*bookVector[i] == *book) {
      return false;
    }
  }
  bookVector.push_back(book);
  return true;
}

bool Library::removeBook(Book *book) {
  for(int i = 0; i < bookVector.size(); i++) {
    if(*bookVector[i] == *book) {
      bookVector.erase(bookVector.begin() + i);
      return true;
    }
  }
  return false;
}

void Library::defaultPrint(ostream &os) const {
  os << "The library is at the following address: " << address << endl;
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
  for(int i = 0; i < bookVector.size(); i++) {
    delete bookVector[i];
  }
  bookVector.clear();
  for(int i = 0; i < library.bookVector.size(); i++) {
    bookVector.push_back(new Book(*library.bookVector[i]));
  }
}