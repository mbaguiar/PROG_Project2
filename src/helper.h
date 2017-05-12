/*
 * helper.h
 *
 *  Created on: May 8, 2017
 *      Author: mariana
 */

#ifndef SRC_HELPER_H_
#define SRC_HELPER_H_

struct Clock{
	int hours;
	int mins;
	bool am;
};

void validArg(int &variable);
void treatTime(int &day, int &hours, int &mins, int time);
string timeToString(int hours1, int hours2, int mins1, int mins2);
void trimstring(string &s);
void normalize(string &s);
void next(string &piece, string &line, string separator);
void next(string &piece, string &line);
void next(int &elem, string &piece, string separator);
Line readLine(string &l);
Driver readDriver(string &d);
Clock addTime(int min, Clock time);
Clock subTime(int min, Clock time);
void printDay(int day);


#endif /* SRC_HELPER_H_ */
