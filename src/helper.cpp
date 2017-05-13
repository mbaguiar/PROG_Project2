/*
 * helper.cpp
 *
 *  Created on: May 8, 2017
 *      Author: mariana
 */
#include <iostream>
#include <iomanip>
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
		if (variable <= 0){
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
	for (int i = 0; i < s.size(); i++) {
		s.at(i) = tolower(s.at(i));
	}
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
	while(piece != ""){
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
		result.am = true;
	}
	return result ;
}

Clock subTime(int min, Clock time){
	Clock result;
	result.hours = time.hours;
	result.mins = time.mins - min;
	while(result.mins < 0){
		result.mins = result.mins + 60;
		result.hours = result.hours -1;
	}
	if(result.hours < 0){
		result.hours = result.hours + 24;
	}
	return result;
}

void treatTime(int &day, int &hours, int &mins, int time){
	day = time/1440 + 1;
	hours = (time%1440)/60 ;
	mins = (time%1440)%60;
}

string timeToString(int hours1, int hours2, int mins1, int mins2){
	string s;
	if(hours1 < 10){
		s = s + "0" + to_string(hours1) + ":";
	}else s = s + to_string(hours1) + ":";
	if(mins1 < 10){
		s = s + "0" + to_string(mins1) + "-";
	}else s = s + to_string(mins1) + "-";
	if(hours2 < 10){
		s = s + "0" + to_string(hours2) + ":";
	}else s = s + to_string(hours2) + ":";
	if(mins2 < 10){
		s = s + "0" + to_string(mins2) ;
	}else s = s + to_string(mins2) ;
	return s;
}

void printDay(int day){
	switch(day){
	case 1:
		cout << setw(3) << "Mon"; break;
	case 2:
		cout << setw(3) << "Tue"; break;
	case 3:
		cout << setw(3) << "Wed"; break;
	case 4:
		cout << setw(3) << "Thu"; break;
	case 5:
		cout << setw(3) << "Fri"; break;
	case 6:
		cout << setw(3) << "Sat"; break;
	case 7:
		cout << setw(3) << "Sun"; break;
	}
}

void timeToMins(int day, int hours, int mins, int &time){
	time = 1440 * day;
	time += 60 * hours;
	time += mins;
}

bool sortShifts(Shift i, Shift j) {
	return (i.getStartTime() < j.getStartTime());
}

struct sortShifts
{
    inline bool operator() (const Shift& i, const Shift& j)
    {
        return (i.getStartTime() < j.getStartTime());
    }
};
