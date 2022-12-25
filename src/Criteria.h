/* Criteria.h */
/* */
/* Purpose: This is the header file for Criteria.cc. It contains the function prototypes/declarations for Criteria.cc and creates the class for Criteria, C_Criteria, A_Criteria and AorC_Criteria. */
/* How to use the file: Link it as necessary with other files in the Makefile. */
/* Authors: Nguyen-Hanh Nong */
/* Revision: Revision 1.0 */
/* */

#ifndef CRITERIA_H
#define CRITERIA_H

#include "Book.h"

using namespace std;

class Criteria {
		
	public:
    friend ostream& operator<<(ostream&, const Criteria&);

    /* These two functions are pure virutal functions */
    virtual bool matches(const Song &) const = 0;
    virtual void print(ostream& os) const = 0;
};

/* C_Criteria virutally inherits from Criteria */
class C_Criteria: public virtual Criteria {
		
	public:
    C_Criteria(const string &category);

    virtual bool matches(const Song &) const;
    virtual void print(ostream &os) const;

  private:
    string category;
};

/* A_Criteira virtually inherits from Criteria */
class A_Criteria: public virtual Criteria {
		
	public:
    A_Criteria(const string &artist);

    virtual bool matches(const Song &) const;
    virtual void print(ostream &os) const;

  private:
    string artist;
};

/* AorC_Criteria uses multiple inheritance to inherit from A_Criteria and C_Criteria */
class AorC_Criteria: public A_Criteria, public C_Criteria {
		
	public:
    AorC_Criteria(const string &artist, const string &category);

    virtual bool matches(const Song &) const;
    virtual void print(ostream &os) const;

};

#endif