//============================================================================
// Name        : MappingBot.cpp
// Author      : Michael Earley
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <tchar.h>
#include "SerialClass.h"
#include <string>
using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	printf("Welcome to the serial test app!\n\n");

	Serial* SP = new Serial("COM5");    // adjust as needed

	if (SP->IsConnected())
		printf("We're connected");

	char incomingData[256] = "";			// don't forget to pre-allocate memory
	//printf("%s\n",incomingData);
	int dataLength = 255;
	int readResult = 0;

	while(SP->IsConnected())
	{
		readResult = SP->ReadData(incomingData,dataLength);
		// printf("Bytes read: (0 means no data available) %i\n",readResult);
                incomingData[readResult] = 0;

        	printf("%s",incomingData);

		Sleep(500);
	}
	return 0;
}

/*
int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
    string s = "Hi";
    cout<< s<< endl;
	return 0;
}
*/