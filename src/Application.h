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
#include "helper.h"

using namespace std;


class Application {
typedef void(Application::*MenuOption)(void);
typedef void(Application::*UpdateMenuOption)(int id);
private:
	Company company;
	bool linesChanged;
	bool driversChanged;
	int day_start;
	int day_end;
	map<string,MenuOption> mainMenu;
	map<string,UpdateMenuOption> lineUpdateMenu;
	map<string,UpdateMenuOption> driverUpdateMenu;
	string linesFilepath;
	string driversFilepath;
	bool INSIDE_SUBMENU;
	string LINES_IDENTIFIER;
	string DRIVERS_IDENTIFIER;

public:
	Application();
	bool validIdLines(int id_number);
	bool validIdDrivers(int id_number);
	void loadFiles();
	void setupMenu();
	void displayMainMenu();
	void displayUpdateMenu(int id_number, string identifier);
	map<string, MenuOption> getMainMenu();
	void inputMenu();
	void updateMenu(int id_number, string identifier);
	void linesShow();
	void linesSummaryShow();
	void linesDetailShow(int id_number);
	void linesCreate();
	void linesUpdate();
	void linesUpdateFreq(int id_number);
	void linesUpdateStops(int id_number);
	void linesUpdateTimes(int id_number);
	void linesDelete();
	void searchStops(string stop, vector<Stop> &stopsDirect, vector<Stop> &stopsInverse);
	int chooseLine();
	int printTimes(vector<Clock> time, int freq, int n, int d);
	void printStops(int id_number, Line& line);
	void printStopsHeader(const Line& line, int id_number, int direction);
	void linesSchedule();
	void linesTravelTimes();
	void linesStopLines();
	void linesStopTimetable();
	void driversDetailShow(int id_number);
	void driversShow();
	void driversCreate();
	void driversUpdate();
	void driversUpdateName(int id_number);
	void driversUpdateMaxShift(int id_number);
	void driversUpdateMaxWeek(int id_number);
	void driversUpdateMinRest(int id_number);
	void driversDelete();
	void exitMenu();
	virtual ~Application();
};

#endif /* APPLICATION_H_ */
