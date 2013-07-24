#pragma once

/*	Created by Jonathan Bobrow on 2/1/13.
 *	Copyright 2013 Potion. All rights reserved.
 */

#include "poObject.h"
#include "poShapeBasics2D.h"
#include "poFBO.h"
#include "poGeometryMask.h"

class Navigator : public po::Object
{
public:
	Navigator(float w, float h);
	virtual ~Navigator();
	
	void addToCanvas(po::Object *o);
	void clearCanvas();
	void resizeCanvas(float w, float h);
	
	virtual void update();
	virtual void eventHandler(po::Event *event);
	virtual void messageHandler(const std::string &msg, const poDictionary& dict=po::Dictionary());
	
	po::RectShape		*canvas;
	po::FBO			*canvasFBO;
	
	po::RectShape		*map;
	
	po::RectShape		*miniMap;
	po::GeometryMask	*miniMapMask;
	po::RectShape		*highlight;
	po::RectShape		*highlightStroke;
	
	po::Point			grabPoint;
};