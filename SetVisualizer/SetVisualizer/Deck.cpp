#include "Deck.h"
#include <math.h>

Deck::Deck()
{
	bWithReplacement = false;
	bDrawHeatmap = false;
	
	numProperties = 4;
	numOptions = 3;
	
	poRandSeed();
	
	createCards();
	//printDeck();
	
	dealCards(12);
	updateNeededCards();
	printNeededRatios();
	
	addEvent(PO_KEY_DOWN_EVENT, this);
}

Deck::~Deck() 
{
}

void Deck::update() 
{
}

void Deck::draw()
{
	if(bDrawHeatmap){
		glBegin(GL_POINTS);
		for(int i=0; i<cards.size(); i++){
			glColor3f(255,i,0);//(float)i/cardsDealt.size(), (float)i/cardsDealt.size(), (float)i/cardsDealt.size());
			glVertex2f(cards[i]->position.x,cards[i]->position.y);
		}
		glEnd();
	}
}

void Deck::createCards()
{
	numCombinations = pow(numOptions,numProperties);
	
	Card *c;
	int count = 0;
	
	for( int i=0; i<3; i++ ){
		
		for( int ii=0; ii<3; ii++ ){
			
			for( int iii=0; iii<3; iii++ ){
				
				for( int iiii=0; iiii<3; iiii++ ){
					
					c = new Card(count++);
					c->setCount(i);
					c->setColor(ii);		
					c->setFill(iii);
					c->setShape(iiii);
					c->setVisuals();
					
					c->position.set( 50 * (iii*3 + iiii), 50 * (i*3 + ii), 0);
					c->changeState(CARD_STATE_IN_DECK);
					
					cards.push_back(c);
					addChild(cards.back());
				}
			}
		}
	}
}

void Deck::dealCards(int n)
{
	printf("------ Dealt Hand ---------\n");
	
	for (int i=0; i<n; i++) {
		Card *c1 = (Card *) cards[rand()%80];
		
		while((c1->state == CARD_STATE_DEALT) || (!bWithReplacement && c1->state == CARD_STATE_DISCARD)){
			c1 = (Card *) cards[rand()%80];
		}
		c1->changeState(CARD_STATE_DEALT);
		cardsDealt.push_back(c1);
		
		printf("Card: %i, count: %i, color: %i, fill: %i, shape: %i\n", c1->cardID, c1->_count, c1->_color, c1->_fill, c1->_shape);
	}
	printf("---------------------------\n");
}

void Deck::addCard( Card *c, std::vector<Card *> *cs)
{
}

void Deck::removeCard( Card *c, std::vector<Card *> *cs )
{
	for(int i=0; i<cs->size(); i++){
		
		Card *c1 = (Card *) cs->at(i);
		
		if(c->isCardEqual(c1)){
			c1->changeState(CARD_STATE_DISCARD);
			cs->erase(cs->begin()+i);
		}
	}
}

void Deck::removeAllCards()
{
	for( int i=0; i<cardsDealt.size(); i++){
		Card *c = (Card *) cardsDealt[i];
		c->changeState(CARD_STATE_IN_DECK);
	}
	cardsDealt.clear();
}

void Deck::findSet()
{
	for( int i=0; i<cardsDealt.size(); i++ ){
		
		for (int j=i+1; j<cardsDealt.size(); j++) {
			
			//printf("permutation: %i, %i\n", i, j);
			Card *c1 = (Card *) cardsDealt[i];
			Card *c2 = (Card *) cardsDealt[j];
			Card *c3 = c1->findCardToCompleteSet(c2);
			
			if(c3 != NULL){
				for( int k=0; k<cardsDealt.size(); k++ ){
					
					Card *s = (Card *) cardsDealt[k];
					
					if( c3->isCardEqual(s)){
						
						printf("--------removing found set---------\n");
						c1->printCard();
						c2->printCard();
						c3->printCard();
						printf("-----------------------------------\n");
						
						removeCard(c1, &cardsDealt);
						removeCard(c2, &cardsDealt);
						removeCard(c3, &cardsDealt);
						
						printHand();
					}
				}
			}
			else {
				printf("Null Card!!!!\n");
			}
		}
	}
}

