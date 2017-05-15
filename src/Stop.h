/*
 * Stop.h
 *
 *  Created on: May 8, 2017
 *      Author: mariana
 */

#ifndef STOP_H_
#define STOP_H_

#include <string>
#include <iostream>

using namespace std;

class Stop {
private:
	string name;
	int lineID;
	int posInLine;
	int timeFromStart;
	int freq;
	int direction;
public:
	Stop();
	virtual ~Stop();
	string getName() const;
	int getLineId() const;
	int getPosInLine() const;
	int getTimeFromStart() const;
	int getFreq() const;
	int getDirection() const;
	void setName(string name);
	void setPosInLine(int posInLine);
	void setLineId(int LineId);
	void setTimeFromStart(int timeFromStart);
	void setFreq(int freq);
	void setDirection(int direction);
};

#endif /* STOP_H_ */
