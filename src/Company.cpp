#include "Company.h"

// CONSTRUCTORS

Company::Company(string nome, string driversFile, string linesFile){}

// GET METHODS

string Company::getName() const{
  return name;
}

Line Company::getLine(int index) const{
	return lines.at(index);
}

Driver Company::getDriver(int index) const{
	return drivers.at(index);
}

void Company::distribuiServico(){
}

// MUTATING METHODS

void Company::addLine(Line l) {
	lines.push_back(l);
}

void Company::addDriver(Driver d){
	drivers.push_back(d);
}
