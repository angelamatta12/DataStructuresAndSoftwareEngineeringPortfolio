// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "Player.h"
#include <string>
#include <vector>
#include <cassert>
#include <iostream> 
#include <algorithm>


int findNonTrump(std::vector<Card> h,std::string t){

int nonTrump;

for(int i = 0; i<h.size();i++){

if(!h[i].is_trump(t)){

nonTrump = i;


}


}

return nonTrump;

}




//notes regarding imp 

//2. how to delete an obj @ specific 
//index in vector

//hand.begin+position = delete @ position 

//note for first one am comparing it to itself!!

int findIndHighCardled(std::vector<Card> h,std::string t,const Card &led_card){

int high = findNonTrump(h,t);
Card highC = h[high];

for(int i = 0; i<h.size();i++){

if(Card_less(highC,h[i],led_card,t) && 
h[i].get_suit(t) == led_card.get_suit(t)){

high = i;

highC = h[i];

}

}

return high;

}


int findIndHighCardledAllTrump(std::vector<Card> h,std::string t,const Card &led_card){

int high = 0;
Card highC = h[high];

for(int i = 1; i<h.size();i++){

if(Card_less(h[i],highC,led_card,t)){

high = i;

highC = h[i];

}

}

return high;

}







int findIndHighCard(std::vector<Card> h,std::string t){

int high = 0;
Card highC = h[high];

for(int i = 0; i<h.size();i++){

if(!Card_less(h[i], highC,t)){

high = i;

highC = h[i];

}

}

return high;

}




int findIndHighCardButNotTrump(std::vector<Card> h,std::string t){

int high = findNonTrump(h,t);
Card highC = h[high];

for(int i = 0; i<h.size();i++){

if((Card_less(highC,h[i],t)) && h[i].get_suit(t) != t){

high = i;

highC = h[i];

}

}

return high;

}



int findIndLowestInd(std::vector<Card> h,std::string t,Card l){

int low = 0;
Card lowC = h[low];

for(int i = 1; i<h.size();i++){

//need to ensure that the card suit doesnt equal the led suit
if(Card_less(h[i],lowC,l,t) ){

low = i;

lowC = h[i];

}

}

return low;

}


//need to see if this works as intended
std::ostream & operator<<(std::ostream &os, const Player &p){

os << p.get_name();

return os;
    
}



// void sort( RandomIt first, RandomIt last, Compare comp ){




// }



class SimplePlayer:public Player{

private:

//name
std::string name;


//hand 
std::vector<Card> hand;

public:

SimplePlayer(std::string n){

name = n;

}

const std::string & get_name() const{

return name;

}

void add_card(const Card &c){

assert(hand.size() < MAX_HAND_SIZE);

hand.push_back(c);

}


void add_and_discard(const Card &upcard){

hand.push_back(upcard);

//sort(hand.begin(),hand.end());

//find lowest card 

int lowLoc = findIndLowestInd(hand,upcard.get_suit(),upcard);


hand.erase(hand.begin()+lowLoc);

}


Card lead_card(const std::string &trump){

//find if they have non trump card 

//count 
Card toBePlayed;

int countTrump = 0;
for(int i = 0; i<hand.size();i++){

if(hand[i].is_trump(trump)){

countTrump++;

}

}

if(countTrump  < hand.size()){

int indexNotTrump = findIndHighCardButNotTrump(hand,trump);

toBePlayed = hand[indexNotTrump];

hand.erase(hand.begin()+indexNotTrump);

return toBePlayed;

}

else{

int indexTrump = findIndHighCard(hand,trump);

toBePlayed = hand[indexTrump];

hand.erase(hand.begin()+indexTrump);

return toBePlayed;


}

}



Card play_card(const Card &led_card, const std::string &trump){

//can follow suit
//play highest led
Card toBePlayed;

int countLed = 0;
int countTrump = 0;

if(hand.size() == 1){

toBePlayed = hand[0];

hand.erase(hand.begin());

return toBePlayed;

}


for(int i = 0; i< hand.size();i++){

if(hand[i].get_suit(trump) == led_card.get_suit(trump)){

countLed++;

}
else if (hand[i].is_trump(trump)){

countTrump++;

}

}


if(led_card.get_suit(trump) == trump && countLed == hand.size()){

int indexHighLed = findIndHighCard(hand,trump);

toBePlayed = hand[indexHighLed];

hand.erase(hand.begin()+indexHighLed);

return toBePlayed;

}

 else if(countTrump == hand.size() && led_card.get_suit(trump) != trump){

int indexHighLed = findIndHighCardledAllTrump(hand,trump,led_card);

toBePlayed = hand[indexHighLed];

hand.erase(hand.begin()+indexHighLed);

return toBePlayed;

}

else if(countLed > 0){
int indexHighLed = findIndHighCardled(hand,trump,led_card);

toBePlayed = hand[indexHighLed];

hand.erase(hand.begin()+indexHighLed);

return toBePlayed;

}
//nope 
//play lowest non led


int indexLowest = findIndLowestInd(hand,trump,led_card);

toBePlayed = hand[indexLowest];

hand.erase(hand.begin()+indexLowest);

return toBePlayed;



}



int countFaceAce(Card upcard)const{

int countFace = 0;

 for(int i = 0; i< hand.size();i++){

bool faceAceFlag = hand[i].is_face_or_ace();

if(faceAceFlag && (upcard.get_suit() == hand[i].get_suit(upcard.get_suit()))){

countFace++;

}

}

return countFace;

}



bool make_trump(const Card &upcard, bool is_dealer,
                          int round, std::string &order_up_suit) const{



if(round == 1){

 int countFace = countFaceAce(upcard);

if(countFace >= 2){

order_up_suit = upcard.get_suit();

return true;

}

}

//same as above but need to 
else if(round == 2){

 int countFace2 = 0;

 for(int i = 0; i< hand.size();i++){

bool faceAceFlag = hand[i].is_face_or_ace();

if(faceAceFlag && (Suit_next(upcard.get_suit())
 == hand[i].get_suit(Suit_next(upcard.get_suit())))){

countFace2++;

}

}


if(countFace2 >= 1){

order_up_suit = Suit_next(upcard.get_suit());
return true;

}

}

else if (is_dealer && round == 3){

//need  to check if this is the suit I set it to
order_up_suit = Suit_next(upcard.get_suit());

return true;


}

return false;

 }

};






