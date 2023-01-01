#ifndef VIEW_HPP
#define VIEW_HPP

#include <iostream>
#include <string>
#include <limits>

#include "Library.hh"
#include "Algorithms.hh"

using namespace std;

class View {
	public:
    View();
    ~View();

    void mainMenu(int& choice) const;
    
    void testerMainMenu(int& choice) const;

    void starterLibraryMenu(int& choice) const;

    void createLibraryMenu(Library& library) const;

    void mainLibraryMenu(int& choice) const;
};
#endif