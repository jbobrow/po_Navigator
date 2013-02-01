/////////////////////////////////////////
//
// pocode application configuration
//
/////////////////////////////////////////

#include "poHelpers.h"
#include "poApplication.h"
#include "NavigatorApp.h"

poObject *createObjectForID(uint uid) {
	return new NavigatorApp();
}

void setupApplication() {
	lookUpAndSetPath("resources");
	applicationCreateWindow(0, WINDOW_TYPE_NORMAL, "Navigator", 100, 100, 800, 600);
}

void cleanupApplication() {
}