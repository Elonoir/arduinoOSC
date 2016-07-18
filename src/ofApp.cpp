#include "ofApp.h"


//-----SETUP---------------------------------------------------------
void ofApp::setup() {

	//openFrameworks
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofBackground(255, 0, 130);

	//OSC
	send.setup(HOST, PORT);

	//ARDUINO
	ard.connect("COM7", 57600);

	// listen for EInitialized notification. this indicates that
	// the arduino is ready to call setupArduino()
	ofAddListener(ard.EInitialized, this, &ofApp::setupArduino);
	bSetupArduino = false;	// flag so we setup arduino when its ready, you don't need to touch this :)
}

void ofApp::setupArduino(const int & version) {

	// remove listener
	ofRemoveListener(ard.EInitialized, this, &ofApp::setupArduino);

	// it is now safe to send commands to the Arduino
	bSetupArduino = true;

	// set pins D2 to digital input
	ard.sendDigitalPinMode(12, ARD_INPUT);

	// set pin A0 to analog input
	ard.sendAnalogPinReporting(0, ARD_ANALOG);
	ard.sendAnalogPinReporting(1, ARD_ANALOG);
	ard.sendAnalogPinReporting(2, ARD_ANALOG);
	ard.sendAnalogPinReporting(3, ARD_ANALOG);
	ard.sendAnalogPinReporting(4, ARD_ANALOG);
	ard.sendAnalogPinReporting(5, ARD_ANALOG);
}

//-------UPDATE-------------------------------------------------------
void ofApp::update() {

	updateArduino();

	ofxOscMessage msg;
	msg.setAddress("/wek/inputs");
		msg.addFloatArg(ard.getAnalog(0));
		msg.addFloatArg(ard.getAnalog(1));
		msg.addFloatArg(ard.getAnalog(2));
		msg.addFloatArg(ard.getAnalog(3));
		msg.addFloatArg(ard.getAnalog(4));
		msg.addFloatArg(ard.getAnalog(5));
	send.sendMessage(msg);

}

void ofApp::updateArduino() {

	// update the arduino, get any data or messages. // Required
	ard.update();

	if (bSetupArduino) {
		//Do somethings on the arduino get or update data
		cout << "analog pin: stable " << ofToString(0) << " = " << ofToString(ard.getAnalog(0)) << endl;
		cout << "analog pin: stable " << ofToString(1) << " = " << ofToString(ard.getAnalog(1)) << endl;
		cout << "analog pin: stable " << ofToString(2) << " = " << ofToString(ard.getAnalog(2)) << endl;
		cout << "analog pin: stable " << ofToString(3) << " = " << ofToString(ard.getAnalog(3)) << endl;
		cout << "analog pin: stable " << ofToString(4) << " = " << ofToString(ard.getAnalog(4)) << endl;
		cout << "analog pin: stable " << ofToString(5) << " = " << ofToString(ard.getAnalog(5)) << endl;
	}
	else {
		cout << "arduino not ready...\n" << endl;
	}

}

//--------DRAW------------------------------------------------------
void ofApp::draw() {
	if (!bSetupArduino) {
	}
	else {

	}
}