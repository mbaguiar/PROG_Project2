#ifndef DRIVER_H_
#define DRIVER_H_

#include <iostream>
#include <string>
#include <vector>

#include "Shift.h"


using namespace std;

class Driver{
 private:
  unsigned int id;
  string name;
  unsigned int max_shift;        // maximum duration of a shift
  unsigned int max_week;  // maximum number of hours of work in a week
  unsigned int min_rest;     // minimum number of rest hours between shifts
  vector<Shift> shifts;         // assigned shifts
 public:
  Driver();
  Driver(string textLine);
  Driver(int id, string name, unsigned int max_shift, unsigned int max_week, unsigned int min_rest, vector<Shift> shifts);

  // GET METHODS

  unsigned int getId() const;
  string getName() const;
  unsigned int getShiftMaxDuration() const;
  unsigned int getMaxWeekWorkingTime() const;
  unsigned int getMinRestTime() const;
  vector<Shift> getShifts() const;

  // SET METHODS

  void setId(unsigned int id);
  void setName (string name);
  void setMax_shift(unsigned int max_shift);
  void setMax_week(unsigned int max_week);
  void setMin_rest(unsigned int min_rest);
  void setShifts(vector<Shift> shifts);

};

#endif


//for (int x = 0; x < foundLines2.stopsInverse.size(); x++) {
//	if (foundLines1.stopsInverse.at(i).lineID == foundLines2.stopsInverse.at(x).lineID) {
//		if (foundLines1.stopsInverse.at(i).posInLine > foundLines2.stopsInverse.at(x).posInLine) {
//			newRoute2.lineID = foundLines1.stopsInverse.at(i).lineID;
//			newRoute2.linePos = foundLines1.stopsInverse.at(i).linePos;
//			newRoute2.startingPos = foundLines1.stopsInverse.at(i).posInLine;
//			newRoute2.endingPos = foundLines2.stopsInverse.at(x).posInLine;
//			newRoute2.time = 0;
//			newRoute2.direction = 1;
//			for (int z = newRoute2.startingPos - 1; z >= newRoute2.endingPos; z--) {
//				newRoute2.time += lines.at(newRoute2.linePos).times.at(z);
//			}
//			vector<string> stops;
//			for (int z = newRoute2.startingPos; z >= newRoute2.endingPos; z--) {
//				stops.push_back(lines.at(newRoute2.linePos).stops.at(z));
//			}
//			newRoute2.stops = stops;
//			routes.push_back(newRoute2);
//			break;
//		}
//	}
//}
//}
