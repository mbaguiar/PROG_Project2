/*
 * Application.cpp
 *
 *  Created on: Apr 28, 2017
 *      Author: mariana
 */

#include "Application.h"
#include "Company.h"
#include "Line.h"
#include "Driver.h"
#include "Stop.h"
#include "helper.h"

typedef map<int, Driver> DriverList;
typedef map<int, Line> LineList;


Application::Application() {
	day_start = 7;
	day_end = 23;
	linesChanged = false;
	driversChanged = false;
	INSIDE_SUBMENU = false;
	LINES_IDENTIFIER = "lines";
	DRIVERS_IDENTIFIER = "drivers";
	LineList l;
	DriverList d;
	Company c = Company("Semprarrolar", l, d);
	company = c;
	linesFilepath = "";
	driversFilepath = "";
}

// Tests if the line with id id_number exists
bool Application::validIdLines(int id_number) {
	LineList lines = company.getLines();
	if (lines.find(id_number) != lines.end()) return true;
	else return false;
}

// Tests if the line with id id_number exists
bool Application::validIdDrivers(int id_number) {
	DriverList drivers = company.getDrivers();
	if (drivers.find(id_number) != drivers.end()) return true;
	else return false;
}

// Asks for the input files and saves their information in the company object
void Application::loadFiles() {
	ifstream linesfile;
	ifstream driversfile;
	string l;
	string d;

	// Lines

	do {
		cout << "Insert lines filename: ";
		getline(cin, linesFilepath);
		linesfile.open(linesFilepath);
		if (!linesfile.fail()) break;
		else cout << "Error opening file. Try again.\n";
	} while (true);

	while (!linesfile.eof()) {
		getline(linesfile, l);
		company.addLine(readLine(l));
	}
	linesfile.close();

	// Drivers

	do {
		cout << "Insert drivers filename: ";
		getline(cin, driversFilepath);
		driversfile.open(driversFilepath);
		if (!driversfile.fail()) break;
		else cout << "Error opening file. Try again.\n";
	} while (true);

	while (!driversfile.eof()) {
		getline(driversfile, d);
		company.addDriver(readDriver(d));
	}
	driversfile.close();

}

// Creates the buses vector for each line
void Application::loadBuses() {
	LineList lines = company.getLines();
	for (auto& x : lines) {
		Line l = x.second;
		int fullTripDuration = 0;
		int freq = l.getFreq();
		for (size_t i = 0; i < l.getTimes().size(); i++) {
			fullTripDuration += +l.getTimes().at(i);
		}
		fullTripDuration *= 2;

		int numberOfBuses = (int)((double)fullTripDuration / freq + 1.0); // n = number of buses needed

		for (size_t i = 1; i <= numberOfBuses; i++) {
			int depTime = day_start * 60 + freq * (i - 1); // departure time
			int endTime = day_end * 60;	// end time

			Bus b;
			b.setLineId(l.getId());
			b.setOrderInLine(i);

			// Creates shifts for every day of the week and places it on the
			// shifts vector

			for (size_t day = 1; day <= 7; day++) {

				while (depTime <= endTime) {
					Shift s = Shift(l.getId(), 0, i, depTime, depTime + fullTripDuration);
					b.addShift(s);
					depTime += freq * numberOfBuses;
				}
				// +1 Day on the clock
				depTime = day_start * 60 + 1440 * day + freq * (i - 1);
				endTime = day_end * 60 + 1440 * day;
			}
			company.addBus(b);
		}
	}
}

// Displays a line summary and asks if the user wants to see detailed info
// about a individual line
void Application::linesShow() {
	linesSummaryShow();
	string foo;
	do {
		cout << "Do you wish to view detailed information about a line (Y/N)?: ";
		getline(cin, foo);
		normalize(foo);
		if (foo == "y") {
			cout << endl;
			linesDetailShow(chooseLine());
		}
		else if (foo == "n") break;
		else {
			cout << "Invalid option. Reenter." << endl;
		}
	} while (true);
	cout << endl;
}

// Displays detailed info about the line with id id_number
void Application::linesDetailShow(int id_number) {
	Line line = company.getLines()[id_number];
	cout << setw(12) << "ID: ";
	cout << line.getId() << endl;
	cout << setw(12) << "Frequency: ";
	cout << line.getFreq() << "min\n";
	cout << setw(12) << "Stops: ";
	for (size_t i = 0; i < line.getStops().size(); i++) {
		cout << line.getStops().at(i);
		if (i != (line.getStops().size() - 1)) cout << ", ";
		else cout << endl;
	}
	cout << setw(12) << "Times: ";
	for (size_t i = 0; i < line.getTimes().size(); i++) {
		cout << line.getTimes().at(i);
		if (i != (line.getTimes().size() - 1)) cout << ", ";
		else cout << endl << endl;
	}

}

// Displays a table with the ids, frequency and first and last stop of the lines
void Application::linesSummaryShow() {
	LineList lines = company.getLines();
	cout << "LINE SUMMARY\n\n";
	cout << std::left << setw(5) << "ID" << setw(3) << " " << setw(5) << "FREQ" << setw(3) << " " << "ROUTE" << endl;
	for (auto& x : lines) {
		Line l = x.second;
		cout << setw(5) << l.getId() << setw(3) << " " << setw(5) << l.getFreq() << setw(3) << " ";
		cout << l.getStops().at(0) << " <--> " << l.getStops().at(l.getStops().size() - 1) << endl;
	}
	cout << endl;
}

