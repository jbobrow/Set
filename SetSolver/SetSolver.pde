/*
 *  Recreation of Set Solver coded in Pocode @ Potion by Jonathan Bobrow in 2012
 *
 *
 *  by Jonathan Bobrow
 *  11/30/2016
 */

Deck deck;

void setup() {
  deck = new Deck();
}

void draw() {
  
}

void keyPressed() {
  switch (key) {
      case ' ':
        deck.removeAllCards();
        deck.dealCards(12);
        deck.updateNeededCards();
        deck.printNeededRatios();
        break;
        
      case 'f':
        deck.findSet();
        break;
        
      case 'u':
        deck.updateNeededCards();
        deck.printNeededRatios();
        break;
        
      case 'd':
        deck.dealCards(12-deck.cardsDealt.size());
        break;
    
      case 'a':
        deck.dealCards(3);
        break;
        
      case 'p':
        Card c1 = deck.cards.get(int(random(0,80)));
        Card c2 = deck.cards.get(int(random(0,80)));
        Card c3 = c1.findCardToCompleteSet(c2);
        if(c3 == null)  return;
        println("--------------------------------------\n");
        println("the card match for %i, %i, %i, %i\n", c1._count, c1._color, c1._fill, c1._shape);
        println("               and %i, %i, %i, %i\n", c2._count, c2._color, c2._fill, c2._shape);
        println("               is  %i, %i, %i, %i\n", c3._count, c3._color, c3._fill, c3._shape);
        println("--------------------------------------\n");
        break;
    }
}