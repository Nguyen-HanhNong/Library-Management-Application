/* Criteria.h */
/* */
/* Purpose: This is the header file for Criteria.cc. It contains the function prototypes/declarations for Criteria.cc and creates the class for Criteria, C_Criteria, A_Criteria and AorC_Criteria. */
/* How to use the file: Link it as necessary with other files in the Makefile. */
/* Authors: Nguyen-Hanh Nong */
/* Revision: Revision 1.0 */
/* */

#ifndef CRITERIA_HPP
#define CRITERIA_HPP

#include "Book.hh"

using namespace std;

class Criteria {	
	public:
    friend ostream& operator<<(ostream&, const Criteria&);

    /* These two functions are pure virutal functions */
    virtual bool matches(const Book &) const = 0;
    virtual void print(ostream& os) const = 0;
};

class Title_Criteria: public virtual Criteria {
		
	public:
    Title_Criteria(const string &title);

    virtual bool matches(const Book &) const;
    virtual void print(ostream &os) const;

  private:
    string title;
};


class Author_Criteria: public virtual Criteria {
		
	public:
    Author_Criteria(const string &author);

    virtual bool matches(const Book &) const;
    virtual void print(ostream &os) const;

  private:
    string author;
};

class Genre_Criteria: public virtual Criteria {
		
	public:
    Genre_Criteria(const string &genre);

    virtual bool matches(const Book &) const;
    virtual void print(ostream &os) const;

  private:
    string genre;
};

class Subgenre_Criteria: public virtual Criteria {
		
	public:
    Subgenre_Criteria(const string &subgenre);

    virtual bool matches(const Book &) const;
    virtual void print(ostream &os) const;

  private:
    string subgenre;
};

class Publisher_Criteria: public virtual Criteria {
		
	public:
    Publisher_Criteria(const string &publisher);

    virtual bool matches(const Book &) const;
    virtual void print(ostream &os) const;

  private:
    string publisher;
};

class Page_Criteria: public virtual Criteria {
		
	public:
    Page_Criteria(const int pageCount);

    virtual bool matches(const Book &) const;
    virtual bool lessThan(const Book &) const;
    virtual bool moreThan(const Book &) const;
    virtual void print(ostream &os) const;

  private:
    int pageCount;
};


#endif