// Searches a stop given a string stop in every line and places the information
// in vectors (direct and inverse) of Stop objects
void Application::searchStops(string stop, vector<Stop> &stopsDirect, vector<Stop> &stopsInverse) {
	vector<Stop> stopsD;
	vector<Stop> stopsI;
	LineList lines = company.getLines();
	for (auto& x : lines) {
		Line l = x.second;
		for (size_t x = 0; x < l.getStops().size(); x++) {
			if (l.getStops().at(x) == stop) {

				// Direct direction

				Stop newStop;
				newStop.setName(stop);
				newStop.setPosInLine(x);
				newStop.setLineId(l.getId());
				newStop.setFreq(l.getFreq());
				newStop.setTimeFromStart(0);
				newStop.setDirection(0);
				for (int z = 0; z < x; z++) {
					newStop.setTimeFromStart(newStop.getTimeFromStart() + l.getTimes().at(z));
				}
				newStop.setStopH(day_start);
				newStop.setStopM(newStop.getTimeFromStart());
				stopsD.push_back(newStop);

				// Inverse direction

				Stop newStop2;
				newStop2.setName(stop);
				newStop2.setPosInLine(x);
				newStop2.setLineId(l.getId());
				newStop2.setFreq(l.getFreq());
				newStop2.setTimeFromStart(0);
				newStop2.setDirection(1);
				for (int z = l.getTimes().size() - 1; z >= x; z--) {
					if (z < 0) break;
					newStop2.setTimeFromStart(newStop2.getTimeFromStart() + l.getTimes().at(z));
				}
				newStop2.setStopH(day_start);
				newStop2.setStopM(newStop.getTimeFromStart());
				stopsI.push_back(newStop2);
				break;
			}
		}
	}
	stopsDirect = stopsD;
	stopsInverse = stopsI;
}

// Returns the id of the chosen lines
int Application::chooseLine() {
	int lineID;
	LineList lines = company.getLines();
	if (!lines.empty()) {
		cout << "Available line IDs: ";
		for (auto& x : lines) {
			Line l = x.second;
			cout << l.getId() << " ";
		}
		cout << endl;
	}
	do {
		cout << "Choose line: ";
		if (!validArg(lineID)) continue;
		if (validIdLines(lineID)) break;
		else {
			cout << "Invalid id. Reenter.\n";
		}
	} while (true);
	return lineID;
}

void Application::printTimes(vector<Clock> time, Line line, int &n, int d) {
	vector<string> stops = line.getStops();
	int freq = line.getFreq();
	int t;
	bool end = false;
	cout << std::left;
	while (!end) {
		for (int i = 0; i < time.size(); i++) {
			string v;
			if (time.at(i).hours < 10) {
				v = "0" + to_string(time.at(i).hours) + ":";
			}
			else
				v = to_string(time.at(i).hours) + ":";

			if (time.at(i).mins < 10) {
				v = v + "0" + to_string(time.at(i).mins);
			}
			else
				v = v + to_string(time.at(i).mins);
			if (d == 1) {
				t = i;
			}
			else t = stops.size() - 1 - i;
			if (stops.at(t).size() < 5) {
				cout << setw(5) << v;
			}
			else cout << setw(stops.at(t).size()) << v;
			if (i != stops.size() - 1) {
				cout << setw(3) << " ";
			}
			else cout << endl;
		}
		for (int i = 0; i < time.size(); i++) {
			time.at(i) = addTime(freq, time.at(i));
		}
		if (d == 1) {
			n++;
			if (time.at(0).hours >= day_end) end = true;
		}
		if (d == -1) {
			n--;
			if (n == 0) end = true;
		}
	}
}

// Prints line schedule
void Application::linesSchedule() {
	int sum;
	Clock start_time;
	start_time.hours = day_start;
	start_time.mins = 0;
	int n = 0;
	string s;
	vector<Clock> time;
	vector <Clock> time2;


	Line line = company.getLines()[chooseLine()];

	cout << "Direction: " << line.getStops().at(0);
	cout << " -> " << line.getStops().at(line.getStops().size() - 1) << endl << endl;
	cout << std::left;
	for (int i = 0; i < line.getStops().size(); i++) {
		if (line.getStops().at(i).size() < 5) {
			cout << setw(5) << line.getStops().at(i);
		}
		else cout << setw(line.getStops().at(i).size()) << line.getStops().at(i);
		if (i != line.getStops().size() - 1) {
			cout << setw(3) << " ";
		}
		else cout << endl << endl;
	}

	time.push_back(start_time);
	sum = 0;
	for (int i = 0; i < line.getTimes().size(); i++) {
		sum = sum + line.getTimes().at(i);
		time.push_back(addTime(sum, start_time));
	}
	printTimes(time, line, n, 1);
	cout << endl << endl;

	cout << "Direction: " << line.getStops().at(line.getStops().size() - 1);
	cout << " to " << line.getStops().at(0) << endl << endl;
	cout << std::left;
	for (int i = line.getStops().size() - 1; i >= 0; i--) {
		if (line.getStops().at(i).size() < 5) {
			cout << setw(5) << line.getStops().at(i);
		}
		else cout << setw(line.getStops().at(i).size()) << line.getStops().at(i);
		if (i != 0) {
			cout << setw(3) << " ";
		}
		else cout << endl << endl;
	}
	start_time = addTime(sum, start_time);
	time2.push_back(start_time);
	sum = 0;
	for (int i = line.getTimes().size() - 1; i >= 0; i--) {
		sum = sum + line.getTimes().at(i);
		time2.push_back(addTime(sum, start_time));
	}
	printTimes(time2, line, n, -1);
	cout << endl;
	pause();

}

// Recieves 2 stops
void Application::route(Stop stop1, Stop stop2, int pos1, int pos2, int &duration, vector<string> &route) {
	duration = 0;
	int id1 = stop1.getLineId();
	Line line1 = company.getLines()[id1];
	int id2 = stop2.getLineId();
	Line line2 = company.getLines()[id2];
	if (stop1.getPosInLine() < pos1) {
		for (int i = stop1.getPosInLine(); i <= pos1; i++) {
			if (i == pos1) route.push_back(line1.getStops().at(i) + "*");
			else route.push_back(line1.getStops().at(i));
		}
		for (int i = stop1.getPosInLine(); i < pos1; i++) {
			duration = duration + line1.getTimes().at(i);
		}
	}
	else {
		for (int i = stop1.getPosInLine(); i >= pos1; i--) {
			if (i == pos1) route.push_back(line1.getStops().at(i) + "*");
			else route.push_back(line1.getStops().at(i));
		}
		for (int i = pos1; i < stop1.getPosInLine(); i++) {
			duration = duration + line1.getTimes().at(i);
		}
	}
	if (stop2.getPosInLine() < pos2) {
		for (int i = pos2 - 1; i > stop2.getPosInLine(); i--) {
			route.push_back(line2.getStops().at(i));
		}
		for (int i = stop2.getPosInLine(); i < pos2; i++) {
			duration = duration + line2.getTimes().at(i);
		}
	}
	else {
		for (int i = pos2 + 1; i <= stop2.getPosInLine(); i++) {
			route.push_back(line2.getStops().at(i));
		}
		for (int i = pos2; i < stop2.getPosInLine(); i++) {
			duration = duration + line2.getTimes().at(i);
		}
	}
}

