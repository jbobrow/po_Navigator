/*	Created by Jonathan Bobrow on 2/1/13.
 *	Copyright 2013 __MyCompanyName__. All rights reserved.
 */

#include "poObject.h"
#include "Navigator.h"

class NavigatorApp : public po::Object {
public:
	NavigatorApp();
	virtual ~NavigatorApp();
	
    virtual void update();
    
    virtual void draw();
	
    virtual void eventHandler(poEvent *event);
	
    virtual void messageHandler(const std::string &msg, const poDictionary& dict=po::Dictionary());
	
	Navigator	*nav;
};

