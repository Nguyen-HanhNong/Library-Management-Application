#include "Address.hh"

Address::Address(const string& streetNumber, const string& streetName, const string& cityName, const string& provinceName, const string& postalCode): streetNumber(streetNumber), streetName(streetName), cityName(cityName), provinceName(provinceName), postalCode(postalCode) 
{ 
}

Address::~Address()
{
}

Address::Address(const Address &copyAddress): streetNumber(copyAddress.streetNumber), streetName(copyAddress.streetName), cityName(copyAddress.cityName), provinceName(copyAddress.provinceName), postalCode(copyAddress.postalCode)
{
}

const string& Address::getStreetNumber() const {
  return this->streetNumber;
}

const string& Address::getStreetName() const {
  return this->streetName;
}

const string& Address::getCityName() const {
  return this->cityName;
}

const string& Address::getProvinceName() const {
  return this->provinceName;
}

const string& Address::getPostalCode() const {
  return this->postalCode;
}

void Address::printAddress(ostream &os) const {
  if(!checkUnknownAdress()) {
    os << this->streetNumber << " " << this->streetName << endl;
    os << this->cityName << ", " << this->provinceName << " " << this->postalCode << endl;
  }
  else {
    os << "Unknown Address" << endl;
  }
}

bool Address::matches(const Address &address) const {
  if (this->streetNumber.compare(address.streetNumber) == 0 && this->streetName.compare(address.streetName) == 0 && this->cityName.compare(address.cityName) == 0 && this->provinceName.compare(address.provinceName) == 0 && this->postalCode.compare(address.postalCode) == 0) {
    return true;
  }
  else {
    return false;
  }
}

bool Address::checkUnknownAdress() const {
  if (this->streetNumber.compare("Unknown") == 0 && this->streetName.compare("Unknown") == 0 && this->cityName.compare("Unknown") == 0 && this->provinceName.compare("Unknown") == 0 && this->postalCode.compare("Unknown") == 0) {
    return true;
  }
  else {
    return false;
  }
}

ostream& operator<<(ostream &os, const Address &address) {
  address.printAddress(os);
  return os;
}

bool Address::operator==(const Address &address) const {
  return this->matches(address);
}

bool Address::operator!=(const Address &address) const {
  return !this->matches(address);
}

bool Address::operator<(const Address &address) const {
  if (this->streetName.compare(address.streetName) < 0) {
    return true;
  }
  else if(this->streetName.compare(address.streetName) == 0) {
    if (this->streetNumber.compare(address.streetNumber) < 0) {
      return true;
    }
    else {
      if(this->cityName.compare(address.cityName) < 0) {
        return true;
      }
      else if(this->cityName.compare(address.cityName) == 0) {
        if(this->provinceName.compare(address.provinceName) < 0) {
          return true;
        }
        else if(this->provinceName.compare(address.provinceName) == 0) {
          if(this->postalCode.compare(address.postalCode) < 0) {
            return true;
          }
          else {
            return false;
          }
        }
        else {
          return false;
        }
      }
      else {
        return false;
      }
    }
  }
  else {
    return false;
  }
}

bool Address::operator>(const Address &address) const {
  if (this->streetName.compare(address.streetName) > 0) {
    return true;
  }
  else if(this->streetName.compare(address.streetName) == 0) {
    if (this->streetNumber.compare(address.streetNumber) > 0) {
      return true;
    }
    else {
      if(this->cityName.compare(address.cityName) > 0) {
        return true;
      }
      else if(this->cityName.compare(address.cityName) == 0) {
        if(this->provinceName.compare(address.provinceName) > 0) {
          return true;
        }
        else if(this->provinceName.compare(address.provinceName) == 0) {
          if(this->postalCode.compare(address.postalCode) > 0) {
            return true;
          }
          else {
            return false;
          }
        }
        else {
          return false;
        }
      }
      else {
        return false;
      }
    }
  }
  else {
    return false;
  }
}