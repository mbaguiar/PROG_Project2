#include "Line.h"


Line::Line(string textLIne){

  // INITIALISATION CODE GOES IN HERE
  

}

////////////////
// get methods
////////////////

unsigned int Line::getId() const{
  return id;
}

vector<string> Line::getBusStops() const{
  return busStopList;
}

vector<int> Line::getTimings() const{
  return timesList;
}
