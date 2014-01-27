#pragma once

/*	Created by Jonathan Bobrow on 6/12/12.
 *	Copyright 2012 __MyCompanyName__. All rights reserved.
 */

/*	About the Set Visualizer
 *	
 *	The aim of this project is to show that there is possible strategy, and what a single
 *	player should be looking for at any given moment in the game.
 *
 *	Technical:
 *	The ideal setup is a camera and projector pair to recognize cards and augment the playing field
 *
 *	Assumption:
 *	Properties as recognizeable by the eye is order of easiest to hardest:	count, color, fill, shape
 */
 
#include "poObject.h"
#include "Card.h"

class Deck : public poObject
{
public:
	Deck();
	virtual ~Deck();
	
	virtual void update();
	virtual void draw();
	virtual void eventHandler(poEvent *event);
	virtual void messageHandler(const std::string &msg, const poDictionary& dict=poDictionary());
	
	void createCards();
	void dealCards( int n );
	
	void addCard( Card *c, std::vector<Card *> *cs );
	void removeCard( Card *c, std::vector<Card *> *cs );
	void removeAllCards();
	
	void findSet();
//	void highlightSet( std::vector<Card *> *cs );
	
	void updateNeededCards();
	void printNeededRatios();
	
	void printHand();
	void printDeck();
	
	std::vector<Card *> cards;
	std::vector<Card *> cardsDealt;
	std::vector<Card *> cardsNeeded;
	
	int numCombinations;
	int numProperties;
	int numOptions;
	
	bool bWithReplacement;
	bool bDrawHeatmap;
};