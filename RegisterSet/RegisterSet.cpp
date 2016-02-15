/*
RegisterSet.cpp

Name: E. Jo Zimmerman
Course: CS280
CRN: 36298
Assignment: #2 - Register Set
Date: 2016-2-14

Algorithm:

*/
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <string>
#include <limits>
#include "RegisterSet.h"

using namespace std;

template<class ItemType>
RegisterSet<ItemType>::RegisterSet() {

	myType = i;
	registerFile = (ItemType*)calloc(sizeof(ItemType),9);

	registerCount = 9;
	flagsCNZ = new bitset<3>[registerCount];
}

template<class ItemType>
RegisterSet<ItemType>::RegisterSet(registerType rType, int count)
{


	if (count > 0 && count < 10)
	{
		myType = rType;
		registerFile = calloc(sizeof(ItemType), count);
		registerCount = count;
		flagsCNZ = new bitset<3>[registerCount];

	}
	else
	{
		string message = "RegisterSet constructor used invalid register count";
		throw(IllegalArgumentException(message));
	}

}

template<class ItemType>
RegisterSet<ItemType>::~RegisterSet() {

	delete registerFile;
	delete flagsCNZ;
}

template<class ItemType>
ItemType RegisterSet<ItemType>::get(int registerIndex)
{
//	ItemType returnValue = registerFile[registerIndex];

	if (flagsCNZ[registerIndex][2] == 1)
		return 0;
	else if (flagsCNZ[registerIndex][1] == 1 && flagsCNZ[registerIndex][0] == 1)
		return (sizeof(ItemType) + registerFile[registerIndex]) * -1;
	else if (flagsCNZ[registerIndex][1] == 1)
		return registerFile[registerIndex] * -1;
	else if (flagsCNZ[registerIndex][0] == 1)
		return sizeof(ItemType) + registerFile[registerIndex];
	else
		return registerFile[registerIndex];

}

template<class ItemType>
void RegisterSet<ItemType>::LD(int index,ItemType newItem)
{
	if (index > 0 && index < 10)
		registerFile[index] = newItem;
	else
	{
		string message = "LD() called with an invalid register";
		throw(IllegalArgumentException(message));
	}
}

// ADD(int Register1, int Register2) - Add the value in register2 to Register1.
// If the result exceeds the value that can be stored in a register set the carry
// flag to 1
template<class ItemType>
void RegisterSet<ItemType>::ADD(int reg1, int reg2)
{
	if (flagsCNZ[reg1][0] == 1 && flagsCNZ[reg2][0] == 1)
	{
		string message = "ADD() called with overflow";
		throw(IllegalArgumentException(message));
	}
	else if ((flagsCNZ[reg1][1] == 0 && flagsCNZ[reg2] == 1)
			|| (flagsCNZ[reg1][1] == 1 && flagsCNZ[reg2] == 0))
	{
		if (registerFile[reg1] - registerFile[reg2] < 0)
		{
			registerFile[reg1] = (registerFile[reg1] - registerFile[reg2]) * -1;
			if (flagsCNZ[reg1][1] == 0)
				flagsCNZ[reg1][1] = 1;
			else
				flagsCNZ[reg1][1] = 0;
		}
		else
			registerFile[reg1] -= registerFile[reg2];		
	}
	else if ((registerFile[reg1] + registerFile[reg2] < registerFile[reg1] && flagsCNZ[reg1][1] == 0)
			|| (registerFile[reg1] + registerFile[reg2] > 0 && flagsCNZ[reg1][1] == 1))
	{
		registerFile[reg1] -= registerFile[reg1] + registerFile[reg2];
		flagsCNZ[reg1][0] = 1;
	}
	else
		registerFile[reg1] += registerFile[reg2];
		
	if (registerFile[reg1] == 0)
		flagsCNZ[reg1][2] = 1;
}

// SUB(int Register1, int Register2) - Subtract the value in Register2 from Register1. 
// If the result is negative set the negative flag on register1 to 1
template<class ItemType>
void RegisterSet<ItemType>::SUB(int reg1, int reg2)
{
	if (flagsCNZ[reg1][0] == 1 && flagsCNZ[reg2][0] == 1)
	{
		string message = "SUB() called with overflow";
		throw(IllegalArgumentException(message));
	}
	else if ((flagsCNZ[reg1][1] == 1 && flagsCNZ[reg2] == 1)
			|| (flagsCNZ[reg1][1] == 0 && flagsCNZ[reg2] == 0))
	{
		if (registerFile[reg1] - registerFile[reg2] < 0)
		{
			registerFile[reg1] = (registerFile[reg1] - registerFile[reg2]) * -1;
			if (flagsCNZ[reg1][1] == 0)
				flagsCNZ[reg1][1] = 1;
			else
				flagsCNZ[reg1][1] = 0;
		}
		else
			registerFile[reg1] -= registerFile[reg2];		
	}
	else if ((registerFile[reg1] + registerFile[reg2] < registerFile[reg1] && flagsCNZ[reg1][1] == 0)
			|| (registerFile[reg1] + registerFile[reg2] > registerFile[reg1] && flagsCNZ[reg1][1] == 1))
	{
		registerFile[reg1] -= registerFile[reg1] - registerFile[reg2];
		flagsCNZ[reg1][0] = 1;
	}
	else
		registerFile[reg1] -= registerFile[reg2];
		
	if (registerFile[reg1] == 0)
	{
		flagsCNZ[reg1][2] = 1;
		flagsCNZ[reg1][1] = 0;
	}
}