void Application::linesTravelTimes() {
	string stop1, stop2;
	vector<Stop> stopsDirect1, stopsDirect2, stopsInverse1, stopsInverse2;
	do {
		cout << "Insert the first stop name: ";
		getline(cin, stop1);
		searchStops(stop1, stopsDirect1, stopsInverse1);

		if (stopsDirect1.empty() && stopsInverse1.empty()) {
			cout << "Invalid stop name.\n";
		}
		else break;
	} while (true);

	do {
		cout << "Insert the second stop name: ";
		getline(cin, stop2);
		searchStops(stop2, stopsDirect2, stopsInverse2);
		if (stopsDirect2.empty() && stopsInverse2.empty()) {
			cout << "Invalid stop name.\n";
		}
		else break;
	} while (true);

	vector<int> IDs;
	vector<int> directions;
	vector<int> times;
	vector<vector <string> > routes;

	vector<int> startIDs;
	vector<int> endIDs;
	vector<int> times2;
	vector<vector <string> > routes2;

	for (int i = 0; i < stopsDirect1.size(); i++) {
		for (int x = 0; x < stopsDirect2.size(); x++) {
			if (stopsDirect1.at(i).getLineId() == stopsDirect2.at(x).getLineId()) {
				if (stopsDirect1.at(i).getPosInLine() < stopsDirect2.at(x).getPosInLine()) {
					IDs.push_back(stopsDirect1.at(i).getLineId());
					directions.push_back(0);
					int time = 0;
					for (int z = stopsDirect1.at(i).getPosInLine(); z < stopsDirect2.at(x).getPosInLine(); z++) {
						time += company.getLines()[stopsDirect1.at(i).getLineId()].getTimes().at(z);
					}
					times.push_back(time);
					vector<string> stops;
					for (int z = stopsDirect1.at(i).getPosInLine(); z <= stopsDirect2.at(x).getPosInLine(); z++) {
						stops.push_back(company.getLines()[stopsDirect1.at(i).getLineId()].getStops().at(z));
					}
					routes.push_back(stops);
					break;
				}
			}
		}
	}

	for (int i = 0; i < stopsInverse1.size(); i++) {
		for (int x = 0; x < stopsInverse2.size(); x++) {
			if (stopsInverse1.at(i).getLineId() == stopsInverse2.at(x).getLineId()) {
				if (stopsInverse1.at(i).getPosInLine() > stopsInverse2.at(x).getPosInLine()) {
					IDs.push_back(stopsInverse1.at(i).getLineId());
					directions.push_back(1);
					int time = 0;
					for (int z = stopsInverse1.at(i).getPosInLine() - 1; z >= stopsInverse2.at(x).getPosInLine(); z--) {
						time += company.getLines()[stopsDirect1.at(i).getLineId()].getTimes().at(z);
					}
					times.push_back(time);
					vector<string> stops;
					for (int z = stopsInverse1.at(i).getPosInLine(); z >= stopsInverse2.at(x).getPosInLine(); z--) {
						stops.push_back(company.getLines()[stopsInverse1.at(i).getLineId()].getStops().at(z));
					}
					routes.push_back(stops);
					break;
				}
			}
		}
	}
	if (!IDs.empty()) {
		cout << "There are " << IDs.size() << " direct routes from " << stop1 << " to " << stop2 << ":\n";
		for (int i = 0; i < IDs.size(); i++) {
			cout << endl;
			cout << "Line " << IDs.at(i);
			cout << " - ";
			if (directions.at(i) == 0) cout << "MAIN DIRECTION";
			else cout << "INVERSE DIRECTION";
			cout << " - ETA: ";
			if (times.at(i) >= 60) {
				int t = times.at(i);
				int h = 0;
				while (t >= 60) {
					t -= 60;
					h++;
				}
				cout << h << "h " << t << "min";
			}
			else cout << times.at(i) << "min";
			cout << " - (";
			for (size_t x = 0; x < routes.at(i).size(); x++) {
				cout << routes.at(i).at(x);
				if (x != routes.at(i).size() - 1) {
					cout << ", ";
				}
				else {
					cout << ")\n";
				}
			}
		}
	}
	else {
		cout << "There are no direct routes from " << stop1 << " to " << stop2 << ".\n";
		for (int i = 0; i < stopsDirect1.size(); i++) {
			int id1 = stopsDirect1.at(i).getLineId();
			for (int x = 0; x < stopsDirect2.size(); x++) {
				int id2 = stopsDirect2.at(x).getLineId();
				int pos1 = -1;
				int pos2 = -1;
				for (int t = 0; t < company.getLines()[id1].getStops().size(); t++) {
					for (int z = 0; z < company.getLines()[id2].getStops().size(); z++) {
						if (company.getLines()[id1].getStops().at(t) == company.getLines()[id2].getStops().at(z)) {
							pos1 = t;
							pos2 = z;
						}
					}
				}
				if (pos1 != -1 && pos2 != -1) {
					startIDs.push_back(id1);
					endIDs.push_back(id2);
					int temp;
					vector<string> temp2;
					route(stopsDirect1.at(i), stopsDirect2.at(x), pos1, pos2, temp, temp2);
					times2.push_back(temp);
					routes2.push_back(temp2);
				}
			}
		}
		if (!startIDs.empty()) {
			cout << "There are " << startIDs.size() << " non-direct routes from " << stop1 << " to " << stop2 << ":\n";
			cout << "* Marks the stop where you must switch lines.\n";
			for (size_t i = 0; i < startIDs.size(); i++) {
				cout << endl;
				cout << "Line " << startIDs.at(i) << " and " << endIDs.at(i);
				cout << " - ";
				cout << "ETA: ";
				if (times2.at(i) >= 60) {
					int t = times2.at(i);
					int h = 0;
					while (t >= 60) {
						t -= 60;
						h++;
					}
					cout << h << "h " << t << "min";
				}
				else cout << times2.at(i) << "min";
				cout << " - (";
				for (size_t x = 0; x < routes2.at(i).size(); x++) {
					cout << routes2.at(i).at(x);
					if (x != routes2.at(i).size() - 1) {
						cout << ", ";
					}
					else {
						cout << ")\n";
					}
				}
			}
		}
	}

	pause();
}


