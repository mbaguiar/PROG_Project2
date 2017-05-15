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
  unsigned int max_shift;
  unsigned int max_week;
  unsigned int min_rest;
  vector<Shift> shifts;

 public:

  // Constructors

  Driver();
  Driver(int id, string name, unsigned int max_shift, unsigned int max_week, unsigned int min_rest, vector<Shift> shifts);

  // Get methods

  unsigned int getId() const;
  string getName() const;
  unsigned int getMaxShift() const;
  unsigned int getMaxWeek() const;
  unsigned int getMinRest() const;
  vector<Shift> getShifts() const;

  // Set methods

  void setId(unsigned int id);
  void setName (string name);
  void setMaxShift(unsigned int max_shift);
  void setMaxWeek(unsigned int max_week);
  void setMinRest(unsigned int min_rest);
  void setShifts(vector<Shift> shifts);

};

#endif

