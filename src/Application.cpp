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
	Company c = Company("semprarrolar",l, d) ;
	company = c;
	linesFilepath = "";
	driversFilepath= "";
}


bool Application::validIdLines(int id_number){
	LineList lines = company.getLines();
	if (lines.find(id_number) != lines.end()) return true;
	else return false;
}

bool Application::validIdDrivers(int id_number){
	DriverList drivers = company.getDrivers();
	if (drivers.find(id_number) != drivers.end()) return true;
	else return false;
}

void Application::loadFiles(){
	ifstream linesfile;
	ifstream driversfile;
	string l;
	string d;

	do {
		cout << "Insert lines filename: ";
		getline(cin,linesFilepath);
		linesfile.open(linesFilepath);
		if (!linesfile.fail()) break;
		else cout << "Error opening file. Try again.\n";
	} while (true);

	while(!linesfile.eof()) {
		getline(linesfile,l);
		company.addLine(readLine(l));
	}
	linesfile.close();

	do {
		cout << "Insert drivers filename: ";
		getline(cin,driversFilepath);
		driversfile.open(driversFilepath);
		if (!driversfile.fail()) break;
		else cout << "Error opening file. Try again.\n";
	} while (true);

	while(!driversfile.eof()) {
		getline(driversfile,d);
		company.addDriver(readDriver(d));
	}
	driversfile.close();

}

void Application::linesShow(){
	linesSummaryShow();
	int id;
	string foo;
	do {
		cout << "Do you wish to view detailed information about a line (Y/N)?: ";
		getline(cin, foo);
		normalize(foo);
		if (foo == "y") {
			linesDetailShow(chooseLine());
		} else if (foo == "n") break;
		else {
			cout << "Invalid option. Reenter." << endl;
		}
	} while (true);
	cout << endl;
}

void Application::linesDetailShow(int id_number) {
	Line line = company.getLines()[id_number];
	cout << setw(12) << "ID: ";
	cout << line.getId() << endl;
	cout << setw(12) << "Frequency: ";
	cout << line.getFreq() << "min\n";
	cout << setw(12) << "Stops: ";
	for (int i = 0; i < line.getStops().size(); i++) {
		cout << line.getStops().at(i);
		if (i != (line.getStops().size() - 1)) cout << ", ";
		else cout << endl;
	}
	cout << setw(12) << "Times: ";
	for (int i = 0; i < line.getTimes().size(); i++) {
		cout << line.getTimes().at(i);
		if (i != (line.getTimes().size() - 1)) cout << ", ";
		else cout << endl << endl;
	}

}

void Application::linesSummaryShow(){
	LineList lines = company.getLines();
	cout << "LINE SUMMARY\n\n";
	cout << std::left << setw(5) << "ID" << setw(3) << " " << setw(5) << "FREQ" << setw(3) << " " << "ROUTE" << endl;
	for (auto& x: lines) {
		Line l = x.second;
		cout << setw(5) << l.getId() << setw(3) << " " << setw(5) << l.getFreq() << setw(3) << " ";
		cout << l.getStops().at(0) << " <--> " << l.getStops().at(l.getStops().size() - 1) << endl;
	}
	cout << endl;
}

void Application::linesCreate(){
	Line newline;
	string foo;
	int id_number, freq, time;
	string stop;
	vector<string> stops;
	vector<int> times;
	LineList lines = company.getLines();

	cout << "Insert the new line information: \n\n";
	do {
		cout << "Insert id_number: "; validArg(id_number);
		if (validIdLines(id_number)) {
			cout << "The line already exists. Please insert another id or delete the line." << endl;
		} else {
			break;
		}
	} while (true);

	cout << "Insert frequency: "; validArg(freq);
	cout << "Insert the stops:(Press enter to stop) ";
	while(true){
		getline(cin,stop);
		if(stop == "") break;
		stops.push_back(stop);
	}
	cout << "Insert the times:(Press enter to stop) ";
	while(true){
		time = 0;
		getline(cin,foo);
		if(foo == "") break;
		while(true){
			time = 0;
			try{
				time = stoi(foo, nullptr);
			}
			catch(const std::invalid_argument& ia){
				cout << "Invalid input. Reenter." << endl; getline(cin,foo);
			}
			if(time) break;
		}
		times.push_back(time);
	}
	newline.setId(id_number);
	newline.setFreq(freq);
	newline.setStops(stops);
	newline.setTimes(times);
	company.addLine(newline);
	linesChanged = true;
}

