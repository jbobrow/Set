
/*
 *  ENUMS
 */
enum ItemColor{
  RED,
  GREEN,
  PURPLE
};

enum ItemShape{
  OVAL,
  DIAMOND,
  SQUIGGLE  
};

enum ItemFill{
  OUTLINE,
  SOLID,
  STRIPED
};

enum CardState{
  IN_DECK,
  DEALT,
  DISCARD
};

/*
 *  Class for a single Set card
 *
 */

class Card
{
  int      _id;
  
  ItemColor  _color;
  ItemShape  _shape;
  ItemFill  _fill;
  int      _count;
  
  CardState  state;
  
  // Constructor
  Card() {
    _id = -1;
  };

  Card(int id) {
    _id = id;
  };

  //
  Card findCardToCompleteSet(Card c)
  {
    Card solution;
    solution = new Card();
    
    //-----------------------------------------
    //  
    //  [If] two cards share a property, it follows that the card to complete the set will have the same property.
    //  [Else] the third card needs to be not-the-same-property. 
    //  
    //-----------------------------------------
    
    // find the correct color
    if( _color == c._color )
      solution._color = _color;
    else {
      int combination = _color.ordinal() + c._color.ordinal();
      switch (combination) {
        case 1:    solution.setColor(2);  break;
        case 2:    solution.setColor(1);  break;
        case 3:    solution.setColor(0);  break;
        default:  break;
      }
    }
    
    // find the correct shape
    if( _shape == c._shape )
      solution._shape = _shape;
    else {
      int combination = _shape.ordinal() + c._shape.ordinal();
      switch (combination) {
        case 1:    solution.setShape(2);  break;
        case 2:    solution.setShape(1);  break;
        case 3:    solution.setShape(0);  break;
        default:  break;
      }
    }  
    
    // find the correct fill
    if( _fill == c._fill )
      solution._fill = _fill;
    else {
      int combination = _fill.ordinal() + c._fill.ordinal();
      switch (combination) {
        case 1:    solution.setFill(2);  break;
        case 2:    solution.setFill(1);  break;
        case 3:    solution.setFill(0);  break;
        default:  break;
      }
    }  
    
    // find the correct count
    if( _count == c._count )
      solution._count = _count;
    else {
      int combination = _count + c._count;
      switch (combination) {
        case 1:    solution.setCount(2);  break;
        case 2:    solution.setCount(1);  break;
        case 3:    solution.setCount(0);  break;
        default:  break;
      }
    }  
    
    if( isCardEqual(c) )
      return null;
    else
      return solution;
  }
  
  //
  boolean isCardEqual(Card c)
  {
    return(( _color == c._color )
         &&( _shape == c._shape )
         &&( _fill == c._fill )
         &&( _count == c._count ));
  }
  
  //
  void setColor(int c)
  {
    switch (c) {
      case 0:    _color = ItemColor.RED;  break;
      case 1:    _color = ItemColor.GREEN;  break;
      case 2:    _color = ItemColor.PURPLE;  break;
      default:  break;
    }
  }
  
  //
  void setShape(int s)
  {
    switch (s) {
      case 0:    _shape = ItemShape.OVAL;    break;
      case 1:    _shape = ItemShape.DIAMOND;  break;
      case 2:    _shape = ItemShape.SQUIGGLE;  break;
      default:  break;
    }
  }
  
  //
  void setFill(int f)
  {
    switch (f) {
      case 0:    _fill = ItemFill.OUTLINE;  break;
      case 1:    _fill = ItemFill.SOLID;  break;
      case 2:    _fill = ItemFill.STRIPED;  break;
      default:  break;
    }
  }
  
  //
  void setCount(int c)
  {
    _count = c;
  }
  
  void changeState(int s)
  {
    switch (s) {
      case 0:    state = CardState.IN_DECK;  break;
      case 1:    state = CardState.DEALT;    break;
      case 2:    state = CardState.DISCARD;  break;      
      default:  break;
    };
  }
  
  void printCard()
  {
    println("Card: " + _id + ", count: " + _count + ", color: " + _color + ", fill: " + _fill + ", shape: " + _shape); 
  }

};