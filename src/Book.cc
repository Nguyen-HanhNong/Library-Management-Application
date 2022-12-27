/* Book.cc */
/* */
/* Purpose: This is a .CC file that contains the implentations of the Book.h header file, and contains the functions and variables necessary for a Book. */
/* How to use the file: Link it as necessary with other files in the Makefile. */
/* Authors: Nguyen-Hanh Nong */
/* Revision: Revision 1.0 */
/* */

#include "Book.hh"

Book::Book(const string& title, const string& author, const string& genre, const string& subgenre, const string& publisher, int pageCount, const int ID): title(title), author(author), genre(genre), subgenre(subgenre), publisher(publisher), pageCount(pageCount), ID(ID)
{
}

Book::Book(const Book &copyBook): title(copyBook.title), author(copyBook.author), genre(copyBook.genre), subgenre(copyBook.subgenre), publisher(copyBook.publisher), pageCount(copyBook.pageCount)
{
}

const string& Book::getTitle() const {
  return this->title;
}

const string& Book::getAuthor() const {
  return this->author;
}

const string& Book::getGenre() const {
  return this->genre;
}

const string& Book::getSubgenre() const {
  return this->subgenre;
}

const string& Book::getPublisher() const {
  return this->publisher;
}

const int Book::getPageCount() const {
  return this->pageCount;
}

void Book::print(ostream &os) const {
  os << "This book is named " << this->title << " and is written by " << this->author << ".\n The genre and subgenre of the book is the following " << this->genre << ", " << this->subgenre << ". \n This book is published by " << this->publisher << " and has " << this->pageCount << " pages. " << endl;
}

bool Book::matches(const Book &book) const {
  if(this->author.compare(book.author) != 0 || this->title.compare(book.title) != 0 || this->genre.compare(book.genre) != 0 || this->subgenre.compare(book.subgenre) != 0 || this->publisher.compare(book.publisher) != 0 || this->pageCount != book.pageCount) {
    return false;
  } else {
    return true;
  }
}

ostream& operator<<(ostream& os, const Book& book) {
  book.print(os);
  return os;
}

bool Book::operator!=(const Book& secondBook) const {
  return !this->matches(secondBook);
}

bool Book::operator==(const Book& secondBook) const {
  return this->matches(secondBook);
}

void Book::operator=(const Book& book) {
  this->title = book.title;
  this->author = book.author;
  this->genre = book.genre;
  this->subgenre = book.subgenre;
  this->publisher = book.publisher;
  this->pageCount = book.pageCount;
}

bool Book::compareOrderAdded(const Book *book1, const Book *book2) {
  return book1->ID < book2->ID;
}
bool Book::compareTitle(const Book *book1, const Book *book2) {
  return book1->title.compare(book2->title) < 0;
}
bool Book::compareAuthor(const Book *book1, const Book *book2) {
  return book1->author.compare(book2->author) < 0;
}
bool Book::compareGenre(const Book *book1, const Book *book2) {
  return book1->genre.compare(book2->genre) < 0;
}
bool Book::compareSubgenre(const Book *book1, const Book *book2) {
  return book1->subgenre.compare(book2->subgenre) < 0;
}
bool Book::comparePublisher(const Book *book1, const Book *book2) {
  return book1->publisher.compare(book2->publisher) < 0;
}
bool Book::comparePageCount(const Book *book1, const Book *book2) {
  return book1->pageCount < book2->pageCount;
}
