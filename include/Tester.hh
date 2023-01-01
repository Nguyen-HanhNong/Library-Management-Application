/* Tester.hh */
/* Author: Nguyen-Hanh Nong */
/* Revision: Revision 1.0 */
/* */
/* This is the header file for the Tester class which contains the various classes involved with testing each of the component class including Book, Library and LibraryManager. */

#ifndef TESTER_HPP
#define TESTER_HPP

// Necessary libraries and imports
#include <iostream>
#include <string>
#include "TestBook.hh"
#include "TestLibrary.hh"
#include "TestLibraryManager.hh"

using namespace std;

/* Tester class declaration */
class Tester {
		
	public:
		/* Constructors and destructors */
		Tester();
		~Tester();

		void launch(int& choice); //Launches the various testers
	
	private:
		TestBook* bookTester;												//Tester for the Book class
		TestLibrary* libraryTester;									//Tester for the Library class
		TestLibraryManager* libraryManagerTester;   //Tester for the LibraryManager class

};
#endif