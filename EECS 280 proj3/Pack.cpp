// Project UID 1d9f47bfc76643019cfbf037641defe1
#include "Card.h"
#include "Pack.h"
#include <array>
#include <string>

  Pack::Pack(){
//grab the suit 
reset();

for(int i = 0; i < NUM_SUITS; i++){

int count = 0;

if(i == 1){

count = 6;

}

else if (i == 2){

    count = 12;
}

else if(i == 3){

count = 18;

}

//grab the rank 
for(int j = 7; j< NUM_RANKS; j++){
std::string suit = SUIT_NAMES_BY_WEIGHT[i];

std::string rank = RANK_NAMES_BY_WEIGHT[j];

Card c = Card(rank,suit);

//add to the deck 
cards[count] = c;

count++;

}

}

reset();

  }




  // REQUIRES: cards remain in the Pack
  // EFFECTS: Returns the next card in the pack and increments the next index
  Card Pack::deal_one(){

   Card c = cards[next];

   next++;

   return c;

  }

  // EFFECTS: Resets next index to first card in the Pack
  void Pack::reset(){

   next = 0;

  }
// REQUIRES: pack_input contains a representation of a Pack in the
  //           format required by the project specification
  // MODIFIES: pack_input
  // EFFECTS: Initializes Pack by reading from pack_input.
  Pack::Pack(std::istream& pack_input){

std::string suit = "";
std::string rank = "";
std::string ofStorage ="";

for(int i = 0;i<PACK_SIZE;i++){

pack_input >> rank >> ofStorage >> suit;

cards[i]= Card(rank,suit);

}

reset();

  }




  // EFFECTS: Shuffles the Pack and resets the next index. This
  //          performs an in shuffle seven times. See
  //          https://en.wikipedia.org/wiki/In_shuffle.

  void Pack::shuffle(){

//split in half 

Card a[PACK_SIZE/2];
Card b[PACK_SIZE/2];


std::array<Card,PACK_SIZE> copyPack;
for(int j = 0; j < 7;j++){


for(int i = 0; i < PACK_SIZE/2;i++){

a[i]= cards[i];


}


int count2 = 0;
for(int j = PACK_SIZE/2; j < PACK_SIZE;j++){

b[count2]= cards[j];
count2++;

}


int countB =0;
int countA = 0;

for(int i = 0; i< PACK_SIZE;i++){

//check if index even or odd 
//even
if(i%2 == 0){

copyPack[i]= b[countB];
countB++;

}


else if(i%2==1){

copyPack[i]= a[countA];
countA++;


}

}

cards = copyPack;


//split again


// for(int i = 0; i < PACK_SIZE/2;i++){

// a[i]= cards[i];


// }
 
// count2 = 0;
// for(int j = PACK_SIZE/2; j < PACK_SIZE;j++){

// b[count2]= cards[j];
// count2++;

// }


}

reset();

  }


  // EFFECTS: returns true if there are no more cards left in the pack
  bool Pack::empty() const{

if(next >= PACK_SIZE){
    return true;
}

return false;

  }