void Deck::updateNeededCards()
{
	cardsNeeded.clear();
	
	if(bWithReplacement){
		for( int i=0; i<cardsDealt.size(); i++ ){
			
			for (int j=i; j<cardsDealt.size(); j++) {
			
				//printf("permutation: %i, %i\n", i, j);
				Card *c1 = (Card *) cardsDealt[i];
				Card *c2 = (Card *) cardsDealt[j];
				Card *c3 = c1->findCardToCompleteSet(c2);
				if(c3 != NULL){
					cardsNeeded.push_back(c3);
				}
			}
		}
	}else {
		for( int i=0; i<cardsDealt.size(); i++ ){
			
			for (int j= i; j<cardsDealt.size(); j++) {
				
				//printf("permutation: %i, %i\n", i, j);
				Card *c1 = (Card *) cardsDealt[i];
				Card *c2 = (Card *) cardsDealt[j];
				Card *c3 = c1->findCardToCompleteSet(c2);
				
				if(c3 != NULL){
					if(c3->state != CARD_STATE_DISCARD)
					cardsNeeded.push_back(c3);
				}
			}
		}
	}
}

void Deck::printNeededRatios()
{
	int one		= 0;
	int two		= 0;
	int three	= 0;
	
	int red		= 0;
	int green	= 0;
	int purple	= 0;
	
	int solid	= 0;
	int outlined = 0;
	int striped	= 0;
	
	int oval	= 0;
	int diamond	= 0;
	int squiggle = 0;
	
	for( int i=0; i<cardsNeeded.size(); i++ ){
		Card *c = (Card *)cardsNeeded[i];
		
		switch(c->_count){
			case 0:		one++;		break;
			case 1:		two++;		break;
			case 2:		three++;	break;
			default: break;
		}
		switch(c->_color){
			case 0:		red++;		break;
			case 1:		green++;	break;
			case 2:		purple++;	break;
			default: break;
		}
		switch(c->_fill){
			case 0:		solid++;	break;
			case 1:		outlined++;	break;
			case 2:		striped++;	break;
			default: break;
		}
		switch(c->_shape){
			case 0:		oval++;		break;
			case 1:		diamond++;	break;
			case 2:		squiggle++;	break;
			default: break;
		}
	}
	
	printf("-----------------------------\n");
	printf("count:  %i, %i, %i\n", one, two, three);
	printf("-----------------------------\n");
	printf("colors: %i, %i, %i\n", red, green, purple);
	printf("-----------------------------\n");
	printf("fill:   %i, %i, %i\n", outlined, solid, striped);
	printf("-----------------------------\n");
	printf("shape:  %i, %i, %i\n", oval, diamond, squiggle);
	printf("-----------------------------\n");
	
	// calculate needed ratios
	
	// calculate ideal card
}

void Deck::printHand()
{
	printf("-------- ||| Hand ||| ---------\n");
	for( int i=0; i<cardsDealt.size(); i++ ){
		Card *c = (Card *)cardsDealt[i];
		c->printCard();
	}
	printf("-------- |||      ||| ---------\n");
}

void Deck::printDeck()
{
	printf("-------- ::: Deck ::: ---------\n");
	for( int i=0; i<cards.size(); i++ ){
		Card *c = (Card *)cards[i];
		c->printCard();
	}
	printf("-------- :::      ::: ---------\n");

}

void Deck::eventHandler(poEvent *event)
{
	switch (event->keyChar) {
		case ' ':
			removeAllCards();
			dealCards(12);
			updateNeededCards();
			printNeededRatios();
			break;
			
		case 'f':
			findSet();
			break;
			
		case 'u':
			updateNeededCards();
			printNeededRatios();
			break;
			
		case 'd':
			dealCards(12-cardsDealt.size());
			break;
	
		case 'a':
			dealCards(3);
			break;
			
		case 'p':
			Card *c1 = (Card *) cards[rand()%80];
			Card *c2 = (Card *) cards[rand()%80];
			Card *c3 = c1->findCardToCompleteSet(c2);
			if(c3 == NULL)	return;
			printf("--------------------------------------\n");
			printf("the card match for %i, %i, %i, %i\n", c1->_count, c1->_color, c1->_fill, c1->_shape);
			printf("               and %i, %i, %i, %i\n", c2->_count, c2->_color, c2->_fill, c2->_shape);
			printf("               is  %i, %i, %i, %i\n", c3->_count, c3->_color, c3->_fill, c3->_shape);
			printf("--------------------------------------\n");
			break;
	}
}

void Deck::messageHandler(const std::string &msg, const poDictionary& dict) 
{
}
