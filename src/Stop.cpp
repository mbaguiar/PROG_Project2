/*
 * Stop.cpp
 *
 *  Created on: May 8, 2017
 *      Author: mariana
 */

#include "Stop.h"

Stop::Stop() {
	name = "";
	lineID = -1;
	posInLine = -1;
	timeFromStart = -1;
	stopH = -1;
	stopM = -1;
	freq= 0;
	direction = 0;
}

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

int Stop::getStopH() const{
	return stopH;
}

int Stop::getStopM() const{
	return stopM;
}

int Stop::getFreq() const{
	return freq;
}

int Stop::getDirection() const{
	return direction;
}

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

void Stop::setStopH(int stopH){
	this->stopH = stopH;
}

void Stop::setStopM(int stopM){
	this->stopM = stopM;
}

void Stop::setFreq(int freq){
	this->freq = freq;
}

void Stop::setDirection(int direction){
	this->direction = direction;
}


Stop::~Stop() {
	// TODO Auto-generated destructor stub
}