void Application::linesStopLines() {
	string stop;
	vector<Stop> stopsDirect;
	vector<Stop> stopsInverse;
	do {
		cout << "Insert the stop name to search for (CTRL-Z to cancel): ";
		getline(cin, stop);
		if (cin.eof()) {
			cin.clear();
			return;
		}
		searchStops(stop, stopsDirect, stopsInverse);

		if (stopsDirect.empty() && stopsInverse.empty()) {
			cout << "Invalid stop name.\n";
		}
		else break;
	} while (true);
	cout << "The stop '" << stop << "' belongs to the following lines: ";
	for (size_t i = 0; i < stopsDirect.size(); i++) {
		cout << stopsDirect.at(i).getLineId();
		if (i != stopsDirect.size() - 1) {
			cout << ", ";
		}
		else {
			cout << ".\n";
		}
	}
}

void Application::printTable(Stop stop, int duration, Clock start, string begin, string end, int &n) {
	Clock time = start;
	int direction = stop.getDirection();
	string stopName = stop.getName();
	int travel = stop.getTimeFromStart();
	int freq = stop.getFreq();
	vector<Clock> empty;
	vector<Clock> temp;
	vector < vector < Clock > > hours;
	time = addTime(travel, time);
	temp.push_back(time);
	if (!direction) {
		while (true) {
			int foo = time.hours;
			time = addTime(freq, time);
			Clock foo2 = subTime(travel, time);
			if (foo2.hours >= day_end) {
				hours.push_back(temp);
				break;
			}
			else if (time.hours > foo) {
				hours.push_back(temp);
				temp.resize(0);
				temp.push_back(time);
				n++;
			}
			else {
				temp.push_back(time);
				n++;
			}
		}
	}
	else {
		while (true) {
			int foo = time.hours;
			time = addTime(freq, time);
			if (n == 0) {
				hours.push_back(temp);
				break;
			}
			else if (time.hours > foo) {
				hours.push_back(temp);
				temp.resize(0);
				temp.push_back(time);
				n--;
			}
			else if (foo == 23 && time.hours == 0) {
				hours.push_back(temp);
				temp.resize(0);
				temp.push_back(time);
				n--;
			}
			else {
				temp.push_back(time);
				n--;
			}
		}
	}
	int id = stop.getLineId();
	cout << "Line: " << id << " - " << stop.getName() << endl;
	cout << "Direction: " << begin;
	cout << " to " << end << endl << endl;
	for (int i = 0; i < hours.size(); i++) {
		cout << setw(6) << hours.at(i).at(0).hours;
	}
	cout << endl;
	for (int i = 0; i < hours.size(); i++) {
		cout << setw(6) << "--";
	}
	int size = 0;
	for (int i = 0; i < hours.size(); i++) {
		size = size + hours.at(i).size();
	}
	cout << endl;
	int t = 0;
	while (size > 0) {
		for (int i = 0; i < hours.size(); i++) {
			string s;
			if (t >= hours.at(i).size()) {
				cout << setw(6) << " ";
			}
			else if (hours.at(i).at(t).mins < 10) {
				s = "0" + to_string(hours.at(i).at(t).mins);
				cout << setw(6) << s;
				size--;
			}
			else {
				s = to_string(hours.at(i).at(t).mins);
				cout << setw(6) << s;
				size--;
			}
		}
		cout << endl;
		t++;
	}
	cout << endl;
}

void Application::linesStopTimetable(){
	string stop;
	int n=0;
	int travel;
	vector<Stop> stopsDirect, stopsInverse;
	do {
		cout << "Insert the stop name: ";
		getline(cin, stop);
		searchStops(stop, stopsDirect,  stopsInverse);

		if (stopsDirect.empty() && stopsInverse.empty()) {
			cout << "Invalid stop name.\n\n";
		}
		else break;
	} while (true);
	Clock start;
	for(int i = 0; i<stopsDirect.size(); i++){
		int duration= 0;
		n=0;
		start.hours = day_start;
		start.mins = 0;
		travel  = stopsDirect.at(i).getTimeFromStart();
		Line line = company.getLines()[stopsDirect.at(i).getLineId()];
		for(int t=0; t<line.getTimes().size(); t++){
			duration = duration + line.getTimes().at(t);
		}
		printTable(stopsDirect.at(i),duration, start, line.getStops().at(0), line.getStops().at(line.getStops().size()-1), n );
		start = addTime(duration, start);
		travel = stopsInverse.at(i).getTimeFromStart();
		line = company.getLines()[stopsInverse.at(i).getLineId()];
		printTable(stopsInverse.at(i), duration, start, line.getStops().at(line.getStops().size()-1), line.getStops().at(0), n);
	}
}

void Application::driversShow() {
	printDrivers();
	cout << endl << endl;
	pause();

}

void Application::printDrivers() {
	DriverList drivers = company.getDrivers();
	cout << std::left << setw(4) << "ID" << setw(3) << " " << setw(30) << "NAME" << setw(3) << " " << setw(7);
	cout << "H/SHIFT" << setw(3) << " " << setw(6) << "H/WEEK" << setw(3) << " " << setw(6) << "H/REST" << endl;
	for (auto& x : drivers) {
		Driver d = x.second;
		cout << std::left << setw(4) << d.getId() << setw(3) << " ";
		cout << setw(30) << d.getName() << setw(3) << " ";
		cout << std::right << setw(7) << d.getMaxShift() << setw(3) << " ";
		cout << setw(6) << d.getMaxWeek() << setw(3) << " ";
		cout << setw(6) << d.getMinRest() << endl;
	}
}
void Application::driversDetailShow(int id_number) {
	Driver driver = company.getDrivers()[id_number];
	cout << std::left;
	cout << setw(15) << "ID: ";
	cout << driver.getId() << endl;
	cout << setw(15) << "Name: ";
	cout << driver.getName() << endl;
	cout << setw(15) << "Daily shift: ";
	cout << driver.getMaxWeek() << "h\n";
	cout << setw(15) << "Weekly shift: ";
	cout << driver.getMaxShift() << "h\n";
	cout << setw(15) << "Resting hours: ";
	cout << driver.getMinRest() << "h\n\n";
}

