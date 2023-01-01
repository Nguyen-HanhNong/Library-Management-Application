#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <iostream>
#include <string>

#include "View.hh"
#include "Tester.hh"
#include "LibraryManager.hh"

using namespace std;

class Controller {
	public:
    Controller();
    ~Controller();

    void launchMainMenu();
    void launchTester();
    void launchScratch();

    void launchLibraryMenu();

  private: 
    View view;
    Tester tester;
    LibraryManager* libraryManager;
};
#endif