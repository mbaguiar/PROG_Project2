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
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "Company.h"

using namespace std;


class Application {
typedef void(Application::*MenuOption)(void);
private:
	Company company;
	bool linesChanged;
	bool driversChanged;
	int day_start;
	int day_end;
	map<string,MenuOption> menu;
	string linesFilepath;
	string driversFilepath;

public:
	Application();
	bool validIdLines(int id_number);
	bool validIdDrivers(int id_number);
	void loadFiles();
	void setupMenu();
	void displayMenu();
	void inputMenu();
	void linesShow();
	void linesSummaryShow();
	void linesCreate();
	void linesUpdate();
	void linesDelete();
	void linesSchedule();
	void linesTravelTimes();
	void linesStopLines();
	void linesStopTimetable();
	void driversSummaryShow();
	void driversShow();
	void driversCreate();
	void driversUpdate();
	void driversDelete();
	void exitMenu();
	virtual ~Application();
};

#endif /* APPLICATION_H_ */
