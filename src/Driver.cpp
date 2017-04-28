#include "Driver.h"

Driver::Driver(string textLine){

  // INITIALISATION CODE GOES IN HERE
  
}

// GET METHODS

unsigned int Driver::getId() const{
  return id;
}

string Driver::getName() const{
  return name;
}

unsigned int Driver::getShiftMaxDuration() const{
  return max_shift;
}

unsigned int Driver::getMaxWeekWorkingTime() const{
  return max_week;
}

unsigned int Driver::getMinRestTime() const{
  return min_rest;
}

vector<Shift> Driver::getShifts() const{
  return shifts;
}

// SET METHODS

void Driver::setId(unsigned int id){
	this->id = id;
}

void Driver::setName (string name) {
	this->name = name;
}

void Driver::setMax_shift(unsigned int max_shift) {
	this->max_shift = max_shift;
}

void Driver::setMax_week(unsigned int max_week){
	this->max_week = max_week;
}

void Driver::setMin_rest(unsigned int min_rest) {
	this->min_rest = min_rest;
}

void Driver::setShifts(vector<Shift> shifts) {
	this->shifts = shifts;
}
