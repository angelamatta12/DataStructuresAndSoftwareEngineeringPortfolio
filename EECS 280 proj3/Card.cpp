// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include "Card.h"
// add any necessary #include or using directives here

// rank and suit names -- do not remove these
constexpr const char* const Card::RANK_TWO;
constexpr const char* const Card::RANK_THREE;
constexpr const char* const Card::RANK_FOUR;
constexpr const char* const Card::RANK_FIVE;
constexpr const char* const Card::RANK_SIX;
constexpr const char* const Card::RANK_SEVEN;
constexpr const char* const Card::RANK_EIGHT;
constexpr const char* const Card::RANK_NINE;
constexpr const char* const Card::RANK_TEN;
constexpr const char* const Card::RANK_JACK;
constexpr const char* const Card::RANK_QUEEN;
constexpr const char* const Card::RANK_KING;
constexpr const char* const Card::RANK_ACE;

constexpr const char* const Card::SUIT_SPADES;
constexpr const char* const Card::SUIT_HEARTS;
constexpr const char* const Card::SUIT_CLUBS;
constexpr const char* const Card::SUIT_DIAMONDS;

// add your code below


// NOTE: We HIGHLY recommend you check out the operator overloading
// tutorial in the project spec before implementing
// the following operator overload functions:
//   operator<<
//   operator<
//   operator<=
//   operator>
//   operator>=
//   operator==
//   operator!=aaaa

// literally suit on the card, not change due to bower, for get suit 


Card::Card(){

this->rank = RANK_TWO;
this->suit = SUIT_SPADES;


}

Card::Card(const std::string &rank_in, const std::string &suit_in){

this->rank = rank_in;
this->suit = suit_in;


}

  //EFFECTS Returns the rank
std::string Card::get_rank() const{

return rank;

  }

  //EFFECTS Returns the suit.  Does not consider trump. 
  std::string Card::get_suit() const{


return suit;


  }

  //REQUIRES trump is a valid suit
  //EFFECTS Returns the suit
  //HINT: the left bower is the trump suit!
  //objectname.
  //call left bower function
  //else return suit
  std::string Card::get_suit(const std::string &trump) const{


if(is_left_bower(trump)){

return trump;

}

return this->get_suit();


  }


//EFFECTS Returns true if card is a face card (Jack, Queen, King or Ace)
  //objectname.
  bool Card::is_face_or_ace() const{

if(get_rank() == RANK_ACE){

    return true;
}
else if(get_rank() == RANK_KING){

return true;

}
else if(get_rank() == RANK_JACK){
    
    return true;
    
    }
else if(get_rank() == RANK_QUEEN){
    
    return true;
    
    }

return false;


  }


  //REQUIRES trump is a valid suit
  //EFFECTS Returns true if card is the Jack of the trump suit
  //objectname.
  bool Card::is_right_bower(const std::string &trump) const{


if (get_rank() == RANK_JACK && get_suit() == trump){

return true;


}

return false;


  }

//REQUIRES trump is a valid suit
  //EFFECTS Returns true if card is the Jack of the next suit
  //objectname.
  bool Card::is_left_bower(const std::string &trump) const{

 if(get_rank() == RANK_JACK){


if(Suit_next(trump) == get_suit()){

return true;

}

 }

   return false;

  }



 //REQUIRES trump is a valid suit
  //EFFECTS Returns true if the card is a trump card.  All cards of the trump
  // suit are trump cards.  The left bower is also a trump card.
  //objectname.
  bool Card::is_trump(const std::string &trump) const{

 std::string suitTest = get_suit();


   if(is_left_bower(trump)){

   return true;

    }

  else if (suitTest == trump){

    return true;

  }


return false;

  }

//find rank weight 

int get_rank_weight(const Card &lhs){

int index = 0;
std::string rank = lhs.get_rank();

for(int i = 0; i< NUM_RANKS; i++){

if(RANK_NAMES_BY_WEIGHT[i] == rank){

index = i;
break;

}

}

return index;


}


//find suit weight 
int get_suit_weight(const Card &lhs){

int index = 0;
std::string rank = lhs.get_suit();


for(int i = 0; i< NUM_SUITS; i++){

if(SUIT_NAMES_BY_WEIGHT[i] == rank){

index = i;
break;

}

}

return index; 

}




//EFFECTS Returns true if lhs is lower value than rhs.
//  Does not consider trump.

bool operator<(const Card &lhs, const Card &rhs){

int weightSuitLhs = get_suit_weight(lhs);
int weightRankLhs = get_rank_weight(lhs);

int weightSuitRhs = get_suit_weight(rhs);
int weightRankRhs = get_rank_weight(rhs);


if(weightRankLhs < weightRankRhs){

return true;

}

else if(weightRankLhs > weightRankRhs){


return false;


}


//if == then suit determines which is larger

//check if suit > or <
else if(weightSuitLhs <  weightSuitRhs){

return true;

}
else if (weightSuitLhs >  weightSuitRhs){

return false;


}


return false;



}


//EFFECTS Returns true if lhs is lower value than rhs or the same card as rhs.
//  Does not consider trump.


bool operator<=(const Card &lhs, const Card &rhs){


//if > -> false r True


if(!(lhs > rhs)){

return true;

}

return false;


}



