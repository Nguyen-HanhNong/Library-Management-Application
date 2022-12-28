/* Book.h */
/* */
/* Purpose: This is the header file for Book.cc. It contains the function prototypes/declarations for Book.cc and creates the class for Book. */
/* How to use the file: Link it as necessary with other files in the Makefile. */
/* Authors: Nguyen-Hanh Nong */
/* Revision: Revision 1.0 */
/* */

#ifndef BOOK_HPP
#define BOOK_HPP

/* Necessary libraries and imports */
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

#define NUM_BOOK_PROPERTIES 6

class Book {
		
	public:
		//overloaded operators
		friend ostream& operator<<(ostream&, const Book&);
		bool operator==(const Book&) const;
		void operator=(const Book&);
		bool operator!=(const Book&) const;

		//constructors
		Book(const string& title = "Unknown Title", const string& author = "Unknown Author", const string& genre = "Unknown Genre", const string& subgenre = "Unknown Subgenre", const string& publisher = "Unknown Publisher", int pageCount = 0, const int ID = 0);
		Book(const Book &copyBook);

		//getters
		const string& getTitle() const;
		const string& getAuthor() const;
		const string& getGenre() const;
		const string& getSubgenre() const;
		const string& getPublisher() const;
		const int getPageCount() const;
		const int getID() const;

		//comparison functions
		static bool compareOrderAdded(const Book *book1, const Book *book2);
		static bool compareTitle(const Book *book1, const Book *book2);
		static bool compareAuthor(const Book *book1, const Book *book2);
		static bool compareGenre(const Book *book1, const Book *book2);
		static bool compareSubgenre(const Book *book1, const Book *book2);
		static bool comparePublisher(const Book *book1, const Book *book2);
		static bool comparePageCount(const Book *book1, const Book *book2);

		//print formatting
		void print(ostream &os) const;

		//matching function
		bool matches(const Book &book) const;

	private:
		string title;		//title of the book
		string author;	//artist of the book
		string genre;		//category of the book
		string subgenre; //subgenre of the book
		string publisher; // publisher of the book
		int pageCount; //number of pages in book
		int ID; //unique ID of book
};
#endif