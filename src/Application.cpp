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
	cout << "Insert lines's file name" << endl;
	getline(cin,linesFilepath);
	linesfile.open(linesFilepath);

	while(linesfile.fail()){
		cout << "Error opening file. Try again.";
		cout << "Insert lines's file name" << endl;
		getline(cin,linesFilepath);
		linesfile.open(linesFilepath);
	}
	while(!linesfile.eof()) {
		getline(linesfile,l);
		company.addLine(readLine(l));
	}
	linesfile.close();

	cout << "Insert drivers' file name" << endl;
	getline(cin,driversFilepath);
	driversfile.open(driversFilepath);

	while(driversfile.fail()){
		cout << "Error opening file. Try again.";
		cout << "Insert drivers' file name" << endl;
		getline(cin,driversFilepath);
		driversfile.open(driversFilepath);
	}

	while(!driversfile.eof()) {
		getline(driversfile,d);
		company.addDriver(readDriver(d));
	}
	driversfile.close();

}

void Application::linesShow(){
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
	cout << endl;
	linesDetailShow(id);
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
				cout << "Invalid. Reenter." << endl; getline(cin,foo);
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
	cout << "Insert the line to change: ";
	do {
		cout << "Line's id:";
		validArg(id);
		if (validIdLines(id)) break;
		else {
			cout << "Invalid id. Reenter." << endl;
		}
	} while (true);

	cout << endl;

	linesDetailShow(id);
	cout << "Which field do you wish to update(id, freq, stops, times): ";
	string cmd;
	do {
		getline(cin, cmd);

	} while (true);
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
	cout << "Line " << id << " deleted successfully.\n";
	linesChanged= true;
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

void Application::linesSchedule(){

}

void Application::linesTravelTimes(){
	string stop1, stop2;
	vector<Stop> stopsDirect1, stopsDirect2, stopsInverse1, stopsInverse2;
	do {
		cout << "Insert the first stop name (CTRL-Z to cancel): ";
		getline(cin, stop1);
		if (cin.eof()) {
			cin.clear();
			return;
		}
		searchStops(stop1, stopsDirect1,  stopsInverse1);

		if (stopsDirect1.empty() && stopsInverse1.empty()) {
			cout << "Invalid stop name.\n";
		}
		else break;
	} while (true);

	do {
		cout << "Insert the second stop name (CTRL-Z to cancel): ";
		getline(cin, stop2);
		if (cin.eof()) {
			cin.clear();
			return;
		}
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
			for (int x = 0; x < routes.at(i).size(); x++) {
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

void Application::linesStopTimetable(){

}

void Application::driversSummaryShow(){
	DriverList drivers = company.getDrivers();
	cout << std::left << setw(4) << "ID" << setw(3) << " " << setw(30) << "NAME" << setw(3) << " " << setw(7) << "H/SHIFT"			<< setw(3) << " " << setw(6) << "H/WEEK" << setw(3) << " " << setw(6) << "H/REST" << endl;
	for (auto& x: drivers) {
		Driver d = x.second;
		cout << std::left << setw(4) << d.getId() << setw(3) << " ";
		cout << setw(30) << d.getName() << setw(3) << " ";
		cout << std::right << setw(7) << d.getShiftMaxDuration() << setw(3) << " ";
		cout << setw(6) << d.getMaxWeekWorkingTime() << setw(3) << " ";
		cout << setw(6) << d.getMinRestTime()<< endl;
	}
	cout << endl;
}

void Application::driversShow(){
	driversSummaryShow();
	int id;
	do {
		cout << "Driver's id:";
		validArg(id);
		if (validIdDrivers(id)) break;
		else {
			cout << "Invalid id. Reenter." << endl;
		}
	} while (true);
	Driver driver = company.getDrivers()[id];
	cout << std::left;
	cout << setw(15) << "ID: ";
	cout << driver.getId() << endl;
	cout << setw(15) << "Name: ";
	cout << driver.getName() << endl;
	cout << setw(15) << "Daily shift: ";
	cout << driver.getMaxWeekWorkingTime() << "h\n";
	cout << setw(15) << "Weekly shift: ";
	cout << driver.getShiftMaxDuration() << "h\n";
	cout << setw(15) << "Resting hours: ";
	cout << driver.getMinRestTime() << "h\n\n";
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
	newdriver.setMax_shift(max_shift);
	newdriver.setMax_week(max_week);
	newdriver.setMin_rest(min_rest);
	company.addDriver(newdriver);
	driversChanged = true;
}

void Application::driversUpdate(){

}

void Application::driversDelete(){
	driversSummaryShow();
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
	menu["lines show"] = &Application::linesShow;
	menu["lines create"] = &Application::linesCreate;
	menu["lines update"] = &Application::linesUpdate;
	menu["lines delete"] = &Application::linesDelete;
	menu["lines schedules"] = &Application::linesSchedule;
	menu["lines travel time"] = &Application::linesTravelTimes;
	menu["lines stop lines"] = &Application::linesStopLines;
	menu["lines stop timetable"] = &Application::linesStopTimetable;
	menu["drivers show"] = &Application::driversShow;
	menu["drivers create"] = &Application::driversCreate;
	menu["drivers update"] = &Application::driversUpdate;
	menu["drivers delete"] = &Application::driversDelete;
	menu["exit"] = &Application::exitMenu;
	//shortcuts
	menu["ls"] = &Application::linesShow;
	menu["lc"] = &Application::linesCreate;
	menu["lu"] = &Application::linesUpdate;
	menu["ld"] = &Application::linesDelete;
	menu["lsch"] = &Application::linesSchedule;
	menu["ltt"] = &Application::linesTravelTimes;
	menu["lsl"] = &Application::linesStopLines;
	menu["lst"] = &Application::linesStopTimetable;
	menu["ds"] = &Application::driversShow;
	menu["dc"] = &Application::driversCreate;
	menu["du"] = &Application::driversUpdate;
	menu["dd"] = &Application::driversDelete;
	menu["e"] = &Application::exitMenu;
}

void Application::displayMenu(){
	cout << "\n";
	cout << "Lines" << endl;
	cout << "     Show, Create, Update, Delete" << endl;
	cout << "     Schedules, Travel time" << endl;
	cout << "     Stop Lines, Stop Timetable" << endl;
	cout << "Drivers" << endl;
	cout << "     Show, Create, Update, Delete" << endl;
	cout << "Exit" << endl;
}

void Application::inputMenu(){
	string command;
	string foo;
	while(true){
		displayMenu();
		cout << "Command:";
		getline(cin,command);
		normalize(command);
		if(menu.find(command) != menu.end()){
			(this->*menu[command])();
		}else cout << "Invalid";
		cout << "\nPress enter to continue";
		getline(cin,foo);
	}
}
Application::~Application() {
	// TODO Auto-generated destructor stub
}

