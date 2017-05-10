#include "Company.h"
#include <map>
#include <string>

using namespace std;

// CONSTRUCTORS

Company::Company(){
	name = "";
	DriverList d;
	LineList l;
	drivers = d;
	lines = l;
}

Company::Company(string name, LineList lines , DriverList drivers){
	this->name = name;
	this->lines = lines;
	this->drivers = drivers;
}


// GET METHODS

string Company::getName() const{
  return name;
}

LineList Company::getLines() const {
	return lines;
}

DriverList Company::getDrivers() const {
	return drivers;
}

//Line Company::getLine(int index) const{
//	return lines.at(index);
//}
//
//Driver Company::getDriver(int index) const{
//	return drivers.at(index);
//}

void Company::distribuiServico(){
}

// MUTATING METHODS

void Company::addLine(Line l) {
	lines[l.getId()] = l;
}

void Company::addDriver(Driver d){
	drivers[d.getId()] = d;
}

void Company::eraseLine(int id){
	lines.erase(id);
}

void Company::eraseDriver(int id){
	drivers.erase(id);
}

void Company::setLine(int index, Line newLine) {
	lines[index] = newLine;
}

void Company::setDriver(int index, Driver newDriver) {
	drivers[index] = newDriver;
}
