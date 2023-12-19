//============================================================================
// Name        : Sort.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <raylib.h>
using namespace std;

class dataPoint{
	public:
	float x;
	float y;
	float angle;
	
	dataPoint(float x_,float y_,float angle_){
		x = x_;
		y = y_;
		angle = angle_;
	}

	string toString(){
		return "x: " + to_string(x) + " y: " + to_string(y) + " angle: " + to_string(angle);
	}

};

vector<dataPoint> getData(fstream csvfile);

vector<dataPoint> getData(string csvFile){
	ifstream dataFile;
	dataFile.open(csvFile);
	vector<dataPoint> allDataPoints;
	string line = "";
	
	while(getline(dataFile,line)){
		float x;
		float y;
		float angle;
		string tmpString;
		stringstream inputString(line);

		getline(inputString, tmpString, ',');
		x = atof(tmpString.c_str());

		tmpString = "";
		getline(inputString, tmpString, ',');
		y = atof(tmpString.c_str());

		tmpString = "";
		getline(inputString, tmpString, ',');
		angle = atof(tmpString.c_str());

		dataPoint point(x,y,angle);
		allDataPoints.push_back(point);
	}

	return allDataPoints;
}

int main(){
	// Initialization
	//--------------------------------------------------------------------------------------
	const int screenWidth = 800;
	const int screenHeight = 450;
	int xOFFSET = screenWidth / 2;
	int yOFFSET = screenHeight / 2;
	
	string CSV_FILE = "C:\\Users\\livid\\Documents\\GitHub\\MappingBot\\Visual_Display\\VSCode\\locationdata.csv";
	
	vector<dataPoint> allDataPoints = getData(CSV_FILE);

	cout<<allDataPoints[1].toString()<<endl;

	cout<<"Test"<<endl;
	return 0;

	InitWindow(screenWidth, screenHeight, "Mapping Bot Uno");
	SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
	    // Update
	    //----------------------------------------------------------------------------------
	    // TODO: Update your variables here
	    	
	    //----------------------------------------------------------------------------------

	    // Draw
	    //----------------------------------------------------------------------------------
	    BeginDrawing();
	    ClearBackground(RAYWHITE);
		DrawCircle(0 + xOFFSET, 0 + yOFFSET,1,RED);
	    DrawText("Mapping Bot", 190, 200, 20, LIGHTGRAY);
	    WaitTime(0.5);
		EndDrawing();
	        //----------------------------------------------------------------------------------
	    }

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}