void Application::driversCreate() {
	Driver newdriver;
	string foo;
	int id_number, max_shift, max_week, min_rest;
	string name;
	DriverList drivers = company.getDrivers();

	cout << "Insert the new driver information: \n\n";
	do {
		cout << "Insert ID: ";
		if (!validArg(id_number)) continue;
		if (validIdDrivers(id_number)) {
			cout << "This driver already exists. Please insert another id or delete the driver." << endl;
		}
		else {
			break;
		}
	} while (true);

	cout << "Name: ";
	getline(cin, name);
	do {
		cout << "Daily shift(h): ";
		if (validArg(max_shift)) break;
	} while (true);

	do {
		cout << "Weekly shift(h): ";
		getline(cin, foo);
		if (validArg(max_week)) break;
	} while (true);

	do {
		cout << "Rest(h): ";
		if (validArg(min_rest)) break;
	} while (true);

	newdriver.setId(id_number);
	newdriver.setName(name);
	newdriver.setMaxShift(max_shift);
	newdriver.setMaxWeek(max_week);
	newdriver.setMinRest(min_rest);
	company.addDriver(newdriver);
	driversChanged = true;
}

void Application::driversUpdate() {
	int id;
	string foo;
	printDrivers();
	do {
		cout << "Insert the driver to change: ";
		if (!validArg(id)) continue;
		if (validIdDrivers(id)) break;
		else {
			cout << "Invalid id. Reenter.\n";
		}
	} while (true);

	cout << endl;

	driversDetailShow(id);
	do {
		displayUpdateMenu(id, DRIVERS_IDENTIFIER);
		updateMenu(id, DRIVERS_IDENTIFIER);
	} while (INSIDE_SUBMENU);
}

void Application::driversUpdateName(int id_number) {
	Driver d = company.getDrivers()[id_number];
	string foo;
	cout << "The current name for driver " << id_number << " is " << d.getName() << endl;
	cout << "Insert the new name: ";
	getline(cin, foo);
	d.setName(foo);
	company.setDriver(id_number, d);
	driversChanged = true;
	cout << "Driver updated successfully. ";
	pause();
}

void Application::driversUpdateMaxShift(int id_number) {
	Driver d = company.getDrivers()[id_number];
	string foo;
	int shift;
	cout << "The current daily shift for driver " << id_number << " is " << d.getMaxShift() << "h.";
	do {
		bool success = true;
		cout << "Insert the new daily shift(h): ";
		getline(cin, foo);
		try {
			shift = stoi(foo, nullptr);
		}
		catch (const std::invalid_argument& ia) {
			cout << "Invalid input. Reenter." << endl;
			success = false;
		}
		if (success) break;
	} while (true);
	d.setMaxShift(shift);
	company.setDriver(id_number, d);
	driversChanged = true;
	cout << "Driver updated successfully. ";
	pause();
}

void Application::driversUpdateMaxWeek(int id_number) {
	Driver d = company.getDrivers()[id_number];
	string foo;
	int shift;
	cout << "The current weekly shift for driver " << id_number << " is " << d.getMaxWeek() << "h.";
	do {
		bool success = true;
		cout << "Insert the new weekly shift(h): ";
		getline(cin, foo);
		try {
			shift = stoi(foo, nullptr);
		}
		catch (const std::invalid_argument& ia) {
			cout << "Invalid input. Reenter." << endl;
			success = false;
		}
		if (success) break;
	} while (true);
	d.setMaxWeek(shift);
	company.setDriver(id_number, d);
	driversChanged = true;
	cout << "Driver updated successfully. ";
	pause();
}

void Application::driversUpdateMinRest(int id_number) {
	Driver d = company.getDrivers()[id_number];
	string foo;
	int rest;
	cout << "The current daily shift for driver " << id_number << " is " << d.getMinRest() << "h.";
	do {
		bool success = true;
		cout << "Insert the new minimum rest(h): ";
		getline(cin, foo);
		try {
			rest = stoi(foo, nullptr);
		}
		catch (const std::invalid_argument& ia) {
			cout << "Invalid input. Reenter." << endl;
			success = false;
		}
		if (success) break;
	} while (true);
	d.setMinRest(rest);
	company.setDriver(id_number, d);
	driversChanged = true;
	cout << "Driver updated successfully. ";
	pause();
}

void Application::driversDelete() {
	printDrivers();
	int id;
	do {
		cout << "Driver's id:";
		if (!validArg(id)) continue;
		if (validIdDrivers(id)) break;
		else {
			cout << "Invalid id. Reenter." << endl;
		}
	} while (true);
	validIdDrivers(id);
	company.eraseDriver(id);
	cout << "Driver " << id << " deleted successfully. ";
	driversChanged = true;
	pause();
}

void Application::driversShowAssignedWork() {
	printDrivers();
	int id;
	do {
		cout << endl << "Insert the driver number: ";
		if (!validArg(id)) continue;
		if (validIdDrivers(id)) break;
		else cout << "Invalid id. Reenter.\n";
	} while (true);

	Driver d = company.getDrivers()[id];
	cout << d.getShifts().size();

	if (d.getShifts().empty()) cout << "The driver has no assigned work.\n";
	else {
		for (auto &s : d.getShifts()) {
			int day1, hours1, mins1, day2, hours2, mins2;
			cout << "| Line " << s.getBusLineId() << " - Bus " << s.getBusOrderNumber() << ": ";
			treatTime(day1, hours1, mins1, s.getStartTime());
			treatTime(day2, hours2, mins2, s.getEndTime());
			printDay(day1);
			cout << ",";
			cout << setw(12) << timeToString(hours1, hours2, mins1, mins2) << setw(3) << " " << endl;
		}
	}
	pause();

}

