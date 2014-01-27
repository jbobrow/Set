#pragma once

/*	Created by Jonathan Bobrow on 6/12/12.
 *	Copyright 2012 __MyCompanyName__. All rights reserved.
 */

#include "poObject.h"
#include "poSimpleDrawing.h"
#include "poShapeBasics2D.h"

//------------------------------
//		Properties
//------------------------------

enum ItemColor{
	ITEM_COLOR_RED = 0,
	ITEM_COLOR_GREEN = 1,
	ITEM_COLOR_PURPLE = 2
};

enum ItemShape{
	ITEM_SHAPE_OVAL = 0,
	ITEM_SHAPE_DIAMOND = 1,
	ITEM_SHAPE_SQUIGGLE = 2	
};

enum ItemFill{
	ITEM_FILL_OUTLINE = 0,
	ITEM_FILL_SOLID = 1,
	ITEM_FILL_STRIPED = 2
};

//------------------------------

enum CardState{
	CARD_STATE_IN_DECK = 0,
	CARD_STATE_DEALT = 1,
	CARD_STATE_DISCARD = 2
};

//------------------------------

class Card : public poObject
{
public:
	Card(int id = -1);
	virtual ~Card();
	
	virtual void update();
	virtual void draw();
	virtual void eventHandler(poEvent *event);
	virtual void messageHandler(const std::string &msg, const poDictionary& dict=poDictionary());
	
	void setColor(int c);
	void setShape(int s);
	void setFill(int f);
	void setCount(int c);
	void setVisuals();
	
	void changeState(int s);
	
	Card* findCardToCompleteSet(Card *c);
	bool  isCardEqual(Card *c);
	
	void printCard();

	int			cardID;
	
	ItemColor	_color;
	ItemShape	_shape;
	ItemFill	_fill;
	int			_count;
	
	CardState	state;
	
	poRectShape	*base;
	poObject	*face;
};