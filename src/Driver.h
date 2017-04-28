#pragma once

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
