#include "Controller.hh"

Controller::Controller(): view(), tester(), libraryManager(new LibraryManager())
{
}

Controller::~Controller() {
  delete libraryManager;
}

void Controller::launchMainMenu()
{
  while(true) {
    int choice = -1;
    view.mainMenu(choice);

    if (choice == 4) {
      cout << "You have selected to exit the program. Goodbye!" << endl;
      break;
    }

    switch (choice) {
      case 1:
        cout << "You have selected to run the program from scratch." << endl;
        launchScratch();
        break;
      case 2:
        cout << "You have selected to load the program from a file." << endl;
        break;
      case 3:
        cout << "You have selected to run the tester/demo for the application." << endl;
        launchTester();
        break;
    }
  }
}

void Controller::launchTester() 
{
  while(true) {
    int choice = -1;
    view.testerMainMenu(choice);

    if (choice == 15) {
      break;
    }

    tester.launch(choice);
  }
}

void Controller::launchScratch() {
  Library* newLibrary = new Library();
  view.createLibraryMenu(*newLibrary);
  libraryManager->addLibrary(newLibrary);
}

void Controller::launchLibraryMenu() {
  
}