#include "Route.h"

// Constructors

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

// Get methods

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

// Set methods

void Route::setStartLineID(int startID) {
	startLineID = startID;
}
void Route::setEndLineID(int endID) {
	endLineID = endID;
}

void Route::setDuration(int dur) {
	duration = dur;
}

void Route::setStops(vector<string> stops) {
	this->stops = stops;
}

Route::~Route() {
	// Auto-generated destructor stub
}

