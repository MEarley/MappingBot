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

#define SCREENWIDTH 800
#define	SCREENHEIGHT 450
#define xOFFSET SCREENWIDTH / 2
#define yOFFSET SCREENHEIGHT / 2
#define SCALE 2

class dataPoint{
	public:
	float x;
	float y;
	float angle;
	int size = 1;
	Color color = RED;
	
	dataPoint(float x_,float y_,float angle_){
		x = x_ * SCALE;
		y = y_ * SCALE;
		angle = angle_;
	}

	void displayCircle(){
		DrawCircle(x + xOFFSET,  yOFFSET - y,size,color);
	}

	void displayLine(){
		DrawLine(xOFFSET,yOFFSET,x + xOFFSET,yOFFSET - y, color);
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
	
	
	//string CSV_FILE = "C:\\Users\\livid\\Documents\\GitHub\\MappingBot\\Visual_Display\\VSCode\\locationdata.csv";
	string CSV_FILE = "C:\\Users\\Michael\\Documents\\GitHub\\MappingBot\\Visual_Display\\VSCode\\locationdata.csv";
	
	vector<dataPoint> allDataPoints = getData(CSV_FILE);

	cout<<allDataPoints[1].toString()<<endl;

	InitWindow(SCREENWIDTH, SCREENHEIGHT, "Mapping Bot Uno");
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
		for(int i=1;i<(allDataPoints.size());i++){
			allDataPoints[i].displayLine();
			//allDataPoints[i].displayCircle();

			// Display Outline
			if(i == 1)
				continue;
			DrawLine(allDataPoints[i-1].x + xOFFSET,yOFFSET - allDataPoints[i-1].y,allDataPoints[i].x + xOFFSET,yOFFSET - allDataPoints[i].y,BLACK);
		}

		DrawCircle(0 + xOFFSET, 0 + yOFFSET,5,GREEN);
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
