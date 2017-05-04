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

void validArg(int &variable){
	variable = 0;
	string foo;
	while(true){
		getline(cin,foo);
		try{
			variable = stoi(foo,nullptr);
		}
		catch(const std::invalid_argument& ia){
			cout << "Invalid input. Reenter." << endl;
		}
		if(variable) break;
	}
}

// Helpers for string processing
void trimstring(string &s){
	s = s.substr(s.find_first_not_of(" "));
	s = s.substr(0, s.find_last_not_of(" ")+1);
}

void normalize(string &s){
	transform(s.begin(), s.end(), s.begin(), ::tolower);
	trimstring(s);
}

// Generic functions to process files
void next(string &piece, string &line, string separator){
	int temp = line.find_first_of(separator);
	if(temp == string::npos){
		piece = line;
		line = "";
	}else{
		piece = line.substr(0,temp);
		line=line.substr(temp+1, line.length() - 1);
	}
	trimstring(piece);
}

void next(string &piece, string &line){
	next(piece,line,";");
}

void next(int &elem, string &piece, string separator){
	string elemstring;
	next(elemstring,piece,separator);
	elem = stoi(elemstring,nullptr);
}

// Functions to process lines' file
Line readLine(string &l){
	Line newline;
	string piece;

	int foo;
	next(foo,l,";");
	newline.setId(foo);
	next(foo,l,";");
	newline.setFreq(foo);

	next(piece,l);
	vector<string> s;
	while(piece!=""){
		string elem;
		next(elem,piece,",");
		s.push_back(elem);
	}
	newline.setStops(s);
	next(piece,l);
	vector<int> t;
	while(piece!=""){
		int elem;
		next(elem,piece,",");
		t.push_back(elem);
	}
	newline.setTimes(t);
	return newline;
}

Driver readDriver(string &d){
	Driver newdriver;

	int foo;
	string foo2;
	next(foo,d,";");
	newdriver.setId(foo);
	next(foo2,d);
	newdriver.setName(foo2);
	next(foo,d,";");
	newdriver.setMax_shift(foo);
	next(foo,d,";");
	newdriver.setMax_week(foo);
	next(foo,d,";");
	newdriver.setMin_rest(foo);
	return newdriver;
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
	Line line = company.getLines()[id];
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

	cout << "Insert the line to change: ";
	//input

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
	validIdLines(id);
	company.eraseLine(id);
	cout << "Line " << id << " deleted successfully.\n";
	linesChanged= true;
}

void Application::linesSchedule(){

}

void Application::linesTravelTimes(){

}

void Application::linesStopLines(){

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

