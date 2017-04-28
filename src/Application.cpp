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
	company = new Company;
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
	menu["lines show"] = linesShow;
	menu["lines create"] = linesCreate;
	menu["lines update"] = linesUpdate;
	menu["lines delete"] = linesDelete;
	menu["lines schedules"] = linesSchedule;
	menu["lines travel time"] = linesTravelTimes;
	menu["lines stop lines"] = linesStopLines;
	menu["lines stop timetable"] = linesStopTimetable;
	menu["drivers show"] = driversShow;
	menu["drivers create"] = driversCreate;
	menu["drivers update"] = driversUpdate;
	menu["drivers delete"] = driversDelete;
	menu["exit"] = exitMenu;
	//shortcuts
	menu["ls"] = linesShow;
	menu["lc"] = linesCreate;
	menu["lu"] = linesUpdate;
	menu["ld"] = linesDelete;
	menu["lsch"] = linesSchedule;
	menu["ltt"] = linesTravelTimes;
	menu["lsl"] = linesStopLines;
	menu["lst"] = linesStopTimetable;
	menu["ds"] = driversShow;
	menu["dc"] = driversCreate;
	menu["du"] = driversUpdate;
	menu["dd"] = driversDelete;
	menu["e"] = exitMenu;
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

