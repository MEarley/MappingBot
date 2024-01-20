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
#include "AStarAlgorithm.h"
using namespace std;

int xOFFSET = SCREENWIDTH / 2;
int yOFFSET = SCREENHEIGHT / 2;
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
	
	// Gets data from CSV file by recording the values from each line
	while(getline(dataFile,line)){
		float x;
		float y;
		float angle;
		string tmpString;
		stringstream inputString(line);

		// Obtain value of x
		getline(inputString, tmpString, ',');
		x = atof(tmpString.c_str());

		// Obtain value of y
		tmpString = "";
		getline(inputString, tmpString, ',');
		y = atof(tmpString.c_str());

		// Obtain value of angle
		tmpString = "";
		getline(inputString, tmpString, ',');
		angle = atof(tmpString.c_str());

		// Save data to an object and push onto a vector
		dataPoint point(x,y,angle);
		allDataPoints.push_back(point);
	}

	return allDataPoints;
}

void setWalls(set<Node*> &walls,vector<dataPoint> data,vector<vector<Node>> &mat){
	for(Node* segment : walls){
		segment->nType.name = VOID;
		segment->nType.color = BACKGROUND_COLOR;
	}
	walls.clear();
	
	for(dataPoint point : data){
		mat[point.x / 2][point.y / 2] = Node();
		walls
    }
}

int main(){
	// Initialization
	//--------------------------------------------------------------------------------------
	string CSV_FILE = "locationdata.csv";
	
	vector<dataPoint> allDataPoints = getData(CSV_FILE);

	cout<<allDataPoints[1].toString()<<endl;

	vector<vector<Node>> matrix((SCREENWIDTH / SCALE)+1,vector<Node>((SCREENHEIGHT / SCALE)+1));
	for(int w=0;w<(int)matrix.size();w++){
            for(int h=0;h<(int)matrix[w].size();h++){
                matrix[w][h].set_x(w);
                matrix[w][h].set_y(h);
                //std::cout<<w<<" "<<h<<endl;
                if(matrix[w][h].get_x() < 0 || matrix[w][h].get_y() < 0){
                    std::cout<<"break"<<endl;
                    break;
                }
            }
    }

	// Default start and end nodes
    Node* start = &matrix[matrix.size()/2][matrix[0].size()];
    Node* end = &matrix[matrix.size()/2][matrix[0].size()/2];
    
    start->nType.color = BLUE;
    end->nType.color = ORANGE;
	set<Node*> walls;

	setWalls(walls,allDataPoints);

	InitWindow(SCREENWIDTH, SCREENHEIGHT, "Mapping Bot Uno");
	SetTargetFPS(60);               // Set game to run at 60 frames-per-second

	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
	    // Update variables
	    //----------------------------------------------------------------------------------
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

			// Display Outline -----------
			if(i == 1)
				continue;
			DrawLine((allDataPoints[i-1].x*SCALE) + xOFFSET,yOFFSET - (allDataPoints[i-1].y*SCALE),(allDataPoints[i].x*SCALE) + xOFFSET,yOFFSET - (allDataPoints[i].y*SCALE),BLACK);
			// ---------------------------
		}

		// Center circle representing scan point
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
