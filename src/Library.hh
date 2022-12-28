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
		Library(const string& name = "Unknown Name", const Address& address = Address());
		Library(const Library &copyLibrary);

		//getters
		const vector<Book *> &getBooks() const;
    int getNextBookID() const;
    const string& getName() const;
    const Address& getAddress() const;

    //add functions
    bool addBook(const string& title, const string& author, const string& genre, const string& subgenre, const string& publisher, int pageCount);
    bool addBook(Book *book);

    //remove functions
    bool removeBook(Book *book);
    bool removeBookByCriteria(const Criteria &criteria);

    bool removeBooks(Book *book);
    bool removeBooksByCriteria(const Criteria &criteria);
    bool removeBooksBySeveralCriteria(const vector<Criteria> &criteriaVector);
    
		//print formatting
		void defaultPrint(ostream &os) const;

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
    vector<Book *> bookVector;
    Address address;
    string name;
    static int nextBookID;
};
#endif