#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <iostream>
#include <string>

#include "View.hh"
#include "Tester.hh"

using namespace std;

class Controller {
	public:
    Controller();
    ~Controller();

    void launchMainMenu();
    void launchTester();

  private: 
    View view;
    Tester tester;
};
#endif