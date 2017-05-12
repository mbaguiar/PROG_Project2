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
  // CONSTRUCTORS
  Company(string nome, LineList lines, DriverList drivers);
  Company();

  // GET METHODS

  LineList getLines() const; // returns lines map
  DriverList getDrivers() const; // returns drivers map
  vector<Bus> getBuses() const;

//  Line getLine(int index) const; // returns line of lines vector at index
//  Driver getDriver(int index) const; // returns driver of drivers vector at index

  string getName() const; // returns company name

  // SET METHODS

  void setLine(int index, Line newLine); // replaces line at index with newLine
  void setDriver(int index, Driver newDriver); // replaces driver at index with newDriver
  void setBus(Bus bus);

  // OTHER METHODS

  void addLine(Line l);
  void addDriver(Driver d);
  void addBus(Bus b);
  void eraseLine(int id);
  void eraseDriver(int id);

};


#endif
