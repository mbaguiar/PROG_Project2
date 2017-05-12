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
	void loadBuses();
	void changeFile(string type);
	void setupMenu();
	void displayMainMenu();
	void displayUpdateMenu(int id_number, string identifier);
	map<string, MenuOption> getMainMenu();
	void inputMenu();
	void updateMenu(int id_number, string identifier);
	void linesShow();
	void linesSummaryShow();
	void linesDetailShow(int id_number);
	void searchStops(string stop, vector<Stop> &stopsDirect, vector<Stop> &stopsInverse);
	int chooseLine();
	void printTimes(vector<Clock> time, Line line, int &n, int d);
	void linesSchedule();
	void route(Stop stop1, Stop stop2, int pos1, int pos2, int &duration, vector<string> &route);
	void linesTravelTimes();
	void linesStopLines();
	void printTable(Stop stop, int duration, Clock start, string begin, string end, int &n);
	void linesStopTimetable();
	void driversDetailShow(int id_number);
	void printDrivers();
	void driversShow();
	void driversCreate();
	void driversUpdate();
	void driversUpdateName(int id_number);
	void driversUpdateMaxShift(int id_number);
	void driversUpdateMaxWeek(int id_number);
	void driversUpdateMinRest(int id_number);
	void driversDelete();
	void driversShowAssignedWork();
	void printBus(Bus bus, int day);
	void driversShowFreeTime();
	void driversAssignWork();
	void busesShow();
	void busesShowFreeTime();
	vector<string> linesToStrings();
	vector<string> driversToStrings();
	void saveChanges();
	void exitMenu();
	virtual ~Application();
};

#endif /* APPLICATION_H_ */
