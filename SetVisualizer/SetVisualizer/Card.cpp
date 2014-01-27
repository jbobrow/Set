#include "Card.h"

Card::Card(int id)
{
	cardID = id;
	
	base = new poRectShape(40, 30, 5.f);
	addChild(base);
}

Card::~Card() 
{
}

void Card::update() 
{
}

void Card::draw()
{
}

Card* Card::findCardToCompleteSet(Card *c)
{
	Card *solution;
	solution = new Card();
	
	//-----------------------------------------
	//	
	//	[If] two cards share a property, it follows that the card to complete the set will have the same property.
	//	[Else] the third card needs to be not-the-same-property. 
	//	
	//-----------------------------------------
	
	// find the correct color
	if( _color == c->_color )
		solution->_color = _color;
	else {
		int combination = _color + c->_color;
		switch (combination) {
			case 1:		solution->setColor(2);	break;
			case 2:		solution->setColor(1);	break;
			case 3:		solution->setColor(0);	break;
			default:	break;
		}
	}
	
	// find the correct shape
	if( _shape == c->_shape )
		solution->_shape = _shape;
	else {
		int combination = _shape + c->_shape;
		switch (combination) {
			case 1:		solution->setShape(2);	break;
			case 2:		solution->setShape(1);	break;
			case 3:		solution->setShape(0);	break;
			default:	break;
		}
	}	
	
	// find the correct fill
	if( _fill == c->_fill )
		solution->_fill = _fill;
	else {
		int combination = _fill + c->_fill;
		switch (combination) {
			case 1:		solution->setFill(2);	break;
			case 2:		solution->setFill(1);	break;
			case 3:		solution->setFill(0);	break;
			default:	break;
		}
	}	
	
	// find the correct count
	if( _count == c->_count )
		solution->_count = _count;
	else {
		int combination = _count + c->_count;
		switch (combination) {
			case 1:		solution->setCount(2);	break;
			case 2:		solution->setCount(1);	break;
			case 3:		solution->setCount(0);	break;
			default:	break;
		}
	}	
	
	if( isCardEqual(c) )
		return NULL;
	else
		return solution;
}

bool Card::isCardEqual(Card *c)
{
	return(( _color == c->_color )
		   &&( _shape == c->_shape )
		   &&( _fill == c->_fill )
		   &&( _count == c->_count ));
}

void Card::setColor(int c)
{
	switch (c) {
		case 0:		_color = ITEM_COLOR_RED;	break;
		case 1:		_color = ITEM_COLOR_GREEN;	break;
		case 2:		_color = ITEM_COLOR_PURPLE;	break;
		default:	break;
	}
}

void Card::setShape(int s)
{
	switch (s) {
		case 0:		_shape = ITEM_SHAPE_OVAL;		break;
		case 1:		_shape = ITEM_SHAPE_DIAMOND;	break;
		case 2:		_shape = ITEM_SHAPE_SQUIGGLE;	break;
		default:	break;
	}
}

void Card::setFill(int f)
{
	switch (f) {
		case 0:		_fill = ITEM_FILL_OUTLINE;	break;
		case 1:		_fill = ITEM_FILL_SOLID;	break;
		case 2:		_fill = ITEM_FILL_STRIPED;	break;
		default:	break;
	}
}

void Card::setCount(int c)
{
	_count = c;
}

void Card::setVisuals()
{
	face = new poObject();
	addChild(face);
	
	for(int i=0; i<_count+1; i++){
		
		poRectShape *s = new poRectShape(10,20);
		
		switch (_color) {
			case ITEM_COLOR_RED:	s->fillColor = poColor::red;	break;
			case ITEM_COLOR_GREEN:	s->fillColor = poColor(.2f, .6f, .2f);	break;
			case ITEM_COLOR_PURPLE: s->fillColor = poColor(.4f, 0.f, 1.f); break;
		}
		
		switch (_shape) {
			case ITEM_SHAPE_OVAL:		s->placeTexture(poGetTexture("shapes/shape_oval_outline.png"), PO_TEX_FIT_EXACT); break;
			case ITEM_SHAPE_DIAMOND:	s->placeTexture(poGetTexture("shapes/shape_diamond_outline.png"), PO_TEX_FIT_EXACT); break;
			case ITEM_SHAPE_SQUIGGLE:	s->placeTexture(poGetTexture("shapes/shape_squiggle_outline.png"), PO_TEX_FIT_EXACT); break;
		}
		
		s->position.set( 5+10*i, 5, 0);
		
		addChild(s);
	}
}

void Card::changeState(int s)
{
	switch (s) {
		case 0:		state = CARD_STATE_IN_DECK;	alpha = 0.f;	break;
		case 1:		state = CARD_STATE_DEALT;	alpha = 1.f;	break;
		case 2:		state = CARD_STATE_DISCARD;	alpha = .2f;	break;			
		default:	break;
	};
}

void Card::printCard()
{
	printf("Card: %i, count: %i, color: %i, fill: %i, shape: %i\n", cardID, _count, _color, _fill, _shape); 
}

void Card::eventHandler(poEvent *event)
{
}

void Card::messageHandler(const std::string &msg, const poDictionary& dict) 
{
}
