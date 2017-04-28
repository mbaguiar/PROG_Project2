#pragma once

#include <iostream>
#include <string>
#include <vector>



using namespace std;

class Line{
 private:
  unsigned int id;
  unsigned int freq;
  vector<string> stops;
  vector<int> times;
 public:
  Line(string textLine);

  // GET METHODS

  unsigned int getId() const;
  unsigned int getFreq() const;
  vector<string> getStops() const;
  vector<int> getTimes() const;

  // GET METHODS

  void setId(unsigned int id);
  void setFreq(unsigned int freq);
  void setStops(vector<string> stops);
  void setTimes(vector<int> times);

};
