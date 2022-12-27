/* Criteria.cc */
/* */
/* Purpose: This is a .CC file that contains the implentations of the Criteria.h header file, and contains the functions and variables necessary for a Criteria and all its respective subclasses.  */
/* How to use the file: Link it as necessary with other files in the Makefile. */
/* Authors: Nguyen-Hanh Nong */
/* Revision: Revision 1.0 */
/* */

#include "Criteria.hh"

/* This function overloads the << operator for Criteria and it's subclasses */
ostream& operator<<(ostream& os, const Criteria& criteria){ 
  /* Call the print function of the Criteria and pass in the ostream object */
  criteria.print(os);
  return os;
}

Title_Criteria::Title_Criteria(const string &title): title(title) 
{
}

Author_Criteria::Author_Criteria(const string &author): author(author) 
{
}

Genre_Criteria::Genre_Criteria(const string &genre): genre(genre) 
{
}

Subgenre_Criteria::Subgenre_Criteria(const string &subgenre): subgenre(subgenre) 
{
}

Publisher_Criteria::Publisher_Criteria(const string &publisher): publisher(publisher) 
{
}

Page_Criteria::Page_Criteria(const int pageCount): pageCount(pageCount) 
{
}

Criteria::~Criteria() 
{
}
Title_Criteria::~Title_Criteria() 
{
}
Author_Criteria::~Author_Criteria() 
{
}
Genre_Criteria::~Genre_Criteria() 
{
}
Subgenre_Criteria::~Subgenre_Criteria() 
{
}
Publisher_Criteria::~Publisher_Criteria() 
{
}
Page_Criteria::~Page_Criteria() 
{
}

bool Title_Criteria::matches(const Book &book) const {
  return book.getTitle().compare(title) == 0;
}

bool Author_Criteria::matches(const Book &book) const {
  return book.getAuthor().compare(author) == 0;
}

bool Genre_Criteria::matches(const Book &book) const {
  return book.getGenre().compare(genre) == 0;
}

bool Subgenre_Criteria::matches(const Book &book) const {
  return book.getSubgenre().compare(subgenre) == 0;
}

bool Publisher_Criteria::matches(const Book &book) const {
  return book.getPublisher().compare(publisher) == 0;
}

bool Page_Criteria::matches(const Book &book) const {
  return book.getPageCount() == pageCount;
}

bool Page_Criteria::lessThan(const Book &book) const {
  return book.getPageCount() < pageCount;
}

bool Page_Criteria::moreThan(const Book &book) const {
  return book.getPageCount() > pageCount;
}

void Title_Criteria::print(ostream &os) const {
  os << "To match the title criteria, the book must have the same title as: " << this->title << endl;
}

void Author_Criteria::print(ostream &os) const {
  os << "To match the author criteria, the book must have the same author as: " << this->author << endl;
}

void Genre_Criteria::print(ostream &os) const {
  os << "To match the genre criteria, the book must have the same genre as: " << this->genre << endl;
}

void Subgenre_Criteria::print(ostream &os) const {
  os << "To match the subgenre criteria, the book must have the same subgenre as: " << this->subgenre << endl;
}

void Publisher_Criteria::print(ostream &os) const {
  os << "To match the publisher criteria, the book must have the same publisher as: " << this->publisher << endl;
}

void Page_Criteria::print(ostream &os) const {
  os << "To match the page criteria, the book must have the same number of pages as: " << this->pageCount << endl;
}
