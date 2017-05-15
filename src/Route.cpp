/*
 * Route.cpp
 *
 *  Created on: May 15, 2017
 *      Author: tiagofragoso
 */

#include "Route.h"

Route::Route() {
	startLineID = 0;
	endLineID = 0;
	duration = 0;
	vector <string> s;
	stops = s;
}

Route::Route(int startID, int endID, int dur, vector<string> stops){
	startLineID = startID;
	endLineID = endID;
	duration = dur;
	this->stops = stops;
}

int Route::getStartLineID() const {
	return startLineID;
}

int Route::getEndLineID() const {
	return endLineID;
}

int Route::getDuration() const {
	return duration;
}

vector<string> Route::getStops() const {
	return stops;
}
Route::~Route() {
	// TODO Auto-generated destructor stub
}

