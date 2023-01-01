#ifndef LIBRARYMANAGER_HPP
#define LIBRARYMANAGER_HPP

#include <iostream>
#include <iomanip>
#include <string>

#include "Library.hh"

using namespace std;

class LibraryManager {
	public:
    LibraryManager();
    ~LibraryManager();

    bool addLibrary(Library *library);
    bool removeLibrary(Library *library);
    bool getLibrary(const string &libraryName, Library **library) const;

    void printLibraries() const;
    bool printLibrary(const string &libraryName) const;
    bool printLibraryBooks(const string &libraryName) const;

    bool moveBook(const string &bookName, const string &fromLibrary, const string &toLibrary);

    int getNumberOfLibraries() const;

    void clearAllLibraries();

	private:
    vector<Library *>* libraries;

};
#endif