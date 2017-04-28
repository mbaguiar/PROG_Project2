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


Application::Application() {
	day_start = 7;
	day_end = 23;
	LineList l;
	DriverList d;
	Company c = Company("semprarrolar",l, d) ;
	company = c;
}

void Application::linesShow(){

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

Application::~Application() {
	// TODO Auto-generated destructor stub
}

