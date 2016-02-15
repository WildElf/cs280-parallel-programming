/*
 IllegalArgumentException.cpp

Name: E. Jo Zimmerman
Course: CS280
CRN: 36298
Assignment: #2 - Register Set
Date: 2016-2-14

Algorithm:

*/

#include "IllegalArgumentException.h"

using namespace std;

IllegalArgumentException::IllegalArgumentException(const string& message): 
							logic_error("Illegal Argument Exception: " + message)
{
}
