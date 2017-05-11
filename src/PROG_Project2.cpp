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
	do {
	app.inputMenu();
	} while (true);
	return 0;
}