void Application::linesUpdate(){
	int id;
	linesSummaryShow();
	do {
		cout << "Insert the line to change: ";
		validArg(id);
		if (validIdLines(id)) break;
		else {
			cout << "Invalid id. Reenter." << endl;
		}
	} while (true);

	cout << endl;

	linesDetailShow(id);
	do {
		displayUpdateMenu(id, LINES_IDENTIFIER);
		updateMenu(id, LINES_IDENTIFIER);
	} while (INSIDE_SUBMENU);
}

void Application::linesUpdateFreq(int id_number) {
	Line l = company.getLines()[id_number];
	cout << "The current frequeny for line " << id_number << " is " << l.getFreq() << "min.\n";
	string foo;
	int freq;
	do {
		bool success = true;
		cout << "Insert the new frequency: ";
		getline(cin,foo);
		try{
			freq = stoi(foo, nullptr);
		}
		catch(const std::invalid_argument& ia){
			cout << "Invalid input. Reenter." << endl;
			success = false;
		}
		if(success) break;
	} while (true);
	l.setFreq(freq);
	company.setLine(id_number, l);
	linesChanged= true;
	cout << "Line updated successfully.\nPress any key to continue.";
	getchar();
}

void Application::linesUpdateStops(int id_number) {
	Line l = company.getLines()[id_number];
	cout << "The current stops for line " << id_number << " are ";
	for (int i = 0; i < l.getStops().size(); i++){
		cout << l.getStops().at(i);
		if (i != l.getStops().size() - 1) cout << ", ";
		else cout << ".\n";
	}
	string foo;
	vector<string> stops;
	do {
		cout << "Insert the new stops (Press enter twice to stop): ";
		getline(cin, foo);
		if(foo == "") break;
		stops.push_back(foo);
	} while (true);
	l.setStops(stops);
	company.setLine(id_number, l);
	linesChanged= true;
	cout << "Line updated successfully.\nPress any key to continue.";
	getchar();
}
void Application::linesUpdateTimes(int id_number) {
	Line l = company.getLines()[id_number];
	cout << "The current times for line " << id_number << " are ";
	for (int i = 0; i < l.getTimes().size(); i++){
		cout << l.getTimes().at(i);
		if (i != l.getTimes().size() - 1) cout << ", ";
		else cout << ".\n";
	}
	string foo;
	vector<int> times;
	do {
		int time;
		cout << "Insert the new times (Press enter twice to stop): ";
		do {
			bool success = true;
			getline(cin, foo);
			try {
				time = stoi(foo, nullptr);
			}
			catch(const std::invalid_argument& ia) {
				cout << "Invalid input. Reenter.\n";
				success = false;
			}
			if (success) break;
		} while (true);
		times.push_back(time);
		if (foo == "") break;
	} while (true);
	l.setTimes(times);
	company.setLine(id_number, l);
	linesChanged= true;
	cout << "Line updated successfully.\nPress any key to continue.";
	getchar();
}

void Application::linesDelete(){
	linesSummaryShow();
	int id;
	do {
		cout << "Line's id:";
		validArg(id);
		if (validIdLines(id)) break;
		else {
			cout << "Invalid id. Reenter." << endl;
		}
	} while (true);
	company.eraseLine(id);
	linesChanged= true;
	cout << "Line " << id << " deleted successfully.\n";
}

