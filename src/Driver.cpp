#include "Driver.h"

Driver::Driver(){
	id = -1;
	name = "";
	max_shift = 0;
	max_week = 0;
	min_rest = 0;
	vector<Shift> s;
	shifts = s;
}




Driver::Driver(int id, string name, unsigned int max_shift, unsigned int max_week, unsigned int min_rest, vector<Shift> shifts) {
	this->id = id;
	this->max_shift = max_shift;
	this->max_week = max_week;
	this->min_rest = min_rest;
	this->shifts = shifts;
}

// GET METHODS

unsigned int Driver::getId() const{
  return id;
}

string Driver::getName() const{
  return name;
}

unsigned int Driver::getMaxShift() const{
  return max_shift;
}

unsigned int Driver::getMaxWeek() const{
  return max_week;
}

unsigned int Driver::getMinRest() const{
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

void Driver::setMaxShift(unsigned int max_shift) {
	this->max_shift = max_shift;
}

void Driver::setMaxWeek(unsigned int max_week){
	this->max_week = max_week;
}

void Driver::setMinRest(unsigned int min_rest) {
	this->min_rest = min_rest;
}

void Driver::setShifts(vector<Shift> shifts) {
	this->shifts = shifts;
}
