/*
 * Application.h
 *
 *  Created on: Apr 28, 2017
 *      Author: mariana
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <string>
#include <map>
#include "Company.h"
#include <iostream>

using namespace std;


class Application {
typedef void(Application::*MenuOption)(void);
private:
	Company company;
	int day_start;
	int day_end;
	map<string,MenuOption> menu;
public:
	Application();
	void setupMenu();
	void displayMenu();
	void linesShow();
	void linesCreate();
	void linesUpdate();
	void linesDelete();
	void linesSchedule();
	void linesTravelTimes();
	void linesStopLines();
	void linesStopTimetable();
	void driversShow();
	void driversCreate();
	void driversUpdate();
	void driversDelete();
	void exitMenu();
	virtual ~Application();
};

#endif /* APPLICATION_H_ */
