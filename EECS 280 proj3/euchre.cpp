// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "Player.h"
#include "Pack.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>



class Game {

private:
//pack of cards
Pack p;

//collection of players 
std::vector <Player *> playerSet;

//collection of cards for tricks
std::vector <Card> cardTrickSet;

//selected player for dealer
int currentDealer;

//selected player for making trump 
int currentTrumpMaker;

int currentLedMaker;

//pairs
//note odds are pair 
//evens are pair 

int oddPairPoints = 0;

int evenPairPoints = 0;

bool shuffleFlag;

int pointTarget;

std::string trumpSuit;

Card currentLed;

//zero 1st
std::vector<int> ord1 = {1,2,3,0};

//one 1st
std::vector<int> ord2 = {2,3,0,1};

//two 1st
std::vector<int> ord3 = {3,0,1,2};

//three 1st

std::vector<int> ord4 = {0,1,2,3};




//trick order


//zero 1st
std::vector<int> trickOrd1 = {1,2,3};

//one 1st
std::vector<int> trickOrd2 = {2,3,0};


//two 1st
std::vector<int> trickOrd3 = {3,0,1};


//three 1st

std::vector<int> trickOrd4 = {0,1,2};



//order is always 1 left of dealer to start 

//playing trump 

//playing tricks




public:



std::vector<int> currentOrder(int trumpMaker){

switch(trumpMaker){

case 0:
return ord4;
break;

case 1:
return ord1;
break;

case 2:
return ord2;
break;

case 3:
return ord3;
break;

}


return ord3;


}





std::vector<int> currentOrderTrick(){

switch(currentLedMaker){

case 0:
return trickOrd1;
break;

case 1:
return trickOrd2;
break;

case 2:
return trickOrd3;
break;

}

return trickOrd4;

}





std::vector<int> currentOrder(){

switch(currentDealer){

case 0:
return ord1;
break;

case 1:
return ord2;
break;

case 2:
return ord3;
break;

}

return ord4;

}

//constructor
  Game(std::string packFile, int point, std::string shuf,
  std::vector<std::string> str){


//populate the pack
std::ifstream fin;

fin.open(packFile);

if(!fin.is_open()){
std::cout <<"read" <<std::endl;
std::cout <<"error opening file" << packFile <<std::endl;
}

p = Pack(fin);

fin.close();

//populate the players

for(int i = 0; i < str.size()-1; i = i+2){

Player *pl = Player_factory(str[i],str[i+1]);

playerSet.push_back(pl);



}





//populate point target
pointTarget = point;


//populate shuffle flag

if(shuf == "shuffle"){

shuffleFlag = true;

}
else{
shuffleFlag = false;
}

  };


//setup 
//shuffle or no shuffle

void shuffle(Pack p){

p.shuffle();

}




//deal the cards to each person 

void deal(std::vector<int> dealOrder){

//first deal round 

for(int i = 0; i <1; i++){

for(int j = 0; j< dealOrder.size(); j++){

  int currentLoc = dealOrder[j];

  Player *select = playerSet[currentLoc];

//0 1st person 2 3 
//1 2nd person 3 2 
//2 3rd person 2 3
//3 4th person 3 2 

if(j == 0 || j == 2){

select->add_card(p.deal_one());
select->add_card(p.deal_one());
select->add_card(p.deal_one());


}

else{

select->add_card(p.deal_one());
select->add_card(p.deal_one());

}





}

}



//second deal round 
for(int i = 0; i <1; i++){

for(int j = 0; j< dealOrder.size(); j++){

  int currentLoc = dealOrder[j];

  Player *select = playerSet[currentLoc];


//0 1st person 2 3 
//1 2nd person 3 2 
//2 3rd person 2 3
//3 4th person 3 2 

if(j ==0 || j == 2){


select->add_card(p.deal_one());
select->add_card(p.deal_one());

}

else{
select->add_card(p.deal_one());
select->add_card(p.deal_one());
select->add_card(p.deal_one());

}


}

}

}

void updateLedMaker(){

if(currentDealer != 3){
currentLedMaker = currentDealer+1;
}
else{

currentLedMaker = 0;

}

}





//making trump rounds 1 to 3

void trumpRounds(Card up,int indDealer,std::string newSuit,std::vector<int> trumpOrder){
int roundMade = 0;

bool breakFlag = false;

//rounds
for(int i = 1; i < 4; i++){

//players
for(int j = 0; j < trumpOrder.size(); j++){

int ind = trumpOrder[j];

Player *select = playerSet[trumpOrder[j]];

if(select->make_trump(up,indDealer == ind,i,newSuit)){

currentTrumpMaker = ind;
roundMade = i;
std::cout << select->get_name() <<" orders up "<< newSuit <<std::endl;

trumpSuit = newSuit;

updateLedMaker();

breakFlag = true;
break;

}

else{

std::cout << select->get_name() <<" passes" <<std::endl;

}

}


if(breakFlag){

break;

}


}

if(roundMade == 1){

setUpTrumpB4Tricks(up, currentDealer);

}


}


void setUpTrumpB4Tricks(Card up, int indDealer){
    Player *select = playerSet[indDealer];

select->add_and_discard(up);




}



//playing led card 
//need a way to keep track of players 

Card setUpTricks(int indMadeTrump){

Player *select = playerSet[indMadeTrump];

Card ledPlayed = select->lead_card(trumpSuit);

cardTrickSet.push_back(ledPlayed);

std::cout << ledPlayed <<" led by "<< select->get_name()<<std::endl;


currentLed = ledPlayed;

currentLedMaker = indMadeTrump;

return ledPlayed;

}



int determineTrickRoundWinner(std::vector<Card> c,std::string t,const Card &led_card){


int high = 0;
Card highC = c[high];

for(int i = 1; i<c.size();i++){

if(Card_less(highC,c[i],led_card,t)){

high = i;

highC = c[i];

}

}


return high;


}

void determineTrickRoundsWinner(int oddW, int evenW,int indMadeTrump){

//use counter and indMadeTrump to award points 
//odd pair made trump 
if(indMadeTrump % 2 == 1 && 

(oddW== 3 ||oddW== 4)){
std::cout << playerSet[1]->get_name() << " and " << playerSet[3]->get_name() <<
" win the hand" << std::endl;
oddPairPoints++;
}


else if(indMadeTrump % 2 == 1 && 
(oddW== 5)){
std::cout << playerSet[1]->get_name() << " and " << playerSet[3]->get_name() <<
" win the hand" << std::endl;
std::cout << "march!" <<std::endl;
oddPairPoints = oddPairPoints +2;
}

//odd pair didnt make trump 
else if(indMadeTrump % 2 == 0 && 
(oddW== 3 ||oddW== 4||oddW== 5)){
std::cout << playerSet[1]->get_name() << " and " << playerSet[3]->get_name() <<
" win the hand" << std::endl;
std::cout << "euchred!" << std::endl;
oddPairPoints = oddPairPoints +2;
}
//even pair didnt make trump
else if( indMadeTrump % 2 == 1 && 
(evenW== 3 ||evenW== 4||evenW== 5)){
std::cout << playerSet[0]->get_name() << " and " << playerSet[2]->get_name() <<
" win the hand" << std::endl;
std::cout << "euchred!" << std::endl;
evenPairPoints = evenPairPoints +2;
}

//even pair made trump
else if(indMadeTrump % 2 == 0 && 
(evenW== 3 ||evenW== 4)){


std::cout << playerSet[0]->get_name() << " and " << playerSet[2]->get_name() <<
" win the hand" << std::endl;



evenPairPoints++;

}


else if( indMadeTrump % 2 == 0 && 
(evenW== 5)){


std::cout << playerSet[0]->get_name() << " and " << playerSet[2]->get_name() <<
" win the hand" << std::endl;

std::cout << "march!" << std::endl;

evenPairPoints = evenPairPoints + 2;

}

}
//rounds for "tricks" 1 to 5 

//tallying scores at the end, need
//to keep track of which pair made trump 

void trickRounds(int indMadeTrump){
int evenRoundWins = 0;
int oddRoundWins = 0;
//rounds
for(int j = 0;j<5;j++){
 setUpTricks(currentLedMaker);
std::vector<int> trickOrder = currentOrderTrick();
//not finding the correct currentOrder
std::vector<int> curOrder = currentOrder(currentLedMaker);
//players
for(int i = 0; i< trickOrder.size();i++){
int ind = trickOrder[i];
 Player *select = playerSet[ind];
Card trickPlayed = select->play_card(currentLed,trumpSuit);
std::cout << trickPlayed <<" played by "<< select->get_name()<<std::endl;
cardTrickSet.push_back(trickPlayed);
}
int winningCardLoc = determineTrickRoundWinner(cardTrickSet,trumpSuit,currentLed);
currentLedMaker = curOrder[winningCardLoc];
if(currentLedMaker % 2 == 0 ){
std::cout << playerSet[currentLedMaker]->get_name() << " takes the trick"<<std::endl;
evenRoundWins++;
}
else{
std::cout << playerSet[currentLedMaker]->get_name() 
<< " takes the trick"<<std::endl;
oddRoundWins++;
}
cardTrickSet.clear();
std::cout
<<std::endl;
}
determineTrickRoundsWinner(oddRoundWins, evenRoundWins,indMadeTrump);
std::cout << playerSet[0]->get_name() << " and " << playerSet[2]->get_name() <<
" have "<< evenPairPoints <<" points" << std::endl;
std::cout << playerSet[1]->get_name() << " and " << playerSet[3]->get_name() <<
" have "<< oddPairPoints <<" points"  << std::endl;

}



//should check if we only shuffle once

//play method
void play(){

currentDealer = 0;

int countrounds = 0; 


while(evenPairPoints < pointTarget && oddPairPoints < pointTarget){ 

std::string upSuit = "";

Card currentUp; 


std::vector <int> dealingOrder = currentOrder();

if(shuffleFlag){

p.shuffle();

}

// //deal cards
deal(dealingOrder);

currentUp = p.deal_one();

upSuit = currentUp.get_suit();

// //print out the hand 

//need to change it so based off of round starting 0

std::cout << "Hand " << countrounds<< std::endl;

// //print out dealer

std::cout << playerSet[currentDealer]->get_name()<< " deals"<<std::endl;


// //print out current up card

std::cout<< currentUp << " turned up"<<std::endl;


// //call trump function
trumpRounds(currentUp,currentDealer,upSuit,dealingOrder);

std::cout << std::endl;

// //call rounds function

trickRounds(currentTrumpMaker);


// //increment current dealer, 

// //check if current dealer > # of players

// //yes reset to zero 
if(currentDealer == 3){
currentDealer = 0;
}
else{
currentDealer++;
}

//maybe should see about clearing this like I am supposed to clear the players instead
//of clear 

cardTrickSet.clear();

//reset deck 

p.reset();

countrounds++;

std::cout <<std::endl;

}



// //check who has reached the point goal

if(evenPairPoints >= pointTarget){
std::cout<<std::endl;
std::cout << playerSet[0]->get_name() 
<< " and "<< playerSet[2]->get_name() << " win!"<<std::endl;

}

else{
std::cout<<std::endl;
std::cout << playerSet[1]->get_name()
 << " and "<< playerSet[3]->get_name() << " win!"<<std::endl;

}



//anounce winner, reset 

evenPairPoints = 0;
oddPairPoints = 0;
currentDealer = 0;
currentTrumpMaker = 0;
cardTrickSet.clear();





// //delete players at the end
 

for (size_t i = 0; i < playerSet.size(); ++i) {
  delete playerSet[i];
}

}


};


