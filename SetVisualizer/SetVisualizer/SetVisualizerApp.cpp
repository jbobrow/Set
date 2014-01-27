/*	Created by Jonathan Bobrow on 6/12/12.
 *	Copyright 2012 __MyCompanyName__. All rights reserved.
 */

#include "SetVisualizerApp.h"
#include "poApplication.h"
#include "poCamera.h"


// APP CONSTRUCTOR. Create all objects here.
SetVisualizerApp::SetVisualizerApp() {
	addModifier(new poCamera2D(poColor::black));
	
	setDeck = new Deck();
	setDeck->position.set(75, 75, 0);
	addChild(setDeck);
}

// APP DESTRUCTOR. Delete all objects here.
SetVisualizerApp::~SetVisualizerApp() {
}

// UPDATE. Called once per frame. Animate objects here.
void SetVisualizerApp::update() {
	
}

// DRAW. Called once per frame. Draw objects here.
void SetVisualizerApp::draw() {
	
}

// EVENT HANDLER. Called when events happen. Respond to events here.
void SetVisualizerApp::eventHandler(poEvent *event) {
	
}

// MESSAGE HANDLER. Called from within the app. Use for message passing.
void SetVisualizerApp::messageHandler(const std::string &msg, const poDictionary& dict) {
	
}
