#ifndef COMPANY_H_
#define COMPANY_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "Line.h"
#include "Driver.h"
#include "Stop.h"
#include "Bus.h"

  typedef map<int, Driver> DriverList;
  typedef map<int, Line> LineList;

using namespace std;

class Company{

 private:
  string name;
  DriverList drivers;
  LineList lines;
  vector<Bus> buses;

 public:

  // Constructors

  Company(string nome, LineList lines, DriverList drivers);
  Company();

  // Get methods

  LineList getLines() const;
  DriverList getDrivers() const;
  vector<Bus> getBuses() const;
  string getName() const;

  // Set methods

  void setLine(int index, Line newLine);
  void setDriver(int index, Driver newDriver);
  void setBus(Bus bus);

  // Mutating methods

  void addLine(Line l);
  void addDriver(Driver d);
  void addBus(Bus b);
  void eraseLine(int id);
  void eraseDriver(int id);

};

#endif
