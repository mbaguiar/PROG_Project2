#ifndef BUS_H_
#define BUS_H_

#include <iostream>
#include <vector>

#include "Shift.h"


using namespace std;

class Bus{
 private:
  unsigned int orderInLine;
  unsigned int lineId;
  vector<Shift> schedule;
 public:
  Bus(unsigned int orderInLine, unsigned int lineId);
  Bus();
  // get methods
  unsigned int getBusOrderInLine() const;
  unsigned int getLineId() const;
  vector<Shift> getSchedule() const;
  // set methods
   void setOrderInLine(unsigned int orderInLine);
   void setLineId(unsigned int lineId);
   void setSchedule(vector<Shift> schedule);
   void addShift(Shift shift);
  // other methods

};

#endif
