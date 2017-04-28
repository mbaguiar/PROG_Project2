#ifndef COMPANY_H_
#define COMPANY_H_


#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "Line.h"
#include "Driver.h"


using namespace std;

class Company{
 private:
  string name;
  vector<Driver> drivers;
  vector<Line> lines;
 public:
  // CONSTRUCTORS
  Company(string nome, vector<Line> lines, vector<Driver> drivers);
  Company();

  // GET METHODS
  vector<Driver> getLines() const; // returns lines vector
  vector<Line> getDrivers() const; // returns drivers vector
  Line getLine(int index) const; // returns line of lines vector at index
  Driver getDriver(int index) const; // returns driver of drivers vector at index
  string getName() const; // returns company name

  // metodos set

  void setLine(int index, Line newLine); // replaces line at index with newLine
  void setDriver(int index, Driver newDriver); // replaces driver at index with newDriver

  // outros metodos

  void addLine(Line l);
  void addDriver(Driver d);

  void distribuiServico();  // funcao que implementa a afectacao de servico
};


#endif
