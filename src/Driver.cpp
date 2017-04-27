#include "Driver.h"

Driver::Driver(string textLine){

  // INITIALISATION CODE GOES IN HERE
  
}

//////////////
// get methods
//////////////

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