class HumanPlayer:public Player{

private:

//name
std::string name;
//player strat
const std::string strat ="Human";

//hand 
std::vector<Card> hand;


public:

HumanPlayer(std::string n){

    name = n;
}


const std::string & get_name() const{

return name;

}

void add_card(const Card &c){

assert(hand.size() < MAX_HAND_SIZE);

    hand.push_back(c);

    sort(hand.begin(),hand.end());
}


void print_hand() const {

  for (size_t i=0; i < hand.size(); ++i)
    std::cout << "Human player " << name << "'s hand: "
         << "[" << i << "] " << hand[i] << "\n";
}


void add_and_discard(const Card &upcard){

//logic to check which card to discard
print_hand();

std::cout << "Discard upcard: [-1]\n";
std::cout << "Human player " << name << ", please select a card to discard:\n";

std::string respon = "";

std::cin >> respon;

int pos = stoi(respon);

if(pos != -1){
//discard card

hand.erase(hand.begin()+pos);

add_card(upcard);

}

sort(hand.begin(),hand.end());


}


int promptRespon(){
sort(hand.begin(),hand.end());

print_hand();
std::cout << "Human player " << name << ", please select a card:\n";

std::string respon = "";

std::cin >> respon;

int pos = stoi(respon);

return pos;


}



//need to check if both are correct or 
//if need to do something with the param
Card lead_card(const std::string &trump){

int position = promptRespon();

Card toBePlayed = hand[position];

hand.erase(hand.begin()+ position);

sort(hand.begin(),hand.end());

return toBePlayed;



}


Card play_card(const Card &led_card, const std::string &trump){

int position = promptRespon();

Card toBePlayed = hand[position];

hand.erase(hand.begin()+ position);

sort(hand.begin(),hand.end());

return toBePlayed;




}


bool make_trump(const Card &upcard, 
bool is_dealer,
int round, 
std::string &order_up_suit) 
const{

//need to prompt the user but need 
//check round tho, need to account for not
//being able to select upCard suit round 2 

print_hand();
std::cout << "Human player " << name << ", please enter a suit, or \"pass\":\n";

std::string respon = "";

std::cin >> respon;

//round 1 can be same as upcard suit

if(respon != "pass" && respon == upcard.get_suit() && round == 1){

//selected one 

order_up_suit = respon;

return true;

}


//round 2 any but the upcard


else if (respon != "pass" && respon != upcard.get_suit() && round == 2){

//selected one

order_up_suit = respon;

return true;

}

//round 3 screw dealer 

else if (is_dealer && round == 3){

order_up_suit = respon;

return true;

}

return false;

 }





};




Player * Player_factory(const std::string &name, const std::string &strategy){

if(strategy == "Simple"){

return new SimplePlayer(name);

}


return new HumanPlayer(name);

}




