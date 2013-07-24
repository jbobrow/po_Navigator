/*	Created by Jonathan Bobrow on 2/1/13.
 *	Copyright 2013 __MyCompanyName__. All rights reserved.
 */

#include "NavigatorApp.h"
#include "poApplication.h"
#include "poCamera.h"
#include "poTextBox.h"


// APP CONSTRUCTOR. Create all objects here.
NavigatorApp::NavigatorApp() {
	addModifier(new po::Camera2D(poColor::black));
	
	// let's create a canvas with a navigation
	nav = new Navigator(1920,1200);
	addChild(nav);
	
	// how about we draw something to this canvas
	nav->addToCanvas(new po::RectShape("ghostly_02.jpg"));		// image credit to ghostly international
	
	// directions displayed on screen
	po::TextBox	*tb = new po::TextBox(getWindowWidth());
	tb->setAlignment(PO_ALIGN_BOTTOM_LEFT);
	tb->position.set(0,getWindowHeight(),0);
	tb->setText("press or hold any key to add some dots");
	tb->setPadding(20, 0, 10, 5);
	tb->fillEnabled = true;
	tb->fillColor = poColor(0,0,0,.8);
	tb->setTextSize(24);
	tb->textColor = poColor::ltGrey;
	tb->doLayout();
	addChild(tb);
	
	// let's add some stuff on key presses
	addEvent(po::KEY_DOWN_EVENT, this);
}

// APP DESTRUCTOR. Delete all objects here.
NavigatorApp::~NavigatorApp() {
}

// UPDATE. Called once per frame. Animate objects here.
void NavigatorApp::update() {
	
}

// DRAW. Called once per frame. Draw objects here.
void NavigatorApp::draw() {
	
}

// EVENT HANDLER. Called when events happen. Respond to events here.
void NavigatorApp::eventHandler(po::Event *event) {
	
	if( event->type == po::KEY_DOWN_EVENT ) {		// so you pressed a key
		
		// How about a dot of a random diameter
		float diameter = po::Rand(20,100);
		po::OvalShape *shape = new po::OvalShape(diameter,diameter,50);
		shape->position.set(po::Rand(0, nav->getWidth()), po::Rand(0, nav->getHeight()), 0);
		shape->fillColor = blendColors(po::Color::orange, po::Color::random(), .8);
		
		// Don't forget to add it to the canvas
		nav->addToCanvas(shape);
		
		
		// What the heck, let's make this dots animate
		shape->scaleTween
		.set(po::Point(2.f,2.f,1))
			.setDuration(1.f)
			.setRepeat(PO_TWEEN_REPEAT_PINGPONG)
			.setTweenFunction(PO_TWEEN_SINUS_INOUT_FUNC)
			.start();
		// Too much? Probably.
	}
}

// MESSAGE HANDLER. Called from within the app. Use for message passing.
void NavigatorApp::messageHandler(const std::string &msg, const po::Dictionary& dict) {
	
}