int main(int argc, char **argv) {
  // Read command line args and check for errors

std::string shuffleWord = argv[2];

if(!(argc == 12)){

std::cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << std::endl;

return 1;
}

else if (shuffleWord  != "shuffle" && shuffleWord  != "noshuffle"){

std::cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << std::endl;



return 1;

}

int points = std::atoi(argv[3]);
if(points < 1 || points > 100){


std::cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << std::endl;



return 1;


}

std::string type1 = argv[5];
std::string type2 = argv[7];
std::string type3= argv[9];
std::string type4 = argv[11]; 

//5,7,9,11
if((type1 != "Simple"&& type1!="Human")
&&(type2 != "Simple"&& type2!="Human")
&&(type3 != "Simple"&& type3 !="Human")
&&(type4 != "Simple"&&type4!="Human")){


std::cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << std::endl;

return 1;

}

std::ifstream fin;

fin.open(argv[1]);

if(!fin.is_open()){
std::cout << "Error opening " << argv[1] <<std::endl;
return 1;
}

std::vector<std::string> playAtt;

for(int i = 4;i<12;i++){

playAtt.push_back(argv[i]);

}


std::cout << argv[0]<< " "
<< argv[1]<< " "
<< argv[2]<< " "
<< argv[3]<< " "
<< argv[4]<< " "
<< argv[5]<< " "
<< argv[6]<< " "
<< argv[7]<< " "
<< argv[8]<< " "
<< argv[9]<< " "
<< argv[10]<< " "
<< argv[11]<< " "<<std::endl;
  Game game(argv[1],atoi(argv[3]),argv[2],playAtt);
  game.play();


}
