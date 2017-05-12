//============================================================================
// Name        : PROG_Project2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Application.h"
using namespace std;

int main() {
	Application app;
	app.setupMenu();
	app.loadFiles();
	app.loadBuses();
	do {
	app.inputMenu();
	cout << "Press any key to continue.";
	getchar();
	} while (true);
	return 0;
}
