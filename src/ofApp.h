#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofEvents.h"

#define HOST "localhost"
#define PORT 6448

class ofApp : public ofBaseApp{

public:

	void setup();
	void update();
	void draw();

	ofxOscSender send;

	ofArduino	ard;
	bool		bSetupArduino;			// flag variable for setting up arduino once

private:
    
    void setupArduino(const int & version);
	void updateArduino();
};