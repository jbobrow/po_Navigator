#include "Navigator.h"
#include "poApplication.h"

Navigator::Navigator(float w, float h)
{
	// Draw anything to this canvas and it will be shown on the map and mini map
	canvas = new poRectShape(w, h);
	addChild(canvas);
	
	canvasFBO = new poFBO(canvas->getWidth(), canvas->getHeight(), poFBOConfig().setNumMultisamples(4));
	canvas->addModifier(canvasFBO);
	
	// This map will be a dragable and visible version of the canvas (remember the canvas is not drawn, just used for the fbo)
	map = new poRectShape(canvas->getWidth(), canvas->getHeight());
	map->placeTexture(canvasFBO->getColorTexture());
	addChild(map);
	
	// This mini map will show exactly what is on the larger map
	miniMap = new poRectShape( 200, 200 * canvas->getHeight()/canvas->getWidth());
	miniMap->setAlignment(PO_ALIGN_TOP_RIGHT);
	miniMap->position.set(getWindowWidth()-20, 20, 0);
	miniMap->generateStroke(2).strokeColor = poColor::black;
	miniMap->placeTexture(canvasFBO->getColorTexture(), PO_TEX_FIT_EXACT);
	addChild(miniMap);
	
	// Mask the miniMap, because I am goint to dim the map with a really large stroked rectangle
	miniMapMask = new poGeometryMask(new poRectShape(miniMap->getWidth(), miniMap->getHeight()));
	miniMap->addModifier(miniMapMask);
	
	// Calculate highlight size
	float _w = miniMap->getWidth() * getWindowWidth() / canvas->getWidth();
	float _h = miniMap->getHeight() * getWindowHeight() / canvas->getHeight();
	
	// Create a highlight on the mini map by darkening the area around our highlight
	// note, you could just put a red box, but I think this is a nicer effect
	highlight = new poRectShape(_w, _h);
	highlight->fillEnabled = false;
	highlight->generateStroke(200, PO_STROKE_PLACE_OUTSIDE).strokeColor = poColor(0,0,0,.5);
	highlight->position.set(0,0,0);
	miniMap->addChild(highlight);
	
	// Just for emphasis, let's put a red stroke there too :)
	poRectShape *highlightStroke = new poRectShape(_w, _h);
	highlightStroke->fillEnabled = false;
	highlightStroke->generateStroke(2, PO_STROKE_PLACE_OUTSIDE).strokeColor = poColor::red;
	highlight->addChild(highlightStroke);
	
	// add our drag events to the map
	map->addEvent(PO_MOUSE_DOWN_INSIDE_EVENT, this);
	map->addEvent(PO_MOUSE_DRAG_INSIDE_EVENT, this);
	
	// add our drag events to the highlight
	highlight->addEvent(PO_MOUSE_DOWN_INSIDE_EVENT, this);
	highlight->addEvent(PO_MOUSE_DRAG_INSIDE_EVENT, this);
}

Navigator::~Navigator()
{
}

void Navigator::addToCanvas(poObject *o)
{
	canvas->addChild(o);
}

void Navigator::clearCanvas()
{
	canvas->removeAllChildren();
}

void Navigator::resizeCanvas(float w, float h)
{
	// resize the canvas, map, and minimap
	canvas->reshape(w, h);
	map->reshape(w, h);
	miniMap->reshape(200, 200 * canvas->getHeight()/canvas->getWidth());
	
	// resize highlight
	float _w = miniMap->getWidth() * getWindowWidth() / canvas->getWidth();
	float _h = miniMap->getHeight() * getWindowHeight() / canvas->getHeight();
	highlight->reshape(_w, _h);
	highlightStroke->reshape(_w, _h);
}

void Navigator::update()
{
}

void Navigator::eventHandler(poEvent *event)
{
	if( event->source == map ){							// oh, so you clicked on the map
		
		switch ( event->type ){
				
			case PO_MOUSE_DOWN_INSIDE_EVENT:			// I'm gonna remember where you grabbed hold
				map->positionTween.stop();				// and stop smoothing any previous movement
				grabPoint = event->globalPosition - map->position;
				break;
				
			case PO_MOUSE_DRAG_INSIDE_EVENT:			// come with me, right this way
				map->position = event->globalPosition - grabPoint;
				highlight->position = -map->position * miniMap->getWidth()/map->getWidth();
				break;
				
			default: break;
		}
	}
	
	else if( event->source == highlight ){				// ah, you noticed this navigates, too!
		
		switch ( event->type ){
				
			case PO_MOUSE_DOWN_INSIDE_EVENT:			// yeah, let's remember where we started
				grabPoint = event->globalPosition - miniMap->position - highlight->position;
				break;
				
			case PO_MOUSE_DRAG_INSIDE_EVENT:			// since you suck at smoothly draggin this, I'll help you out :)
				highlight->position = event->globalPosition - miniMap->position - grabPoint;
				map->positionTween
					.set(-highlight->position * map->getWidth()/miniMap->getWidth())
					.setTweenFunction(PO_TWEEN_GOTO_FUNC)
					.setExtraValues(.9)
					.start();
				break;
				
			default: break;
		}
	}
}

void Navigator::messageHandler(const std::string &msg, const poDictionary& dict) 
{
}
