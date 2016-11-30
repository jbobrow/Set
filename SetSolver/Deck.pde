/*
 * Class for a Deck
 *
 */
 
class Deck {
  
  ArrayList<Card> cards;
  ArrayList<Card> cardsDealt;
  ArrayList<Card> cardsNeeded;
  
  int numCombinations;
  int numProperties;
  int numOptions;
  
  boolean bWithReplacement;
  boolean bDrawHeatmap;
  
  Deck()
  {
    bWithReplacement = false;
    bDrawHeatmap = false;
    
    numProperties = 4;
    numOptions = 3;
    
    randomSeed(1);
    
    cards = new ArrayList<Card>();
    cardsDealt = new ArrayList<Card>();
    cardsNeeded = new ArrayList<Card>();

    createCards();
    //printDeck();
        
    dealCards(12);
    updateNeededCards();
    printNeededRatios();
  }
  
  void display()
  {
    //if(bDrawHeatmap){
    //  glBegin(GL_POINTS);
    //  for(int i=0; i<cards.size(); i++){
    //    glColor3f(255,i,0);//(float)i/cardsDealt.size(), (float)i/cardsDealt.size(), (float)i/cardsDealt.size());
    //    glVertex2f(cards[i].position.x,cards[i].position.y);
    //  }
    //  glEnd();
    //}
  }
  
  void createCards()
  {
    numCombinations = int(pow(numOptions,numProperties));
    
    Card c;
    int count = 0;
    
    for( int i=0; i<3; i++ ){
      
      for( int ii=0; ii<3; ii++ ){
        
        for( int iii=0; iii<3; iii++ ){
          
          for( int iiii=0; iiii<3; iiii++ ){
            
            c = new Card(count++);
            c.setCount(i);
            c.setColor(ii);    
            c.setFill(iii);
            c.setShape(iiii);
            //c.setVisuals();
            
            //c.position.set( 50  (iii3 + iiii), 50  (i3 + ii), 0);
            c.changeState(CardState.IN_DECK.ordinal());
            
            cards.add(c);
          }
        }
      }
    }
  }
  
  void dealCards(int n)
  {
    println("------ Dealt Hand ---------");
    
    for (int i=0; i<n; i++) {
      Card c1 = cards.get(int(random(0,80)));
      
      while((c1.state == CardState.DEALT) || (!bWithReplacement && c1.state == CardState.DISCARD)){
        c1 = (Card) cards.get(int(random(0,80)));
      }
      c1.changeState(CardState.DEALT.ordinal());
      cardsDealt.add(c1);
      
      println("Card: " + c1._id + ", count: " + c1._count + ", color: " + c1._color + ", fill: " + c1._fill + ", shape: " + c1._shape); 
    }
    println("---------------------------");
  }
  
  void addCard( Card c, ArrayList<Card> cs)
  {
  }
  
  void removeCard( Card c, ArrayList<Card> cs )
  {
    for(int i=0; i<cs.size(); i++){
      
      Card c1 = (Card) cs.get(i);
      
      if(c.isCardEqual(c1)){
        c1.changeState(CardState.DISCARD.ordinal());
        cs.remove(i);
      }
    }
  }
  
  void removeAllCards()
  {
    for( int i=0; i<cardsDealt.size(); i++){
      Card c = (Card) cardsDealt.get(i);
      c.changeState(CardState.IN_DECK.ordinal());
    }
    cardsDealt.clear();
  }
  
  void findSet()
  {
    for( int i=0; i<cardsDealt.size(); i++ ){
      
      for (int j=i+1; j<cardsDealt.size(); j++) {
        
        //printf("permutation: %i, %i\n", i, j);
        Card c1 = (Card) cardsDealt.get(i);
        Card c2 = (Card) cardsDealt.get(j);
        Card c3 = c1.findCardToCompleteSet(c2);
        
        if(c3 != null){
          for( int k=0; k<cardsDealt.size(); k++ ){
            
            Card s = (Card) cardsDealt.get(k);
            
            if( c3.isCardEqual(s)){
              
              println("--------removing found set---------");
              c1.printCard();
              c2.printCard();
              c3.printCard();
              println("-----------------------------------");
              
              removeCard(c1, cardsDealt);
              removeCard(c2, cardsDealt);
              removeCard(c3, cardsDealt);
              
              printHand();
            }
          }
        }
        else {
          println("Null Card!!!!");
        }
      }
    }
  }
  
  void updateNeededCards()
  {
    cardsNeeded.clear();
    
    if(bWithReplacement){
      for( int i=0; i<cardsDealt.size(); i++ ){
        
        for (int j=i; j<cardsDealt.size(); j++) {
        
          //printf("permutation: %i, %i\n", i, j);
          Card c1 = (Card ) cardsDealt.get(i);
          Card c2 = (Card ) cardsDealt.get(j);
          Card c3 = c1.findCardToCompleteSet(c2);
          if(c3 != null){
            cardsNeeded.add(c3);
          }
        }
      }
    }else {
      for( int i=0; i<cardsDealt.size(); i++ ){
        
        for (int j= i; j<cardsDealt.size(); j++) {
          
          //printf("permutation: %i, %i\n", i, j);
          Card c1 = (Card ) cardsDealt.get(i);
          Card c2 = (Card ) cardsDealt.get(j);
          Card c3 = c1.findCardToCompleteSet(c2);
          
          if(c3 != null){
            if(c3.state != CardState.DISCARD)
            cardsNeeded.add(c3);
          }
        }
      }
    }
  }
  
  void printNeededRatios()
  {
    int one    = 0;
    int two    = 0;
    int three  = 0;
    
    int red    = 0;
    int green  = 0;
    int purple  = 0;
    
    int solid  = 0;
    int outlined = 0;
    int striped  = 0;
    
    int oval  = 0;
    int diamond  = 0;
    int squiggle = 0;
    
    for( int i=0; i<cardsNeeded.size(); i++ ){
      Card c = (Card )cardsNeeded.get(i);
      
      switch(c._count){
        case 0:    one++;    break;
        case 1:    two++;    break;
        case 2:    three++;  break;
        default: break;
      }
      switch(c._color){
        case RED:      red++;     break;
        case GREEN:    green++;   break;
        case PURPLE:   purple++;  break;
        default: break;
      }
      switch(c._fill){
        case SOLID:      solid++;     break;
        case OUTLINE:    outlined++;  break;
        case STRIPED:    striped++;   break;
        default: break;
      }
      switch(c._shape){
        case OVAL:       oval++;     break;
        case DIAMOND:    diamond++;  break;
        case SQUIGGLE:   squiggle++; break;
        default: break;
      }
    }
    
    println("-----------------------------");
    println("count:   " + one + ", " + two + ", " + three);
    println("-----------------------------");
    println("colors:  " + red + ", " + green + ", " + purple);
    println("-----------------------------");
    println("fill:    " + outlined + ", " + solid + ", " + striped);
    println("-----------------------------");
    println("shape:   " + oval + ", " + diamond + ", " + squiggle);
    println("-----------------------------");
    
    // calculate needed ratios
    
    // calculate ideal card
  }
  
  void printHand()
  {
    println("-------- ||| Hand ||| ---------");
    for( int i=0; i<cardsDealt.size(); i++ ){
      Card c = (Card )cardsDealt.get(i);
      c.printCard();
    }
    println("-------- |||      ||| ---------");
  }
  
  void printDeck()
  {
    println("-------- ::: Deck ::: ---------");
    for( int i=0; i<cards.size(); i++ ){
      Card c = (Card )cards.get(i);
      c.printCard();
    }
    println("-------- :::      ::: ---------");
  
  }
};