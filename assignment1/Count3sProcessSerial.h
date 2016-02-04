/*
Name: E. Jo Zimmerman
Course: CS280 
CRN: 36298
Assignment: Assignment 1 - Find 3s Serial
Date: 2016-02-03
*/
// header file for Count3SProcessSerial
// Reads 32-bit floating point numbers from 
// a binary file and finds occurrences of 3.00
#ifndef COUNT_3S_PROCESS_SERIAL_H
#define COUNT_3S_PROCESS_SERIAL_H
#include <fstream>
#include <cmath>
#include <string>

using namespace std;

class Count3sProcessSerial
{
	private:
		ifstream binaryFile;
		float zeroCheck;
		float number[4];
		string fileName;
		int found;
	public:
		Count3sProcessSerial()
			{ found = 0; }
		int searchFile(string);
};

#endif
