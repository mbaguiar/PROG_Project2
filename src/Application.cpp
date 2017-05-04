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
	LineList l;
	DriverList d;
	Company c = Company("semprarrolar",l, d) ;
	company = c;
	linesFilepath = "";
	driversFilepath= "";
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

}

void Application::linesSummaryShow(){
	LineList lines = company.getLines();
	cout << "LINE SUMMARY\n\n";
		cout << std::left << setw(5) << "ID" << setw(3) << " " << setw(5) << "FREQ" << setw(3) << " " << "ROUTE" << endl;
//		for (LineList::iterator it  = lines.begin(); it < lines.end(); it++) {
//			Line l1 = lines.at(i);
//			cout << setw(5) << l1.id << setw(3) << " " << setw(5) << l1.freq << setw(3) << " ";
//			cout << l1.stops.at(0) << " <--> " << l1.stops.at(l1.stops.size() - 1) << endl;
//		}
		for (auto& x: lines) {
		    Line l = x.second;
		    cout << setw(5) << l.getId() << setw(3) << " " << setw(5) << l.getFreq() << setw(3) << " ";
		    cout << l.getStops().at(0) << " <--> " << l.getStops().at(l.getStops().size() - 1) << endl;
		  }
		cout << endl;
}

void Application::linesCreate(){

}

void Application::linesUpdate(){

}

void Application::linesDelete(){

}

void Application::linesSchedule(){

}

void Application::linesTravelTimes(){

}

void Application::linesStopLines(){

}

void Application::linesStopTimetable(){

}

void Application::driversShow(){

}

void Application::driversCreate(){

}

void Application::driversUpdate(){

}

void Application::driversDelete(){

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

