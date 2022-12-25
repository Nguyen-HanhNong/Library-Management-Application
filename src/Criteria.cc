/* Criteria.cc */
/* */
/* Purpose: This is a .CC file that contains the implentations of the Criteria.h header file, and contains the functions and variables necessary for a Criteria and all its respective subclasses.  */
/* How to use the file: Link it as necessary with other files in the Makefile. */
/* Authors: Nguyen-Hanh Nong */
/* Revision: Revision 1.0 */
/* */

#include "Criteria.h"

/* This function overloads the << operator for Criteria and it's subclasses */
ostream& operator<<(ostream& os, const Criteria& criteria){ 
  /* Call the print function of the Criteria and pass in the ostream object */
  criteria.print(os);
  return os;
}

/* Constructor for the A_Criteria object which initializes all the member variables */
A_Criteria::A_Criteria(const string &artist): artist(artist) 
{
}

/* Constructor for the C_Criteria object which initializes all the member variables */
C_Criteria::C_Criteria(const string &category): category(category) 
{
}

/* Constructor for the AorC_Criteria object which initializes all the member variables */
AorC_Criteria::AorC_Criteria(const string &artist, const string &category): A_Criteria(artist), C_Criteria(category)
{
}

/* Function that checks whether a song's artist matches a artist, returns true if it does, return false if it doesn't */
bool A_Criteria::matches(const Song &song) const {
  return song.getArtist().compare(this->artist) == 0;
}

/* Function that checks whether a song's category matches a category, returns true if it does, return false if it doesn't */
bool C_Criteria::matches(const Song &song) const {
  return song.getCategory().compare(this->category) == 0;
}

/* Function that checks whether a song's category matches a category or a song's artist matches an artist, returns true if it does, return false if it doesn't */
bool AorC_Criteria::matches(const Song &song) const {
  return A_Criteria::matches(song) || C_Criteria::matches(song);
}

/* This function overrides the print function in the Criteria class and tells the user how the A_Criteria will match a Song */
void A_Criteria::print(ostream &os) const {
  os << "To match the A_Criteria, the user must have the same artist as: " << this->artist << endl;
}

/* This function overrides the print function in the Criteria class and tells the user how the C_Criteria will match a Song */
void C_Criteria::print(ostream &os) const {
  os << "To match the C_Criteria, the user must have the same category as: " << this->category << endl;
}

/* This function overrides the print function in the Criteria class and tells the user how the AorC_Criteria will match a Song */
void AorC_Criteria::print(ostream &os) const {
  os << "To match the AorC_Criteria, the user must match the A_Crtieria or the C_Criteria, which is the following: " << endl;

  A_Criteria::print(os);
  C_Criteria::print(os);
}