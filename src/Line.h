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
  // metodos get
  unsigned int getId() const;
  unsigned int getFreq() const;
  vector<string> getBusStops() const;
  vector<int> getTimings() const;
  // set methods
  void setId(unsigned int id);
  void setFreq(unsigned int freq);
  void setStops(vector<string> stops);
  void setTimes(vector<int> times);
  // other methods
  void showLine(Line) const;
  void showSchedule(Line) const;
  int getTimeStops(Line, string stop1, string stop2) const;
  void showScheduleStops(Line) const;
};
