//============================================================================
// Name        : PROG_Project2.cpp
// Author      : Mariana Aguiar Tiago Fragoso
// Description : Semprarrolar project
//============================================================================

#include <iostream>
#include "Application.h"
using namespace std;

int main() {
	Application app;
	app.setupMenu();
	app.loadFiles();
	app.loadBuses();
	app.start();
	return 0;
}
