#include "Shift.h"

// Constructors

Shift::Shift(){
	busLineId = 0;
	driverId = 0;
	busOrderNumber = 0;
	startTime = 0;
	endTime = 0;
}

Shift::Shift(unsigned int busLineId, unsigned int driverId, unsigned int busOrderNumber, unsigned int startTime, unsigned int endTime){
	this->busLineId = busLineId;
	this->driverId = driverId;
	this->busOrderNumber = busOrderNumber;
	this->startTime = startTime;
	this->endTime = endTime;
}

// Get methods

unsigned int Shift::getBusLineId() const{
  return busLineId;
}

unsigned int Shift::getDriverId() const{
  return driverId;
}
unsigned int Shift::getBusOrderNumber() const{
  return busOrderNumber;
}

unsigned int Shift::getStartTime() const{
  return startTime;
}

unsigned int Shift::getEndTime() const{
  return endTime;
}

// Set methods

void Shift::setBusLineId(unsigned int busLineId){
  this->busLineId = busLineId;
}

void Shift::setDriverId(unsigned int driverId){
  this->driverId = driverId;
}

void Shift::setBusOrderNumber(unsigned int busOrderNumber){
  this->busOrderNumber = busOrderNumber;
}

void Shift::setStartTime(unsigned int startTime){
  this->startTime = startTime;
}

void Shift::setEndTime(unsigned int endTime){
  this->endTime = endTime;
}
