#pragma once

/*	Created by Jonathan Bobrow on 2/1/13.
 *	Copyright 2013 Potion. All rights reserved.
 */

#include "poObject.h"
#include "poShapeBasics2D.h"
#include "poFBO.h"
#include "poGeometryMask.h"

class Navigator : public poObject
{
public:
	Navigator(float w, float h);
	virtual ~Navigator();
	
	void addToCanvas(poObject *o);
	void clearCanvas();
	void resizeCanvas(float w, float h);
	
	virtual void update();
	virtual void eventHandler(poEvent *event);
	virtual void messageHandler(const std::string &msg, const poDictionary& dict=poDictionary());
	
	poRectShape		*canvas;
	poFBO			*canvasFBO;
	
	poRectShape		*map;
	
	poRectShape		*miniMap;
	poGeometryMask	*miniMapMask;
	poRectShape		*highlight;
	poRectShape		*highlightStroke;
	
	poPoint			grabPoint;
};