//EFFECTS Returns true if lhs is higher value than rhs.
//  Does not consider trump.

//need to ask 
bool operator>(const Card &lhs, const Card &rhs){


int weightSuitLhs = get_suit_weight(lhs);
int weightRankLhs = get_rank_weight(lhs);

int weightSuitRhs = get_suit_weight(rhs);
int weightRankRhs = get_rank_weight(rhs);


if(weightRankLhs < weightRankRhs){

return false;

}
else if(weightRankLhs > weightRankRhs){


return true;


}


//if rank ==, then use the suit
//check if suit > or <
else if(weightSuitLhs <  weightSuitRhs){

return false;

}
else if (weightSuitLhs >  weightSuitRhs){

return true;


}


return false;


}




//EFFECTS Returns true if lhs is higher value than rhs or the same card as rhs.
//  Does not consider trump.


bool operator>=(const Card &lhs, const Card &rhs){


if(!(lhs < rhs)){

return true;

}

return false;


}



//EFFECTS Returns true if lhs is same card as rhs.
//  Does not consider trump.


bool operator==(const Card &lhs, const Card &rhs){

int weightSuitLhs = get_suit_weight(lhs);
int weightRankLhs = get_rank_weight(lhs);

int weightSuitRhs = get_suit_weight(rhs);
int weightRankRhs = get_rank_weight(rhs);

if((weightRankLhs == weightRankRhs) && (weightSuitLhs == weightSuitRhs) ){

return true;

}


return false; 



}

//EFFECTS Returns true if lhs is not the same card as rhs.
//  Does not consider trump.

bool operator!=(const Card &lhs, const Card &rhs){


if(!(lhs == rhs)){

return true;

}

return false;

}



//REQUIRES suit is a valid suit
//EFFECTS returns the next suit, which is the suit of the same color

std::string Suit_next(const std::string &suit){



if(suit == Card::SUIT_SPADES){

return Card::SUIT_CLUBS;

}
else if (suit == Card::SUIT_CLUBS){

return Card::SUIT_SPADES;

}

else if(suit == Card::SUIT_DIAMONDS){

return Card::SUIT_HEARTS;

}
 
return Card::SUIT_DIAMONDS;


}

//EFFECTS Prints Card to stream, for example "Two of Spades"

std::ostream & operator<<(std::ostream &os, const Card &card){


os << card.get_rank() << " of "<< card.get_suit();

return os;

}



//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// order, as described in the spec.


//trump beats all or if we have multiple trump cards 
//trump then norm order suit and rank 

bool Card_less(const Card &a, const Card &b, const std::string &trump){

//need to see if either are trump 
//b, not a -> T

if((b.get_suit(trump) == trump) && (a.get_suit(trump) != trump )){

return true;

}

// a not b -> F

else if(b.get_suit(trump) != trump && (a.get_suit(trump) == trump)){

return false;

}
//both are bower
//the one that is the "same color"
//is less

//need to check which is L or R

//L < R 

bool bLBower = b.is_left_bower(trump);
bool bRBower = b.is_right_bower(trump);

bool aLBower = a.is_left_bower(trump);
bool aRBower = a.is_right_bower(trump);

if(bRBower){

return true;

}

else if (aRBower){

return false;

}

//need to check 

//one is left bower, other is not 

else if (aLBower && !bRBower){

return false;

}


else if (!aRBower && bLBower){

return true;

}








//neither 
//could be same or diff suit
//shouldnt be running 
//into case of same color, opp
//is > like w/ D & H 
//same with the rank 
//a<b 

//both are trump -> same suit
//then rank order 


// a<b -> T
//a >= b -> F

return a < b;


}


//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.

//trump beats led
//led beats everything else 
//card order next 
//need to implement the bowers

bool Card_less(const Card &a, const Card &b, const Card &led_card,
               const std::string &trump){


std::string ledCardSuit = led_card.get_suit(trump);

//check if led and trump are same

if(trump == ledCardSuit){

Card_less(a,b,trump);

}

//nope then 

//1. check if either are the trump suit
//trump beat led 

//b not a then -> T

if((b.get_suit(trump) == trump )&& (a.get_suit(trump) != trump )){

return true;

}

// a not b them -> F 


else if(b.get_suit(trump) != trump && (a.get_suit(trump) == trump)){

return false;

}


//neither are trump

//2. check if either are led

//b not a then -> T

else if((b.get_suit(trump) == ledCardSuit)&& (a.get_suit(trump) != ledCardSuit )){

return true;

}
// a not b them -> F 


else if((b.get_suit(trump) != ledCardSuit)&& (a.get_suit(trump) == ledCardSuit )){

return false;

}


//both are bower 


bool bLBower = b.is_left_bower(trump);
bool bRBower = b.is_right_bower(trump);

bool aLBower = a.is_left_bower(trump);
bool aRBower = a.is_right_bower(trump);

if(bRBower){

return true;

}

else if (aRBower){

return false;

}

//need to check 

//one is left bower, other is not 

else if (aLBower && !bRBower){

return false;

}


else if (!aRBower && bLBower){

return true;

}


//cant be bowers 

//both can be trump ->RANK

//both can be led  -> RANK 

//both can be same suit -> RANK 

//can be same rank not suit -> SUIT

//can be diff for both -> R&S

return a < b;

               }











