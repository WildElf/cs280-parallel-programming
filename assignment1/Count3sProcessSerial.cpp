/*
Name: E. Jo Zimmerman
Course: CS280 
CRN: 36298
Assignment: Assignment 1 - Find 3s Serial
Date: 2016-02-03
*/
// Implementation file for Count3SProcessSerial
// Reads 32-bit floating point numbers from 
// a binary file and finds occurrences of 3.00
#include "Count3sProcessSerial.h"
#include <iostream>

using namespace std;

// searches for a fixed pattern of 3.00
int Count3sProcessSerial::searchFile(string file)
{
	const float SEARCH = 3.00;
	const int SIZE = 4;
	
	binaryFile.open(file, ios::binary);

	if (binaryFile.is_open())
	{
		cout << "In file " << file << endl;
		while (!binaryFile.eof())  // continues until end of file
		{
			binaryFile.read (reinterpret_cast<char *>(number), SIZE);
			for (int i=0; i<SIZE; i++)
			{
				zeroCheck = fabs(number[i] - SEARCH); // store absolute value difference
//				cout << zeroCheck << " - ";
			
				if (zeroCheck < 0.001)
					found++;
			}
		}
		binaryFile.close();
		cout << endl;
	}
	else
		cout << "Error: failed to open file " << file << endl;
		
	return found;
}

// demonstrating the class
int main()
{
	Count3sProcessSerial data;
	
	int num3s = data.searchFile("threesData.bin");

	cout << num3s << " occurrences of 3.00 found" << endl;
}