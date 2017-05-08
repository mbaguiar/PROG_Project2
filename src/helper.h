/*
 * helper.h
 *
 *  Created on: May 8, 2017
 *      Author: mariana
 */

#ifndef SRC_HELPER_H_
#define SRC_HELPER_H_

void validArg(int &variable);
void trimstring(string &s);
void normalize(string &s);
void next(string &piece, string &line, string separator);
void next(string &piece, string &line);
void next(int &elem, string &piece, string separator);
Line readLine(string &l);
Driver readDriver(string &d);


#endif /* SRC_HELPER_H_ */
