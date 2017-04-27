#include "Bus.h"


Bus::  Bus(unsigned int id, unsigned int driver, unsigned int line){

  // INITIALISATION CODE GOES IN HERE
  
}

////////////////////////////////
// get methods
///////////////////////////////
unsigned int Bus::getBusOrderInLine() const{
  return orderInLine;
}

unsigned int Bus::getDriverId() const{
  return driverId;
}

unsigned int Bus::getLineId() const{
  return lineId;
}

vector<Shift> Bus::getSchedule() const{
  return schedule;
}


//////////////////////////////
// metodos set
/////////////////////////////

////////////////////////////
// outher methods
///////////////////////////