void Application::driversShowFreeTime() {
	printDrivers();
	int id;
	do {
		cout << endl << "Insert the driver number: ";
		if (!validArg(id)) continue;
		if (validIdDrivers(id)) break;
		else cout << "Invalid id. Reenter.\n";
	} while (true);

	Driver d = company.getDrivers()[id];
	int temp = 0;


	for (auto &s : d.getShifts()) {
		temp += (s.getEndTime() - s.getStartTime());
	}

	if (temp >= d.getMaxWeek() * 60) cout << "The driver has a full schedule for the week.\n";
	else {
		temp = 0;
		int timeStart; // day_start monday
		timeToMins(0, day_start, 0, timeStart);
		int timeEnd; //day_end monday
		timeToMins(0, day_end, 0, timeEnd);

		for (unsigned int i = 1; i <= 7; i++) {
			vector<Shift> dailyShifts;
			for (auto &s : d.getShifts()) {
				if (s.getStartTime() >= timeStart && s.getEndTime() <= timeEnd) dailyShifts.push_back(s);
			}

			if (dailyShifts.empty()) {
				cout << "| "; printDay(i); cout << ": ";
				int d1, h1, m1, d2, h2, m2;
				treatTime(d1, h1, m1, timeStart);
				treatTime(d1, h2, m2, timeEnd);
				cout << timeToString(h1, h2, m1, m2) << endl;
			}
			else {

				int day1, hours1, mins1, day2, hours2, mins2, freeTimeStart, freeTimeEnd;

				for (size_t x = 0; x < dailyShifts.size(); x++) {
					Shift s = dailyShifts.at(x);
					freeTimeStart = s.getStartTime() - (d.getMinRest() * 60);
					if (freeTimeStart > timeStart) {
						cout << "| "; printDay(i); cout << ": ";
						treatTime(day1, hours1, mins1, timeStart);
						treatTime(day2, hours2, mins2, freeTimeStart);
						cout << timeToString(hours1, hours2, mins1, mins2) << endl;
					}
					freeTimeEnd = s.getEndTime() + (d.getMinRest() * 60);
					if (dailyShifts.size() > (x + 1)) {
						Shift nextS = dailyShifts.at(x + 1);
						timeEnd = nextS.getStartTime() - (d.getMinRest() * 60);
					}
					else {
					timeToMins(i - 1, day_end, 0, timeEnd);
					}
					if (freeTimeEnd < timeEnd) {
						cout << "| "; printDay(i); cout << ": ";
						treatTime(day1, hours1, mins1, freeTimeEnd);
						treatTime(day2, hours2, mins2, timeEnd);
						cout << timeToString(hours1, hours2, mins1, mins2) << endl;
						timeStart = timeEnd;
					}
					else {
						timeStart = freeTimeEnd;
					}
				}

			}

			timeToMins(i, day_start, 0, timeStart);
			timeToMins(i, day_end, 0, timeEnd);

		}
	}
}

void Application::driversAssignWork() {
	Shift newdrivershift;
	printDrivers();
	int driverID;
	do {
		cout << endl << "Insert the driver number: ";
		if (!validArg(driverID)) continue;
		if (validIdDrivers(driverID)) break;
		else cout << "Invalid id. Reenter.\n";
	} while (true);

	Driver d = company.getDrivers()[driverID];
	int lineID, busN;
	lineID = chooseLine();
	busN = chooseBus(lineID);

	cout << "Line " << lineID << " Bus " << busN << endl;
	cout << "Shifts:\n";
	vector<Bus> buses = company.getBuses();
	int busIndex;
	for (size_t i = 0; i < buses.size(); i++) {
		if (buses.at(i).getLineId() == lineID && buses.at(i).getBusOrderInLine() == busN) {
			busIndex = i;
			vector<Shift> shifts = buses.at(i).getSchedule();

			for (size_t t = 0; t < shifts.size(); t++) {
				if (shifts.at(t).getDriverId() == 0) {
					int day1, day2, h1, h2, min1, min2;
					treatTime(day1, h1, min1, shifts.at(t).getStartTime());
					treatTime(day2, h2, min2, shifts.at(t).getEndTime());
					cout << "Shift " << setw(3) << t + 1 << setw(3) << " ";
					cout << "Day: "; printDay(day1);
					cout << setw(3) << " " << "Time: " << timeToString(h1, h2, min1, min2) << setw(3) << " ";
					cout << endl;
				}
			}
		}
	}
	vector<int> shiftsNumbers;
	do {
		cout << "Would you like to assign more than one shift (Y/N)? ";
		string foo;
		getline(cin, foo);
		normalize(foo);
		if (foo == "y") {
			do {
				bool success = true;
				shiftsNumbers.clear();
				cout << "Insert consecutive shifts (Press enter to stop): ";
				bool finished = false;
				do {
					int t;
					if (validArg(t, finished)) shiftsNumbers.push_back(t - 1);
				} while (!finished);


				for (size_t i = 0; i < shiftsNumbers.size() - 1; i++) {
					if (!(shiftsNumbers.at(i) == shiftsNumbers.at(i + 1) - 1 ||
						shiftsNumbers.at(i) == shiftsNumbers.at(i + 1) + 1)) {
						success = false;
					}
				}

				for (size_t i = 0; i < shiftsNumbers.size(); i++) {
					if (shiftsNumbers.at(i) + 1 > buses.at(busIndex).getSchedule().size()) {
						success = false;
					}

				}

				sort(shiftsNumbers.begin(), shiftsNumbers.end());

				if (success) break;
				else cout << "Invalid shifts. Please try again.\n";

			} while (true);


			Shift firstShift = buses.at(busIndex).getSchedule().at(shiftsNumbers.at(0));
			Shift lastShift = buses.at(busIndex).getSchedule().at(shiftsNumbers.at(shiftsNumbers.size() - 1));
			newdrivershift.setBusLineId(lineID);
			newdrivershift.setDriverId(driverID);
			newdrivershift.setBusOrderNumber(busN);
			newdrivershift.setStartTime(firstShift.getStartTime());
			newdrivershift.setEndTime(lastShift.getEndTime());
			break;

		}
		else if (foo == "n") {
			int shiftID;
			do {
				cout << "Insert number of shift: ";
				if (!validArg(shiftID)) continue;
				if (shiftID > buses.at(busIndex).getSchedule().size()) cout << "Invalid shift number.\n";
				else break;
			} while (true);

			shiftsNumbers.push_back(shiftID - 1);
			newdrivershift.setBusLineId(lineID);
			newdrivershift.setDriverId(driverID);
			newdrivershift.setBusOrderNumber(busN);
			newdrivershift.setStartTime(buses.at(busIndex).getSchedule().at(shiftID - 1).getStartTime());
			newdrivershift.setEndTime(buses.at(busIndex).getSchedule().at(shiftID - 1).getEndTime());
			break;
		}
		else {
			cout << "Invalid input.\n";
		}
	} while (true);
	int rest = d.getMinRest() * 60;
	int max_shift = d.getMaxShift() * 60;
	int max_week = d.getMaxWeek() * 60;
	int duration = 0;
	bool success = true;
	for (size_t i = 0; i < d.getShifts().size(); i++) {
		int temp = 0;
		temp = d.getShifts().at(i).getEndTime() - d.getShifts().at(i).getStartTime();
		duration = duration + temp;
	}

	int durationShift = newdrivershift.getEndTime() - newdrivershift.getStartTime();
	if (durationShift <= max_shift && (duration + durationShift) <= max_week) {
		if (!d.getShifts().empty()) {
			for (size_t t = 0; t < d.getShifts().size(); t++) {
				if (newdrivershift.getStartTime() >= (d.getShifts().at(t).getStartTime() - rest) && newdrivershift.getStartTime() <= (d.getShifts().at(t).getEndTime() + rest)) {
					success = false;

				}
				else if (newdrivershift.getEndTime() >= (d.getShifts().at(t).getStartTime() - rest) && newdrivershift.getEndTime() <= (d.getShifts().at(t).getEndTime() + rest)) {
					success = false;
				}
			}
		}
	}
	else {
		cout << "Max hours per shift or max hours per week reached!\n";
	}

	if (success) {
		vector<Shift> newshifts = d.getShifts();
		newshifts.push_back(newdrivershift);
		sort(newshifts.begin(), newshifts.end(), sortShifts);
		d.setShifts(newshifts);
		company.setDriver(d.getId(), d);
		for (size_t i = 0; i < shiftsNumbers.size(); i++) {
			buses.at(busIndex).setDriverShift(shiftsNumbers.at(i), driverID);
		}
		company.setBus(buses.at(busIndex));
		cout << "Shift(s) successfully added. ";
		pause();
	}
	else {
		cout << "You cannot overlap shifts!\n";
		return;
	}
}

