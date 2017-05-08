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
  Line();
  Line(string textLine);
  Line (unsigned int id, unsigned int freq, vector<string> stops, vector<int> times);

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

#endif

//int lineH, lineM, stopH, stopM, lineFreq;
//	int lineID = chooseLine();
//	int linePos = searchLine(lineID);
//	Line line = lines.at(linePos);
//	system("cls");
//	cout << "[LINE " << lineID << " SCHEDULE]\n\n";
//	lineFreq = line.freq;
//
//	// MAIN DIRECTION
//	lineH = STARTING_HOUR;
//	lineM = STARTING_MIN;
//	cout << "MAIN DIRECTION: ";
//	cout << line.stops.at(0) << " --> ";
//	cout << line.stops.at(line.stops.size() - 1) << endl << endl;
//	for (int i = 0; i < line.stops.size(); i++) {
//		cout << setw(line.stops.at(i).size()) << line.stops.at(i);
//		if (i != line.stops.size() - 1) {
//			cout << setw(3) << " ";
//		}
//		else {
//			cout << endl;
//		}
//	}
//	cout << std::left;
//	while (true) {
//		treatTime(lineH, lineM);
//		if (lineH > ENDING_HOUR || (lineH == ENDING_HOUR && lineM >= ENDING_MIN)) {
//			break;
//		}
//		cout << setw(line.stops.at(0).size()) << displayTime(lineH, lineM) << setw(3) << " ";
//		stopH = lineH;
//		stopM = lineM;
//		for (int x = 0; x < line.times.size(); x++) {
//			stopM += line.times.at(x);
//			cout << setw(line.stops.at(x + 1).size()) << displayTime(stopH, stopM);
//			if (x != line.times.size() - 1) {
//				cout << setw(3) << " ";
//			}
//			else {
//				cout << endl;
//			}
//		}
//		lineM += lineFreq;
//	}
