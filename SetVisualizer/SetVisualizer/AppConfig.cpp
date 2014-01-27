/////////////////////////////////////////
//
// pocode application configuration
//
/////////////////////////////////////////


#include "poApplication.h"
#include "SetVisualizerApp.h"

poObject *createObjectForID(uint uid) {
	return new SetVisualizerApp();
}

void setupApplication() {
	lookUpAndSetPath("resources");
	applicationCreateWindow(0, WINDOW_TYPE_NORMAL, "SetVisualizer", 100, 100, 600, 600);
}

void cleanupApplication() {
}