int Application::chooseBus(int lineID) {
	int busN;
	int n = 0;
	for (int i = 0; i < company.getBuses().size(); i++) {
		if (company.getBuses().at(i).getLineId() == lineID) {
			n++;
		}
	}
	if (n == 1) {
		cout << "Theres is only 1 available bus for line " << lineID << ":\n";
		return 1;
	}
	else {
		cout << "The buses available for line " << lineID << " are buses 1-" << n << ".\n";
		do {
			cout << "Choose bus: ";
			if (!validArg(busN)) continue;
			if (busN >= 1 && busN <= n) {
				break;
			}
			else {
				cout << "Invalid bus number. Reenter.\n";
			}
		} while (true);

		return busN;
	}
}

void Application::busesShow() {
	int lineID = chooseLine();
	int busN = chooseBus(lineID);

	cout << "Line " << lineID << " Bus number " << busN << endl;
	cout << "Shifts:\n";

	vector<Bus> buses = company.getBuses();
	for (int i = 0; i < buses.size(); i++) {
		if (buses.at(i).getLineId() == lineID && buses.at(i).getBusOrderInLine() == busN) {
			vector<Shift> shifts = buses.at(i).getSchedule();
			for (int t = 0; t < shifts.size(); t++) {
				int day1, day2, h1, h2, min1, min2;
				treatTime(day1, h1, min1, shifts.at(t).getStartTime());
				treatTime(day2, h2, min2, shifts.at(t).getEndTime());
				cout << "Shift " << setw(3) << t + 1 << setw(3) << " ";
				cout << "Day: "; printDay(day1);
				cout << setw(3) << " " << "Time: " << timeToString(h1, h2, min1, min2) << setw(3) << " ";
				cout << "Driver: ";
				if (shifts.at(t).getDriverId() == 0) cout << "Unassigned" << endl;
				else cout << shifts.at(t).getDriverId() << endl;
			}
		}
	}

	pause();
}

void Application::printBus(Bus bus, int day) {
	for (size_t t = 0; t < bus.getSchedule().size(); t++) {
		Shift shift = bus.getSchedule().at(t);
		int day1, day2, hours1, mins1, hours2, mins2;
		int time1 = shift.getStartTime();
		int time2 = shift.getEndTime();
		treatTime(day1, hours1, mins1, time1);
		treatTime(day2, hours2, mins2, time2);
		if (day1 == day && shift.getDriverId() == 0) {
			cout << setw(12) << timeToString(hours1, hours2, mins1, mins2) << setw(3) << " ";
		}
	}
}

void Application::busesShowFreeTime() {
	int id = chooseLine();
	vector<Bus> buses = company.getBuses();
	cout << "Line " << id << endl << endl;
	for (size_t i = 0; i < buses.size(); i++) {
		if (buses.at(i).getLineId() == id) {
			cout << "Bus " << buses.at(i).getBusOrderInLine() << endl;
			cout << setw(12) << "Monday" << setw(3) << " ";
			printBus(buses.at(i), 1);
			cout << endl << endl;
			cout << setw(12) << "Tuesday" << setw(3) << " ";
			printBus(buses.at(i), 2);
			cout << endl << endl;
			cout << setw(12) << "Wednesday" << setw(3) << " ";
			printBus(buses.at(i), 3);
			cout << endl << endl;
			cout << setw(12) << "Thursday" << setw(3) << " ";
			printBus(buses.at(i), 4);
			cout << endl << endl;
			cout << setw(12) << "Friday" << setw(3) << " ";
			printBus(buses.at(i), 5);
			cout << endl << endl;
			cout << setw(12) << "Saturday" << setw(3) << " ";
			printBus(buses.at(i), 6);
			cout << endl << endl;
			cout << setw(12) << "Sunday" << setw(3) << " ";
			printBus(buses.at(i), 7);
			cout << endl;
			cout << endl;
		}
	}
}

