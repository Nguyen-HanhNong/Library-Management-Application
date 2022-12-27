/* Address.hh */
/* */
/* Purpose: This is the header file for Address.cc. It contains the function prototypes/declarations for Address.cc and creates the class for Address. */
/* How to use the file: Link it as necessary with other files in the Makefile. */
/* Authors: Nguyen-Hanh Nong */
/* */

#ifndef ADDRESS_HPP
#define ADDRESS_HPP

/* Necessary libraries and imports */
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

class Address {
		
	public:
		//overloaded operators
		friend ostream& operator<<(ostream&, const Address&);
		bool operator==(const Address&) const;
		bool operator!=(const Address&) const;
		bool operator<(const Address&) const;
		bool operator>(const Address&) const;

		//constructors
		Address(const string& streetNumber = "Unknown", const string& streetName = "Unknown", const string& cityName = "Unknown", const string& provinceName = "Unknown", const string& postalCode = "Unknown");
    ~Address();
    Address(const Address &copyAddress);

    //getters
    const string& getStreetNumber() const;
    const string& getStreetName() const;
		const string& getCityName() const;
		const string& getProvinceName() const;
		const string& getPostalCode() const;

		//print formatting
		void printAddress(ostream &os) const;

		//boolean functions
		bool matches(const Address &address) const;
    bool checkUnknownAdress() const;

	private:
    string streetNumber;
    string streetName;
    string cityName;
    string provinceName;
    string postalCode;
};
#endif