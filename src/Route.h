/*
 * Route.h
 *
 *  Created on: May 15, 2017
 *      Author: tiagofragoso
 */

#ifndef SRC_ROUTE_H_
#define SRC_ROUTE_H_

#include <string>
#include <vector>

using namespace std;

class Route {
private:
	int startLineID;
	int endLineID;
	int duration;
	vector<string> stops;
public:
	Route();
	Route(int startID, int endID, int dur, vector<string> stops);
	~Route();
	int getStartLineID() const;
	int getEndLineID() const;
	int getDuration() const;
	vector<string> getStops() const;
	void setStartLineID(int startID);
	void setEndLineID(int endID);
	void setDuration(int dur);
	void setStops(vector<string> stops);
};

#endif /* SRC_ROUTE_H_ */
