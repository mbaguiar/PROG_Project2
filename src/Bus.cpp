#include "Bus.h"


Bus::Bus(unsigned int orderInLine, unsigned int driverId, unsigned int lineId){
	this->orderInLine = orderInLine;
	this->driverId = driverId;
	this->lineId = lineId;
	vector<Shift> s;
	schedule = s;
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

void Bus::setOrderInLine(unsigned int orderInLine){
	this->orderInLine = orderInLine;
}

void Bus::setLineId(unsigned int lineId){
	this->lineId = lineId;
}

void Bus::setDriverId(unsigned int driverId){
	this->driverId = driverId;
}

void Bus::setSchedule(vector<Shift> schedule){
	this->schedule = schedule;
}

void Bus::addShift(Shift shift){
	schedule.push_back(shift);
}
