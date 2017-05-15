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

	// Constructors

	Stop();

	// Get methods

	string getName() const;
	int getLineId() const;
	int getPosInLine() const;
	int getTimeFromStart() const;
	int getFreq() const;
	int getDirection() const;

	// Set methods

	void setName(string name);
	void setPosInLine(int posInLine);
	void setLineId(int LineId);
	void setTimeFromStart(int timeFromStart);
	void setFreq(int freq);
	void setDirection(int direction);

	virtual ~Stop();
};

#endif /* STOP_H_ */
