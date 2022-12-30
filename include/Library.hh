/* Library.h */
/* */
/* Purpose: This is the header file for Library.cc. It contains the function prototypes/declarations for Library.cc and creates the class for Library. */
/* How to use the file: Link it as necessary with other files in the Makefile. */
/* Authors: Nguyen-Hanh Nong */
/* Revision: Revision 1.0 */
/* */

#ifndef LIBRARY_HPP
#define LIBRARY_HPP

/* Necessary libraries and imports */
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>

#include "Book.hh"
#include "Address.hh"
#include "Criteria.hh"

using namespace std;

class Library {
		
	public:
		//overloaded operators
		friend ostream& operator<<(ostream&, const Library&);
		bool operator==(const Library&) const;
    bool operator!=(const Library&) const;
		void operator=(const Library&);

		//constructors
		Library(const string& name = "Unknown Library Name", const Address& address = Address());
    ~Library();
		Library(const Library &copyLibrary);

		//getters
		const vector<Book *> &getBooks() const;
    const int getNextBookID() const;
    const int getBookCount() const;
    const string& getName() const;
    const Address& getAddress() const;

    //add functions
    bool addBook(const string& title, const string& author, const string& genre, const string& subgenre, const string& publisher, int pageCount);
    bool addBook(Book *book);

    //remove functions
    bool removeBook(Book *book, Book **removedBook);
    bool removeBookByCriteria(const Criteria *criteria, Book **removedBook);
    bool removeBookBySeveralCriteria(const vector<Criteria *> &criteriaVector, Book **removedBook);

    void emptyLibrary();

    //print formatting
		void defaultPrint(ostream &os) const;

    //get book functions
    bool getBookByCriteria(const Criteria &criteria, Book **book) const;
    bool getBooksByCriteria(const Criteria &criteria, vector<Book *> &books) const;
    bool getBookBySeveralCriteria(const vector<Criteria *> &criteriaVector, Book **book) const;
    bool getBooksBySeveralCriteria(const vector<Criteria *> &criteriaVector, vector<Book *> &books) const;

    //sort functions
    void sortBooksByOrderAdded();
    void sortBooksByTitle();
    void sortBooksByAuthor(); 
    void sortBooksByGenre();
    void sortBooksBySubgenre();
    void sortBooksByPublisher();
    void sortBooksByPageCount();

		//matching function
		bool matches(const Library &library) const;

	private:
    Address address;
    string name;
    vector<Book *> bookVector;
    int nextBookID;
};
#endif