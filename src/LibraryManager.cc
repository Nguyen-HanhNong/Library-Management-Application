#include "LibraryManager.hh"

LibraryManager::LibraryManager(): libraries(new vector<Library *>()) 
{ 
}

LibraryManager::~LibraryManager()
{
  while(!libraries->empty())
  {
    delete libraries->back();
    libraries->pop_back();
  }
  delete libraries;
}

bool LibraryManager::addLibrary(Library *library) {
  for(vector<Library *>::iterator it = libraries->begin(); it != libraries->end(); ++it)
  {
    if(*(*it) == *library) {
      return false;
    }
  }

  libraries->push_back(library);
  return true;
}

bool LibraryManager::removeLibrary(Library *library) {
  for(vector<Library *>::iterator it = libraries->begin(); it != libraries->end(); ++it)
  {
    if(*(*it) == *library) {
      delete *it;
      libraries->erase(it);
      return true;
    }
  }
  return false;
}

bool LibraryManager::getLibrary(const string &libraryName, Library **library) const {
  for(vector<Library *>::const_iterator it = libraries->begin(); it != libraries->end(); ++it)
  {
    if((*it)->getName() == libraryName) {
      *library = *it;
      return true;
    }
  }

  return false;
}

void LibraryManager::printLibraries() const {
  for(vector<Library *>::const_iterator it = libraries->begin(); it != libraries->end(); ++it)
  {
    cout << *(*it) << endl;
  }
}

bool LibraryManager::printLibrary(const string &libraryName) const {
  for(vector<Library *>::const_iterator it = libraries->begin(); it != libraries->end(); ++it)
  {
    if((*it)->getName() == libraryName) {
      cout << *(*it) << endl;
      return true;
    }
  }

  return false;
}

bool LibraryManager::printLibraryBooks(const string &libraryName) const {
  for(vector<Library *>::const_iterator it = libraries->begin(); it != libraries->end(); ++it)
  {
    if((*it)->getName() == libraryName) {
      cout << "Books in library " << libraryName << ":" << endl;
      (*it)->printOnlyBooks(cout);
      return true;
    }
  }

  return false;
}

bool LibraryManager::moveBook(const string &bookName, const string &fromLibrary, const string &toLibrary) {
  Library *from = NULL;
  Library *to = NULL;
  Book* book = NULL;

  Criteria *title_criteria = new Title_Criteria(bookName);

  for(vector<Library *>::iterator it = libraries->begin(); it != libraries->end(); ++it)
  {
    if((*it)->getName() == fromLibrary) {
      from = *it;
    }
    if((*it)->getName() == toLibrary) {
      to = *it;
    }
  }

  if(from == NULL || to == NULL) {
    return false;
  }

  from->removeBookByCriteria(title_criteria, &book);

  if(book == NULL) {
    delete title_criteria;
    return false;
  }

  to->addBook(book);
  delete title_criteria;

  return true;
}

int LibraryManager::getNumberOfLibraries() const {
  return libraries->size();
}

void LibraryManager::clearAllLibraries() {
  while(!libraries->empty())
  {
    delete libraries->back();
    libraries->pop_back();
  }
}