//============================================================================
// Name        : Sort.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <raylib.h>
using namespace std;
int* getData(fstream csvfile);
int* getData(fstream csvFile){
	int *fileData;

	return fileData;
}

int main(){
	// Initialization
	//--------------------------------------------------------------------------------------
	const int screenWidth = 800;
	const int screenHeight = 450;
	int xOFFSET = screenWidth / 2;
	int yOFFSET = screenHeight / 2;

	// File pointer 
    fstream datafile; 
  
    // Opens an existing csv file
    datafile.open("locationdata.csv", ios::in); 

	// Read data and store data into an array


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