void Application::exitMenu() {
	saveChanges();
	exit(0);
}

void Application::setupMenu() {
	mainMenu["lines show"] = &Application::linesShow;
	mainMenu["lines schedules"] = &Application::linesSchedule;
	mainMenu["lines routes"] = &Application::linesTravelTimes;
	mainMenu["lines stop lines"] = &Application::linesStopLines;
	mainMenu["lines stop timetable"] = &Application::linesStopTimetable;
	mainMenu["drivers show"] = &Application::driversShow;
	mainMenu["drivers create"] = &Application::driversCreate;
	mainMenu["drivers update"] = &Application::driversUpdate;
	mainMenu["drivers delete"] = &Application::driversDelete;
	mainMenu["drivers show assigned work"] = &Application::driversShowAssignedWork;
	mainMenu["drivers show free time"] = &Application::driversShowFreeTime;
	mainMenu["drivers assign work"] = &Application::driversAssignWork;
	mainMenu["buses show"] = &Application::busesShow;
	mainMenu["buses show free time"] = &Application::busesShowFreeTime;
	mainMenu["exit"] = &Application::exitMenu;
	//shortcuts
	mainMenu["ls"] = &Application::linesShow;
	mainMenu["lsch"] = &Application::linesSchedule;
	mainMenu["lr"] = &Application::linesTravelTimes;
	mainMenu["lsl"] = &Application::linesStopLines;
	mainMenu["lst"] = &Application::linesStopTimetable;
	mainMenu["ds"] = &Application::driversShow;
	mainMenu["dc"] = &Application::driversCreate;
	mainMenu["du"] = &Application::driversUpdate;
	mainMenu["dd"] = &Application::driversDelete;
	mainMenu["dsaw"] = &Application::driversShowAssignedWork;
	mainMenu["dsft"] = &Application::driversShowFreeTime;
	mainMenu["daw"] = &Application::driversAssignWork;
	mainMenu["bs"] = &Application::busesShow;
	mainMenu["bsft"] = &Application::busesShowFreeTime;
	mainMenu["e"] = &Application::exitMenu;
	//driver update menu
	driverUpdateMenu["name"] = &Application::driversUpdateName;
	driverUpdateMenu["h/day"] = &Application::driversUpdateMaxShift;
	driverUpdateMenu["h/week"] = &Application::driversUpdateMaxWeek;
	driverUpdateMenu["h/rest"] = &Application::driversUpdateMinRest;
}

void Application::displayMainMenu() {
	cout << "\n";
	cout << "Lines" << endl;
	cout << "     Show, Schedules, Routes" << endl;
	cout << "     Stop Lines, Stop Timetable" << endl;
	cout << "Drivers" << endl;
	cout << "     Show, Create, Update, Delete" << endl;
	cout << "     Show Assigned Work, Show Free Time, Assign Work" << endl;
	cout << "Buses" << endl;
	cout << "     Show, Show Free Time" << endl;
	cout << "Exit" << endl;
}

void Application::displayUpdateMenu(int id_number, string identifier) {
	if (identifier == DRIVERS_IDENTIFIER) {
		cout << "Drivers Update - Driver " << id_number << " selected" << endl;
		cout << "     Name, H/Day, H/Week, H/Rest" << endl;
	}
	cout << "     Back" << endl;
}

void Application::inputMenu() {
	string command;
	do {
		cout << "Command: ";
		getline(cin, command);
		if (command == "") {
			cout << "Invalid command.\n";
			continue;
		}
		normalize(command);
		if (mainMenu.find(command) != mainMenu.end()) {
			(this->*mainMenu[command])();
			break;
		}
		else cout << "Invalid command.\n";
	} while (true);
}

void Application::start() {
	do {
		displayMainMenu();
		inputMenu();
	} while (true);
}

void Application::updateMenu(int id_number, string identifier) {
	map<string, UpdateMenuOption> updateMenu;
	if (identifier == DRIVERS_IDENTIFIER)  updateMenu = driverUpdateMenu;
	string command;
	do {
		INSIDE_SUBMENU = true;
		cout << "Command: ";
		getline(cin, command);
		normalize(command);
		if (command == "back") {
			INSIDE_SUBMENU = false;
			break;
		}
		else if (updateMenu.find(command) != updateMenu.end()) {
			(this->*updateMenu[command])(id_number);
			break;
		}
		else cout << "Invalid command.\n";
	} while (true);
}

vector<string> Application::driversToStrings() {
	vector<string> v;
	string next;
	DriverList drivers = company.getDrivers();
	for (auto &item : drivers) {
		Driver d = item.second;
		next.clear();
		next = to_string(d.getId()) + " ; " + d.getName() + " ; " + to_string(d.getMaxShift()) + " ; " + to_string(d.getMaxWeek()) + " ; " +
			to_string(d.getMinRest());
		v.push_back(next);
	}
	return v;
}

void Application::changeFile(string type) {
	ofstream output_file;
	string path;
	vector<string> newStrings;

	if (type == LINES_IDENTIFIER) {
		path = linesFilepath;
	}
	else {
		path = driversFilepath;
		newStrings = driversToStrings();

	}
	output_file.open(path);

	if (output_file.fail()) {
		cerr << "The output file could not be opened.\n";
	}
	else {
		for (int i = 0; i < newStrings.size(); i++) {
			output_file << newStrings.at(i);
			if (i != newStrings.size() - 1) output_file << endl;
		}
		cout << "Changes to " << type << " file ('" << path << "') successfully deployed.\n";
		if (type == LINES_IDENTIFIER) linesChanged = false;
		else driversChanged = false;

		output_file.close();
	}
}


void Application::saveChanges() {
	string command;
	if (driversChanged) {
		cout << "There are changes to be deployed to the files.\n";
		do {
			cout << "Would you like to save those changes (Y/N) ? ";
			getline(cin, command);
			normalize(command);
			if (command == "y") {
				if (linesChanged) changeFile("lines");
				if (driversChanged) changeFile("drivers");
				break;
			}
			else if (command == "n") break;
			else {
				cout << "Invalid option.\n";
			}
		} while (true);
	}
}
Application::~Application() {
	// TODO Auto-generated destructor stub
}

