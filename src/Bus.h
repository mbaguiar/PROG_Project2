#pragma once

#include <iostream>
#include <vector>

#include "Shift.h"


using namespace std;

class Bus{
 private:
  unsigned int orderInLine;
  unsigned int driverId;
  unsigned int lineId;
  vector<Shift> schedule;
 public:
  Bus(unsigned int id, unsigned int driver, unsigned int line);
  // get methods
  unsigned int getBusOrderInLine() const;
  unsigned int getDriverId() const;
  unsigned int getLineId() const;
  vector<Shift> getSchedule() const;
  // set methods
    unsigned int setDriverId() const;
    unsigned int setLineId() const;
  // other methods

};
