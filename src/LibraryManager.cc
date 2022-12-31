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
      cout << (*it) << endl;
      return true;
    }
  }

  return false;
}
