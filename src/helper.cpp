/*
 * helper.cpp
 *
 *  Created on: May 8, 2017
 *      Author: mariana
 */
#include <iostream>
#include <string>
#include "Line.h"
#include "Driver.h"
#include "helper.h"

using namespace std;

void validArg(int &variable){
	bool success = true;
	string foo;
	do{
		getline(cin,foo);
		try{
			variable = stoi(foo,nullptr);
		}
		catch(const std::invalid_argument& ia){
			cout << "Invalid input. Reenter." << endl;
			success = false;
		}
		if(success) break;
	} while (true);
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
	newdriver.setMaxShift(foo);
	next(foo,d,";");
	newdriver.setMaxWeek(foo);
	next(foo,d,";");
	newdriver.setMinRest(foo);
	return newdriver;
}

Clock addTime(int min, Clock time){
	Clock result;
	result.hours = time.hours;
	result.mins= time.mins + min;
	while(result.mins >= 60){
		result.mins = result.mins - 60;
		result.hours = result.hours + 1;
	}
	if (result.hours >= 24){
		result.hours = result.hours -24;
	}
	return result ;
}

