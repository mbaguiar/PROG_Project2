#pragma once

#include <iostream>
#include <string>
#include <vector>



using namespace std;

class Line{
 private:
  unsigned int id_num;
  unsigned int freq;
  vector<string> busStopList;
  vector<int> timesList;
 public:
  Line(string textLine);
  // metodos get
  unsigned int getId() const;
  unsigned int getFreq() const;
  vector<string> getBusStops() const;
  vector<int> getTimings() const;
  // set methods
  // other methods
  void showLine(Line) const;
  void showSchedule(Line) const;
  int getTimeStops(Line, string stop1, string stop2);
  void showScheduleStops(Line);
};