// MUL(int Register1, int Register2, int Register3) Multiply the value in
// Register1 by Register2, place any overflow in Register3 and set the carry
// flag on register1
template<class ItemType>
void RegisterSet<ItemType>::MUL(int reg1, int reg2, int reg3)
{
	if (flagsCNZ[reg1][0] == 1 && flagsCNZ[reg2][0] == 1)
	{
		string message = "MUL() called with overflow";
		throw(IllegalArgumentException(message));
	}
	else if (flagsCNZ[reg1][2] == 1 || flagsCNZ[reg2][2] == 1)
	{
		registerFile[reg1] = 0;
		flagsCNZ[reg1][2] = 1;
	}
	else if (registerFile[reg1] * registerFile[reg2] < 0 
			&& flagsCNZ[reg1][1] == flagsCNZ[reg2][1])
	{
		registerFile[reg3] = registerFile[reg1] - (registerFile[reg1] * registerFile[reg2]);
		registerFile[reg1] -= (registerFile[reg1] * registerFile[reg2]);
		flagsCNZ[reg1][0] = 1;
	}
	else if (registerFile[reg1] * registerFile[reg2] > 0 
			&& flagsCNZ[reg1][1] != flagsCNZ[reg2][1])
	{
		registerFile[reg3] = (registerFile[reg1] * registerFile[reg2]) - registerFile[reg1];
		registerFile[reg1] *= registerFile[reg2];
		flagsCNZ[reg1][0] = 1;
	}
	else
		registerFile[reg1] *= registerFile[reg2];
}

// DIV(int Register1, int Register2, int Register3) Divide the value in
// Register1 by Register2, place any remainder in Register3
template<class ItemType>
void RegisterSet<ItemType>::DIV(int reg1, int reg2, int reg3)
{
	if (flagsCNZ[reg2][2] == 1)
	{
		string message = "DIV() called with divide by zero";
		throw(IllegalArgumentException(message));
	}
	else if (registerFile[reg1] / registerFile[reg2] != (double)registerFile[reg1] / (double)registerFile[reg2])
	{
		registerFile[reg3] = registerFile[reg1] % registerFile[reg2];
		registerFile[reg1] /= registerFile[reg2];
	}
	else
		registerFile[reg1] /= registerFile[reg2];
}

// STO(int Register1, Register2) Retrieve the contents of Register2 and
// use its value as the address in memory where the contents of
// Register1 should be stored.
template<class ItemType>
void RegisterSet<ItemType>::STO(int reg1, int reg2)
{
	if (registerFile[reg2] >= 1 && registerFile[reg2] <= 9 
		&& registerFile[reg2] == (int)registerFile[reg2]
		&& reg1 >= 1 && reg1 <=9)
		registerFile[registerFile[reg2]] = registerFile[reg1];
	else
	{
		string message = "STO() called with an invalid register address";
		throw(IllegalArgumentException(message));
	}
}

template<class ItemType>
void RegisterSet<ItemType>::printBitsets()
{
	cout << "flagsCNZ[]: ";
	for (int i = 0; i < registerCount+1;i++)
	{
		cout << i << ": ";
		for (int j = 0; j < 3; j++)
			cout << flagsCNZ[i][j] << ", ";
		cout << "; ";
	}
	cout << endl;
}


int main() {
	cout << "Greetings, Earth" << endl;
	// RegisterSet myRegisters;
	RegisterSet<int>* myRegisters = new RegisterSet<int>();
	
	myRegisters->LD(1,42);
	myRegisters->LD(2,25);
	myRegisters->LD(3,21);
	myRegisters->LD(5,100);
	
	cout << "Register 1: " << myRegisters->get(1) << endl;
	cout << "Register 2: " << myRegisters->get(2) << endl;
	cout << "Register 3: " << myRegisters->get(3) << endl;
	cout << "Register 5: " << myRegisters->get(5) << endl;
	
	myRegisters->ADD(1,5);
	cout << "Register 1 + Register 5: " << myRegisters->get(1) << endl;
	myRegisters->SUB(2,3);
	cout << "Register 2 - Register 3: " << myRegisters->get(2) << endl;
	myRegisters->MUL(3,5,4);
	cout << "Register 3 * Register 5 (w/ Register 4): " << myRegisters->get(3) << " " 
		<< myRegisters->get(4) << endl;
	myRegisters->DIV(3,5,6);
	cout << "Register 3 / Register 5 (w/ Register 6): " << myRegisters->get(3) << " " 
		<< myRegisters->get(6) << endl;
	myRegisters->SUB(1,5);
	cout << "Register 1 - Register 5: " << myRegisters->get(1) << endl;
	myRegisters->DIV(5,1,6);
	cout << "Register 5 / Register 1 (w/ Register 6): " << myRegisters->get(5) << " " 
		<< myRegisters->get(6) << endl;
	
	


}
