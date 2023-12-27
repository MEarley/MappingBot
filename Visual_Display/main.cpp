//============================================================================
// Name        : Mapping Bot Uno
// Author      : Michael Earley
// Description : Uses th ELEGOO Car v4.0 and an ultrasonic sensor to draw
//			     out its surroundings in a 2D plane. Press F5 to run on VSCode IDE
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
int SCALE = 3;

class dataPoint{
	public:
	float x;
	float y;
	float angle;
	int size = 1;
	Color color = RED;
	
	dataPoint(float x_,float y_,float angle_){
		x = x_;
		y = y_;
		angle = angle_;
	}

	void displayCircle(){
		DrawCircle((x * SCALE) + xOFFSET,  yOFFSET - (y * SCALE),size,color);
	}

	void displayLine(){
		DrawLine(xOFFSET,yOFFSET,(x * SCALE) + xOFFSET,yOFFSET - (y * SCALE), color);
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
	
	
	string CSV_FILE = "locationdata.csv";
	
	vector<dataPoint> allDataPoints = getData(CSV_FILE);

	cout<<allDataPoints[1].toString()<<endl;

	InitWindow(SCREENWIDTH, SCREENHEIGHT, "Mapping Bot Uno");
	SetTargetFPS(60);               // Set game to run at 60 frames-per-second

	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
	    // Update
	    //----------------------------------------------------------------------------------
	    // TODO: Update your variables here
		if(IsKeyPressed(KEY_UP)){
			SCALE++;
		}
		else if(IsKeyPressed(KEY_DOWN) && SCALE > 1){
			SCALE--;
		}
	    	
	    //----------------------------------------------------------------------------------

	    // Draw
	    //----------------------------------------------------------------------------------
	    BeginDrawing();
	    ClearBackground(RAYWHITE);
		for(int i=1;i<((int)allDataPoints.size());i++){
			allDataPoints[i].displayLine();
			//allDataPoints[i].displayCircle();

			// Display Outline
			if(i == 1)
				continue;
			DrawLine((allDataPoints[i-1].x*SCALE) + xOFFSET,yOFFSET - (allDataPoints[i-1].y*SCALE),(allDataPoints[i].x*SCALE) + xOFFSET,yOFFSET - (allDataPoints[i].y*SCALE),BLACK);
		}

		DrawCircle(0 + xOFFSET, 0 + yOFFSET,6,BLACK);
		DrawCircle(0 + xOFFSET, 0 + yOFFSET,5,GREEN);
	    DrawText("Mapping Bot", 190, 200, 20, BLACK);
		DrawText(("Scale: " +  to_string(SCALE) + "X").c_str(), 0, 0, 20, LIGHTGRAY);
	    WaitTime(0.05);
		EndDrawing();
	        //----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}
