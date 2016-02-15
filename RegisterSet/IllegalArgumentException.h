/*
 IllegalArgumentException.h

Name: E. Jo Zimmerman
Course: CS280
CRN: 36298
Assignment: #2 - Register Set
Date: 2016-2-14

Algorithm:

*/

#ifndef ILLEGALARGUMENTEXCEPTION_H_
#define ILLEGALARGUMENTEXCEPTION_H_

#include <stdexcept>
#include <string>

using namespace std;

class IllegalArgumentException : public logic_error
{
public:
	IllegalArgumentException(const string& message = "");
};

#endif /* ILLEGALARGUMENTEXCEPTION_H_ */
