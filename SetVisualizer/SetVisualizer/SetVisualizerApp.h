/*	Created by Jonathan Bobrow on 6/12/12.
 *	Copyright 2012 __MyCompanyName__. All rights reserved.
 */

#include "poObject.h"
#include "Deck.h"

class SetVisualizerApp : public poObject {
public:
	SetVisualizerApp();
	virtual ~SetVisualizerApp();
	
    virtual void update();
    
    virtual void draw();
	
    virtual void eventHandler(poEvent *event);
	
    virtual void messageHandler(const std::string &msg, const poDictionary& dict=poDictionary());
	
	Deck* setDeck;
};

