#include "View.hh"

View::View() 
{
}

View::~View() 
{
}

void View::mainMenu(int& choice) const {
  cout << "Hello, welcome to the Library Management Application main menu!" << endl;

  for (;;) {
    cout << "Please select an option from the following:" << endl;

    cout << "1. Run the program from scratch." << endl;
    cout << "2. Load the program from a file." << endl;
    cout << "3. Run the tester/demo for the application." << endl;
    cout << "4. Exit the program" << endl;

    cin >> choice;

    if (cin.fail()) {
      cerr << "Sorry, the input is invalid. Try again." << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      continue;
    }

    if (choice < 1 || choice > 4) {
      std::cerr << "Sorry, the option selected is out of range. Try again." << std::endl;
      continue;
    }

    break;
  }
}

void View::testerMainMenu(int &choice) const {
  cout << "You have entered the tester functionality of the application. Choose which test you want to run: " << endl;

  for (;;) {
    cout << "Please select an option from the following:" << endl;

    cout << "1. Print a list of all books." << endl;
    cout << "2. Compare two books." << endl;
    cout << "3. Test all criteria for the books." << endl;
    cout << "4. Test all getter functions of a Library." << endl;
    cout << "5. Test all add functions of a Library." << endl;
    cout << "6. Test all remove functions of a Library." << endl;
    cout << "7. Test all book retrieval functions of a Library." << endl;
    cout << "8. Test all sorting functions of a Library." << endl;
    cout << "9. Run all tests rigorously." << endl;
    cout << "10. Exit the testing part of the program." << endl;

    cin >> choice;

    if (cin.fail()) {
      cerr << "Sorry, the input is invalid. Try again." << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      continue;
    }

    if (choice < 1 || choice > 10) {
      std::cerr << "Sorry, the option selected is out of range. Try again." << std::endl;
      continue;
    }

    break;
  }
}

void View::starterLibraryMenu(int &choice) const {
  cout << "You have selected to run the program from scratch." << endl;

  for (;;) {
    cout << "Please select an option from the following:" << endl;
    
    cout << "1. Add a book to the library." << endl;
    cout << "2. Remove a book from the library." << endl;
    cout << "3. Search for a book in the library." << endl;
    cout << "4. Sort the library by title." << endl;
    cout << "5. Sort the library by author." << endl;
    cout << "6. Sort the library by year." << endl;
    cout << "7. Sort the library by rating." << endl;
    cout << "8. Print the library." << endl;
    cout << "9. Save the library to a file." << endl;
    cout << "10. Exit the program." << endl;

    cin >> choice;

    if (cin.fail()) {
      cerr << "Sorry, the input is invalid. Try again." << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      continue;
    }

    if(choice < 1 || choice > 10) {
      std::cerr << "Sorry, the option selected is out of range. Try again." << std::endl;
      continue;
    }

    break;
  }
}

void View::createLibraryMenu(Library& library) const {
  
}