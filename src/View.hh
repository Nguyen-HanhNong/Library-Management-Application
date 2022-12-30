#ifndef VIEW_HPP
#define VIEW_HPP

#include <iostream>
#include <string>
#include <limits>

using namespace std;

class View {
	public:
    View();
    ~View();

    void mainMenu(int& choice) const;
    
    void testerMainMenu(int& choice) const;
};
#endif