/*
 * RegisterSet.h

Name: E. Jo Zimmerman
Course: CS280
CRN: 36298
Assignment: #2 - Register Set
Date: 2016-2-14

Algorithm:

*/

#ifndef REGISTERSET_H_
#define REGISTERSET_H_
#include "IllegalArgumentException.h"
#include <bitset>

enum registerType { i, u, n, l, f, d };

using namespace std;

template<class ItemType>
class RegisterSet
{
private:
	int registerCount;
	registerType myType;
	ItemType* registerFile;
	bitset<3>* flagsCNZ;

public:
	RegisterSet();
	RegisterSet(registerType, int);
    void reset();
	ItemType get(int);
	void LD(int,ItemType);
	void ADD(int, int);
	void SUB(int, int);
	void MUL(int, int, int);
	void DIV(int, int, int);
	void STO(int, int);
	void printBitsets();
	virtual ~RegisterSet();

};

#endif /* REGISTERSET_H_ */
