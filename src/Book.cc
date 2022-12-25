/* Book.cc */
/* */
/* Purpose: This is a .CC file that contains the implentations of the Book.h header file, and contains the functions and variables necessary for a Book. */
/* How to use the file: Link it as necessary with other files in the Makefile. */
/* Authors: Nguyen-Hanh Nong */
/* Revision: Revision 1.0 */
/* */

#include "Book.hh"

Book::Book(const string& title, const string& author, const string& genre, const string& subgenre, const string& publisher, int pageCount): title(title), author(author), genre(genre), subgenre(subgenre), publisher(publisher), pageCount(pageCount)
{
}

Book::Book(const Book &copyBook) {
  this->title = copyBook.title;
  this->author = copyBook.author;
  this->genre = copyBook.genre;
  this->subgenre = copyBook.subgenre;
  this->publisher = copyBook.publisher;
  this->pageCount = copyBook.pageCount;
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

ostream& operator<<(ostream& os, const Book& book) {
  book.print(os);
  return os;
}

bool operator==(const Book& firstBook, const Book& secondBook) {
  return firstBook.title == secondBook.title && firstBook.author == secondBook.author && firstBook.genre == secondBook.genre && firstBook.subgenre == secondBook.subgenre && firstBook.publisher == secondBook.publisher && firstBook.pageCount == secondBook.pageCount;
}