void Application::searchStops(string stop, vector<Stop> &stopsDirect, vector<Stop> &stopsInverse){
	vector<Stop> stopsD;
	vector<Stop> stopsI;
	LineList lines = company.getLines();
	for (auto& x: lines) {
		Line l = x.second;
		for (size_t x = 0; x < l.getStops().size(); x++) {
			if (l.getStops().at(x) == stop) {

				// SENTIDO DIRETO

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

				//SENTIDO INVRSO

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

int Application::chooseLine() {
	int lineID;
	LineList lines = company.getLines();
	if (!lines.empty()) {
		cout << "Available line IDs: ";
		for (auto& x:lines) {
			Line l = x.second;
			cout << l.getId() << " ";
		}
		cout << endl;
	}
	do {
		cout << "Choose line: ";
		validArg(lineID);
		if (validIdLines(lineID)) break;
		else {
			cout << "Invalid id. Reenter.";
		}
	} while (true);
	return lineID;
}

void Application::printTimes(vector<Clock> time, Line line, int &n, int d){
	vector<string> stops = line.getStops();
	int freq = line.getFreq();
	int t;
	bool end = false;
	cout << std::left;
	while(!end){
		for (int i = 0; i < time.size(); i++) {
			string v;
			if (time.at(i).hours< 10) {
				v = "0" + to_string(time.at(i).hours) + ":";
			} else
				v = to_string(time.at(i).hours) + ":";

			if (time.at(i).mins < 10) {
				v = v + "0" + to_string(time.at(i).mins);
			} else
				v = v + to_string(time.at(i).mins);
			if(d == 1){
				t= i;
			}else t = stops.size() -1 -i;
			if(stops.at(t).size() < 5){
				cout << setw(5) << v;
			}else cout << setw(stops.at(t).size()) << v;
			if(i != stops.size()-1){
				cout << setw(3) << " ";
			}else cout << endl;
		}
		for(int i=0; i< time.size(); i++){
			time.at(i) = addTime(freq, time.at(i));
		}
		if(d==1){
			n++;
			if(time.at(0).hours >= day_end) end =true;
		}
		if(d == -1){
			n--;
			if(n == 0) end = true;
		}
	}
}

void Application::linesSchedule(){
	int sum;
	Clock start_time;
	start_time.hours = day_start;
	start_time.mins = 0;
	int n =0;
	string s;
	vector<Clock> time;
	vector <Clock> time2;

	Line line = company.getLines()[chooseLine()];

	cout << "Direction: " << line.getStops().at(0);
	cout << " to " << line.getStops().at(line.getStops().size()-1) << endl << endl;
	cout << std::left;
	for(int i=0; i< line.getStops().size(); i++){
		if(line.getStops().at(i).size() < 5){
			cout << setw(5) << line.getStops().at(i);
		}else cout << setw(line.getStops().at(i).size()) << line.getStops().at(i);
		if(i != line.getStops().size()-1){
			cout << setw(3) << " ";
		}else cout << endl << endl;
	}

	time.push_back(start_time);
	sum = 0;
	for(int i=0; i<line.getTimes().size(); i++){
		sum = sum + line.getTimes().at(i);
		time.push_back(addTime(sum , start_time));
	}
	printTimes(time, line, n, 1);
	cout << endl << endl;

	cout << "Direction: " << line.getStops().at(line.getStops().size()-1);
	cout << " to " << line.getStops().at(0) << endl << endl;
	cout << std::left;
	for(int i = line.getStops().size()-1; i >= 0; i--){
		if(line.getStops().at(i).size() < 5){
			cout << setw(5) << line.getStops().at(i);
		}else cout << setw(line.getStops().at(i).size()) << line.getStops().at(i);
		if( i != 0){
			cout << setw(3) << " ";
		}else cout << endl << endl;
	}
	start_time = addTime(sum, start_time);
	time2.push_back(start_time);
	sum = 0;
	for(int i=line.getTimes().size()-1 ; i>=0; i--){
		sum = sum + line.getTimes().at(i);
		time2.push_back(addTime(sum , start_time));
	}
	printTimes(time2, line, n, -1);

}

void Application::linesTravelTimes(){
	string stop1, stop2;
	vector<Stop> stopsDirect1, stopsDirect2, stopsInverse1, stopsInverse2;
	do {
		cout << "Insert the first stop name: ";
		getline(cin, stop1);
		searchStops(stop1, stopsDirect1,  stopsInverse1);

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

	for(int i=0; i<stopsDirect1.size(); i++){
		for(int x=0; x< stopsDirect2.size(); x++){
			if(stopsDirect1.at(i).getLineId() == stopsDirect2.at(x).getLineId()){
				if(stopsDirect1.at(i).getPosInLine() < stopsDirect2.at(x).getPosInLine()){
					IDs.push_back(stopsDirect1.at(i).getLineId());
					directions.push_back(0);
					int time = 0;
					for(int z = stopsDirect1.at(i).getPosInLine(); z < stopsDirect2.at(x).getPosInLine(); z++){
						time += company.getLines()[stopsDirect1.at(i).getLineId()].getTimes().at(z);
					}
					times.push_back(time);
					vector<string> stops;
					for(int z = stopsDirect1.at(i).getPosInLine(); z <= stopsDirect2.at(x).getPosInLine(); z++){
						stops.push_back(company.getLines()[stopsDirect1.at(i).getLineId()].getStops().at(z));
					}
					routes.push_back(stops);
					break;
				}
			}
		}
	}

	for(int i=0; i<stopsInverse1.size(); i++){
		for(int x=0; x< stopsInverse2.size(); x++){
			if(stopsInverse1.at(i).getLineId() == stopsInverse2.at(x).getLineId()){
				if(stopsInverse1.at(i).getPosInLine() > stopsInverse2.at(x).getPosInLine()){
					IDs.push_back(stopsInverse1.at(i).getLineId());
					directions.push_back(1);
					int time = 0;
					for(int z = stopsInverse1.at(i).getPosInLine() -1; z >= stopsInverse2.at(x).getPosInLine(); z--){
						time += company.getLines()[stopsDirect1.at(i).getLineId()].getTimes().at(z);
					}
					times.push_back(time);
					vector<string> stops;
					for(int z = stopsInverse1.at(i).getPosInLine() ; z >= stopsInverse2.at(x).getPosInLine(); z--){
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
	}
}


void Application::linesStopLines(){
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

void Application::printTable(Stop stop, int duration, Clock start, string begin, string end, int &n){
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
	if(!direction){
		while(true){
			int foo = time.hours;
			time = addTime(freq,time);
			Clock foo2 = subTime(travel,time);
			if(foo2.hours >= day_end){
				hours.push_back(temp);
				break;
			}
			else if(time.hours > foo){
				hours.push_back(temp);
				temp.resize(0);
				temp.push_back(time);
				n++;
			}else{
				temp.push_back(time);
				n++;
			}
		}
	}else{
		while(true){
			int foo = time.hours;
			time = addTime(freq, time);
			if(n == 0){
				hours.push_back(temp);
				break;
			}
			else if(time.hours > foo){
				hours.push_back(temp);
				temp.resize(0);
				temp.push_back(time);
				n--;
			}else if(foo == 23 && time.hours == 0){
				hours.push_back(temp);
				temp.resize(0);
				temp.push_back(time);
				n--;
			}else{
				temp.push_back(time);
				n--;
			}
		}
	}
	int id = stop.getLineId();
	cout << "Line: " << id << " - " << stop.getName() << endl;
	cout << "Direction: " << begin;
	cout << " to " << end << endl << endl;
	for(int i=0; i<hours.size(); i++){
		cout << setw(6) << hours.at(i).at(0).hours;
	}
	cout << endl;
	for(int i=0; i< hours.size(); i++){
		cout << setw(6) << "--";
	}
	int size = 0;
	for(int i = 0; i < hours.size(); i++){
		size = size + hours.at(i).size();
	}
	cout << endl;
	int t=0;
	while(size>0){
		for(int i=0; i<hours.size(); i++){
			string s;
			if(t>=hours.at(i).size()){
				cout << setw(6) << " ";
			}
			else if(hours.at(i).at(t).mins < 10){
				s = "0" + to_string(hours.at(i).at(t).mins);
				cout << setw(6) << s;
				size--;
			}else{
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
	int duration= 0;
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
	start.hours = day_start;
	start.mins = 0;
	for(int i = 0; i<stopsDirect.size(); i++){
		travel  = stopsDirect.at(i).getTimeFromStart();
		Line line = company.getLines()[stopsDirect.at(i).getLineId()];
		for(int t=0; t<line.getTimes().size(); t++){
			duration = duration + line.getTimes().at(t);
		}
		printTable(stopsDirect.at(i),duration, start, line.getStops().at(0), line.getStops().at(line.getStops().size()-1), n );
	}
	start = addTime(duration, start);
	for(int i = 0; i<stopsInverse.size(); i++){
		travel = stopsInverse.at(i).getTimeFromStart();
		Line line = company.getLines()[stopsInverse.at(i).getLineId()];
		printTable(stopsInverse.at(i), duration, start, line.getStops().at(line.getStops().size()-1), line.getStops().at(0), n);
	}
}

void Application::driversShow(){
	printDrivers();
	cout << endl << endl;
	cout << "Press any key to continue.";
	getchar();

}

void Application::printDrivers() {
	DriverList drivers = company.getDrivers();
	cout << std::left << setw(4) << "ID" << setw(3) << " " << setw(30) << "NAME" << setw(3) << " " << setw(7);
	cout << "H/SHIFT" << setw(3) << " " << setw(6) << "H/WEEK" << setw(3) << " " << setw(6) << "H/REST" << endl;
	for (auto& x: drivers) {
		Driver d = x.second;
		cout << std::left << setw(4) << d.getId() << setw(3) << " ";
		cout << setw(30) << d.getName() << setw(3) << " ";
		cout << std::right << setw(7) << d.getMaxShift() << setw(3) << " ";
		cout << setw(6) << d.getMaxWeek() << setw(3) << " ";
		cout << setw(6) << d.getMinRest()<< endl;
	}
}
void Application::driversDetailShow(int id_number){
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

void Application::driversCreate(){
	Driver newdriver;
	string foo;
	int id_number, max_shift, max_week, min_rest;
	string name;
	DriverList drivers = company.getDrivers();

	cout << "Insert the new driver information: \n\n";
	do {
		cout << "Insert id_number: "; validArg(id_number);
		if (validIdDrivers(id_number)) {
			cout << "This driver already exists. Please insert another id or delete the driver." << endl;
		} else {
			break;
		}
	} while (true);

	cout << "Name: ";
	getline(cin, name);
	cout << "Daily shift(h): ";
	validArg(max_shift);
	cout << "Weekly shift: ";
	validArg(max_week);
	cout << "Rest(h):";
	validArg(min_rest);

	newdriver.setId(id_number);
	newdriver.setName(name);
	newdriver.setMaxShift(max_shift);
	newdriver.setMaxWeek(max_week);
	newdriver.setMinRest(min_rest);
	company.addDriver(newdriver);
	driversChanged = true;
}

void Application::driversUpdate(){
	int id;
	printDrivers();
	do {
		cout << "Insert the driver to change: ";
		validArg(id);
		if (validIdDrivers(id)) break;
		else {
			cout << "Invalid id. Reenter." << endl;
		}
	} while (true);

	cout << endl;

	driversDetailShow(id);
	do {
		displayUpdateMenu(id, DRIVERS_IDENTIFIER);
		updateMenu(id, DRIVERS_IDENTIFIER);
	} while (INSIDE_SUBMENU);
}

void Application::driversUpdateName(int id_number){
	Driver d = company.getDrivers()[id_number];
	string foo;
	cout << "The current name for driver " << id_number << " is " << d.getName() << endl;
	cout << "Insert the new name: ";
	getline(cin, foo);
	d.setName(foo);
	company.setDriver(id_number, d);
	driversChanged = true;
	cout << "Driver updated successfully.\nPress any key to continue.";
	getchar();
}

void Application::driversUpdateMaxShift(int id_number){
	Driver d = company.getDrivers()[id_number];
	string foo;
	int shift;
	cout << "The current daily shift for driver " << id_number << " is " << d.getMaxShift() << "h.";
	do {
		bool success = true;
		cout << "Insert the new daily shift(h): ";
		getline(cin,foo);
		try{
			shift = stoi(foo, nullptr);
		}
		catch(const std::invalid_argument& ia){
			cout << "Invalid input. Reenter." << endl;
			success = false;
		}
		if(success) break;
	} while (true);
	d.setMaxShift(shift);
	company.setDriver(id_number, d);
	driversChanged = true;
	cout << "Driver updated successfully.\nPress any key to continue.";
	getchar();
}

void Application::driversUpdateMaxWeek(int id_number){
	Driver d = company.getDrivers()[id_number];
	string foo;
	int shift;
	cout << "The current weekly shift for driver " << id_number << " is " << d.getMaxWeek() << "h.";
	do {
		bool success = true;
		cout << "Insert the new weekly shift(h): ";
		getline(cin,foo);
		try{
			shift = stoi(foo, nullptr);
		}
		catch(const std::invalid_argument& ia){
			cout << "Invalid input. Reenter." << endl;
			success = false;
		}
		if(success) break;
	} while (true);
	d.setMaxWeek(shift);
	company.setDriver(id_number, d);
	driversChanged = true;
	cout << "Driver updated successfully.\nPress any key to continue.";
	getchar();
}

void Application::driversUpdateMinRest(int id_number){
	Driver d = company.getDrivers()[id_number];
	string foo;
	int rest;
	cout << "The current daily shift for driver " << id_number << " is " << d.getMinRest() << "h.";
	do {
		bool success = true;
		cout << "Insert the new minimum rest(h): ";
		getline(cin,foo);
		try{
			rest = stoi(foo, nullptr);
		}
		catch(const std::invalid_argument& ia){
			cout << "Invalid input. Reenter." << endl;
			success = false;
		}
		if(success) break;
	} while (true);
	d.setMinRest(rest);
	company.setDriver(id_number, d);
	driversChanged = true;
	cout << "Driver updated successfully.\nPress any key to continue.";
	getchar();
}

void Application::driversDelete(){
	printDrivers();
	int id;
	do {
		cout << "Driver's id:";
		validArg(id);
		if (validIdLines(id)) break;
		else {
			cout << "Invalid id. Reenter." << endl;
		}
	} while (true);
	validIdDrivers(id);
	company.eraseDriver(id);
	cout << "Driver " << id << " deleted successfully.\n";
	driversChanged = true;
}

void Application::exitMenu(){
	cout << "bye bye";
	exit(0);
}


void Application::setupMenu(){
	mainMenu["lines show"] = &Application::linesShow;
	mainMenu["lines create"] = &Application::linesCreate;
	mainMenu["lines update"] = &Application::linesUpdate;
	mainMenu["lines delete"] = &Application::linesDelete;
	mainMenu["lines schedules"] = &Application::linesSchedule;
	mainMenu["lines travel time"] = &Application::linesTravelTimes;
	mainMenu["lines stop lines"] = &Application::linesStopLines;
	mainMenu["lines stop timetable"] = &Application::linesStopTimetable;
	mainMenu["drivers show"] = &Application::driversShow;
	mainMenu["drivers create"] = &Application::driversCreate;
	mainMenu["drivers update"] = &Application::driversUpdate;
	mainMenu["drivers delete"] = &Application::driversDelete;
	mainMenu["exit"] = &Application::exitMenu;
	//shortcuts
	mainMenu["ls"] = &Application::linesShow;
	mainMenu["lc"] = &Application::linesCreate;
	mainMenu["lu"] = &Application::linesUpdate;
	mainMenu["ld"] = &Application::linesDelete;
	mainMenu["lsch"] = &Application::linesSchedule;
	mainMenu["ltt"] = &Application::linesTravelTimes;
	mainMenu["lsl"] = &Application::linesStopLines;
	mainMenu["lst"] = &Application::linesStopTimetable;
	mainMenu["ds"] = &Application::driversShow;
	mainMenu["dc"] = &Application::driversCreate;
	mainMenu["du"] = &Application::driversUpdate;
	mainMenu["dd"] = &Application::driversDelete;
	mainMenu["e"] = &Application::exitMenu;
	//line update menu
	lineUpdateMenu["frequency"] = &Application::linesUpdateFreq;
	lineUpdateMenu["stops"] = &Application::linesUpdateStops;
	lineUpdateMenu["times"] = &Application::linesUpdateTimes;
	//driver update menu
	driverUpdateMenu["name"] = &Application::driversUpdateName;
	driverUpdateMenu["h/day"] = &Application::driversUpdateMaxShift;
	driverUpdateMenu["h/week"] = &Application::driversUpdateMaxWeek;
	driverUpdateMenu["h/rest"] = &Application::driversUpdateMinRest;
}

void Application::displayMainMenu(){
	cout << "\n";
	cout << "Lines" << endl;
	cout << "     Show, Create, Update, Delete" << endl;
	cout << "     Schedules, Travel Time" << endl;
	cout << "     Stop Lines, Stop Timetable" << endl;
	cout << "Drivers" << endl;
	cout << "     Show, Create, Update, Delete" << endl;
	cout << "Exit" << endl;
}

void Application::displayUpdateMenu(int id_number, string identifier){
	if (identifier == LINES_IDENTIFIER){
		cout << "Lines Update - Line " << id_number << " selected" << endl;
		cout << "     Frequency, Stops, Times" << endl;
	} else if (identifier == DRIVERS_IDENTIFIER) {
		cout << "Drivers Update - Driver " << id_number << " selected" << endl;
		cout << "     Name, H/Day, H/Week, H/Rest" << endl;
	}
	cout << "     Back" << endl;
}

void Application::inputMenu(){
	string command;
	displayMainMenu();
	do {
		cout << "Command: ";
		getline(cin,command);
		normalize(command);
		if(mainMenu.find(command) != mainMenu.end()){
			(this->*mainMenu[command])();
			break;
		} else cout << "Invalid command.\n";
	} while(true);
}

void Application::updateMenu(int id_number, string identifier){
	map<string,UpdateMenuOption> updateMenu;
	if (identifier == LINES_IDENTIFIER) updateMenu = lineUpdateMenu;
	else if (identifier == DRIVERS_IDENTIFIER)  updateMenu = driverUpdateMenu;
	string command;
	do {
		INSIDE_SUBMENU = true;
		cout << "Command: ";
		getline(cin,command);
		normalize(command);
		if (command == "back") {
			INSIDE_SUBMENU = false;
			break;
		}
		else if(updateMenu.find(command) != updateMenu.end()){
			(this->*updateMenu[command])(id_number);
			break;
		} else cout << "Invalid command.\n";
	} while(true);
}

vector<string> Application::linesToStrings() {
	vector<string> v;
	string next;
	LineList lines = company.getLines();
	for (auto &item: lines) {
		Line l = item.second;
		next.clear();
		next = to_string(l.getId()) + " ; " + to_string(l.getFreq()) + " ; ";
		for (size_t x = 0; x < l.getStops().size(); x++) {
			next += l.getStops().at(x);
			if (x != l.getStops().size() - 1) {
				next += ", ";
			}
			else {
				next += " ; ";
			}
		}
		for (size_t x = 0; x < l.getTimes().size(); x++) {
			next += to_string(l.getTimes().at(x));
			if (x != l.getTimes().size() - 1) next += ", ";
		}
		v.push_back(next);
	}
	return v;
}

vector<string> Application::driversToStrings() {
	vector<string> v;
	string next;
	DriverList drivers = company.getDrivers();
	for (auto &item: drivers) {
		Driver d = item.second;
		next.clear();
		next = to_string(d.getId()) + " ; " + d.getName() + " ; " + to_string(d.getMaxShift()) + " ; " + to_string(d.getMaxWeek()) + " ; " +
				to_string(d.getMinRest());
		v.push_back(next);
	}
	return v;
}

void Application::saveChanges(string identifier) {
	ofstream output_file;
	string newStrings;
	if (identifier == LINES_IDENTIFIER) {

	}
}

Application::~Application() {
	// TODO Auto-generated destructor stub
}

