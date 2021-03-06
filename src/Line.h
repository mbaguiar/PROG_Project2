#ifndef LINES_H_
#define LINES_H_

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

  // Constructors

  Line();
  Line (unsigned int id, unsigned int freq, vector<string> stops, vector<int> times);

  // Get methods

  unsigned int getId() const;
  unsigned int getFreq() const;
  vector<string> getStops() const;
  vector<int> getTimes() const;

  // Set methods

  void setId(unsigned int id);
  void setFreq(unsigned int freq);
  void setStops(vector<string> stops);
  void setTimes(vector<int> times);

};

#endif
