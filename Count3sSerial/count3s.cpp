// read in from binary file
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

int main()
{
	float SEARCH = 3.00;
	float threes[4]; // holds a 32 bit float
	float zeroCheck; // test for valid floating point numbers
	int num3s = 0; // counter 
	
	ifstream data;
	data.open("threesData.bin", ios::binary);

	if (data.is_open())
	{
		cout << "open\n";
		while (!data.eof())  // continues until end of file
		{
			data.read (reinterpret_cast<char *>(threes), 4);
			for (int i=0; i<4; i++)
			{
				zeroCheck = fabs(threes[i] - SEARCH); // store float absolute value difference
			
				if (zeroCheck < 0.001)
					num3s++;
			}
		}
		cout << num3s << " occurrences of 3.00 found" << endl;
		data.close();
	}
	else
		cout << "failed to open file\n";
	
}