#include "Stop.h"

// Constructors

Stop::Stop() {
	name = "";
	lineID = -1;
	posInLine = -1;
	timeFromStart = -1;
	freq= 0;
	direction = 0;
}

// Get methods

string Stop::getName() const{
	return name;
}

int Stop::getLineId() const{
	return lineID;
}

int Stop::getPosInLine() const{
	return posInLine;
}

int Stop::getTimeFromStart() const{
	return timeFromStart;
}

int Stop::getFreq() const{
	return freq;
}

int Stop::getDirection() const{
	return direction;
}

// Set methods

void Stop::setName(string name){
	this->name = name;
}

void Stop::setPosInLine(int posInLine){
	this->posInLine = posInLine;
}

void Stop::setLineId(int lineID){
	this->lineID = lineID;
}

void Stop::setTimeFromStart(int timeFromStart){
	this->timeFromStart = timeFromStart;
}

void Stop::setFreq(int freq){
	this->freq = freq;
}

void Stop::setDirection(int direction){
	this->direction = direction;
}


Stop::~Stop() {
	// Auto-generated destructor stub
}

