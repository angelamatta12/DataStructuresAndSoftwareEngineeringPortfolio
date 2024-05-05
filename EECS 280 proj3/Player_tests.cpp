// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>
#include <cassert>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

//led and trump not same
TEST(makeTrumpNS){
 Player * alice = Player_factory("Alice", "Simple");
Card c1 = Card(Card::RANK_NINE,Card::SUIT_SPADES);
Card c2 = Card(Card::RANK_TEN,Card::SUIT_SPADES);
Card c3 = Card(Card::RANK_JACK,Card::SUIT_SPADES);
Card c4 = Card(Card::RANK_KING,Card::SUIT_HEARTS);
Card c5 = Card(Card::RANK_ACE,Card::SUIT_HEARTS);


alice->add_card(c1);
alice->add_card(c2);
alice->add_card(c3);
alice->add_card(c4);
alice->add_card(c5);

Card up1R1 = Card(Card::RANK_QUEEN,Card::SUIT_SPADES);
Card up2R1 = Card(Card::RANK_QUEEN,Card::SUIT_HEARTS);
Card up3R2 = Card(Card::RANK_QUEEN,Card::SUIT_CLUBS);
Card up4R3 = Card(Card::RANK_QUEEN,Card::SUIT_DIAMONDS);

//int countR1 = 1; 
//int countR2 = 2;
//int countR3 = 3;

std::string r1 = "";
std::string r2 = "";
std::string r3 = "";
//first round order up 

//spades no
bool firstRound1 = alice->make_trump(up1R1,true,1,r1);
//ASSERT_EQUAL(r1,Card::SUIT_SPADES);
ASSERT_EQUAL(firstRound1,false);

//hearts yes
bool secondRound1 = alice->make_trump(up2R1,true,1,r1);
ASSERT_EQUAL(r1,Card::SUIT_HEARTS);
assert(secondRound1);


//shouldnt order up first round

//diamonds no
bool firstRound1No = alice->make_trump(up4R3,true,1,r1);
ASSERT_EQUAL(firstRound1No,false);

//clubs no 

bool firstRound2No = alice->make_trump(up3R2,true,1,r1);

ASSERT_EQUAL(firstRound2No,false);


//second round 

//clubs upcard

bool secondRound1No = alice->make_trump(up3R2,true,2,r2);
ASSERT_EQUAL(secondRound1No,true);
ASSERT_EQUAL(r2,Card::SUIT_SPADES);


//spades upcard

bool secondRound2No = alice->make_trump(up1R1,true,2,r2);
ASSERT_EQUAL(secondRound2No,true);
ASSERT_EQUAL(r2,Card::SUIT_CLUBS);

//diamonds upcard

bool secondRound3Yes = alice->make_trump(up4R3,true,2,r2);
ASSERT_EQUAL(r2,Card::SUIT_HEARTS);
assert(secondRound3Yes);


//hearts upcard 

bool secondRound4No = alice->make_trump(up2R1,true,2,r2);
ASSERT_EQUAL(secondRound4No,false);
//round 3 screw dealer 

//is dealer 
bool thirdRoundYes = alice->make_trump(up2R1,true,3,r2);
ASSERT_EQUAL(thirdRoundYes,true);

//not dealer

bool thirdRoundNo = alice->make_trump(up2R1,false,3,r2);
ASSERT_EQUAL(thirdRoundNo,false);

 delete alice;

}



//playing nonhighest 
TEST(playLed){



Player * alice = Player_factory("Alice", "Simple");
Card c1 = Card(Card::RANK_NINE,Card::SUIT_SPADES);
Card c2 = Card(Card::RANK_TEN,Card::SUIT_SPADES);
Card c3 = Card(Card::RANK_JACK,Card::SUIT_SPADES);
Card c4 = Card(Card::RANK_KING,Card::SUIT_HEARTS);
Card c5 = Card(Card::RANK_ACE,Card::SUIT_HEARTS);


alice->add_card(c1);
alice->add_card(c2);
alice->add_card(c3);
alice->add_card(c4);
alice->add_card(c5);


//play led

//trump diamonds
//AH

Card tc1 = alice->lead_card(Card::SUIT_DIAMONDS);
ASSERT_EQUAL(tc1,c5);

 delete alice;


}

//seperating led 


TEST(playLed2){


Player * alice = Player_factory("Alice", "Simple");
Card c1 = Card(Card::RANK_NINE,Card::SUIT_SPADES);
Card c2 = Card(Card::RANK_TEN,Card::SUIT_SPADES);
Card c3 = Card(Card::RANK_JACK,Card::SUIT_SPADES);
Card c4 = Card(Card::RANK_KING,Card::SUIT_HEARTS);
Card c5 = Card(Card::RANK_ACE,Card::SUIT_HEARTS);


alice->add_card(c1);
alice->add_card(c2);
alice->add_card(c3);
alice->add_card(c4);
alice->add_card(c5);



//trump hearts
//JS

Card tc2 = alice->lead_card(Card::SUIT_HEARTS);
ASSERT_EQUAL(tc2,c3);



delete alice;

}



TEST(playLed3){


Player * alice = Player_factory("Alice", "Simple");
Card c1 = Card(Card::RANK_NINE,Card::SUIT_SPADES);
Card c2 = Card(Card::RANK_TEN,Card::SUIT_SPADES);
Card c3 = Card(Card::RANK_JACK,Card::SUIT_SPADES);
Card c4 = Card(Card::RANK_KING,Card::SUIT_HEARTS);
Card c5 = Card(Card::RANK_ACE,Card::SUIT_HEARTS);


alice->add_card(c1);
alice->add_card(c2);
alice->add_card(c3);
alice->add_card(c4);
alice->add_card(c5);



//trump spades
//AH
Card tc3 = alice->lead_card(Card::SUIT_SPADES);
ASSERT_EQUAL(tc3,c5);


delete alice;

}




TEST(playLed4){


Player * alice = Player_factory("Alice", "Simple");
Card c1 = Card(Card::RANK_NINE,Card::SUIT_SPADES);
Card c2 = Card(Card::RANK_TEN,Card::SUIT_SPADES);
Card c3 = Card(Card::RANK_JACK,Card::SUIT_SPADES);
Card c4 = Card(Card::RANK_KING,Card::SUIT_HEARTS);
Card c5 = Card(Card::RANK_ACE,Card::SUIT_HEARTS);


alice->add_card(c1);
alice->add_card(c2);
alice->add_card(c3);
alice->add_card(c4);
alice->add_card(c5);

//trump clubs
//AH

Card tc4 = alice->lead_card(Card::SUIT_CLUBS);
ASSERT_EQUAL(tc4,c5);


delete alice;

}


//has only trump 
TEST(playLedNS){

 Player * alice = Player_factory("Alice", "Simple");
Card c1 = Card(Card::RANK_NINE,Card::SUIT_SPADES);
Card c2 = Card(Card::RANK_TEN,Card::SUIT_SPADES);
Card c3 = Card(Card::RANK_JACK,Card::SUIT_SPADES);

alice->add_card(c1);
alice->add_card(c2);
alice->add_card(c3);


Card up = Card(Card::RANK_QUEEN,Card::SUIT_SPADES);

//should be Jack 

Card c = alice->lead_card(Card::SUIT_SPADES);
ASSERT_EQUAL(c,c3);

 delete alice;



}


//trump and led same 
//can follow suit 
TEST(playCard){

 Player * alice = Player_factory("Alice", "Simple");
Card c1 = Card(Card::RANK_NINE,Card::SUIT_SPADES);
Card c2 = Card(Card::RANK_TEN,Card::SUIT_SPADES);
Card c3 = Card(Card::RANK_JACK,Card::SUIT_SPADES);
Card c4 = Card(Card::RANK_KING,Card::SUIT_HEARTS);
Card c5 = Card(Card::RANK_ACE,Card::SUIT_HEARTS);


alice->add_card(c1);
alice->add_card(c2);
alice->add_card(c3);
alice->add_card(c4);
alice->add_card(c5);

Card ledUp = Card(Card::RANK_QUEEN,Card::SUIT_HEARTS);

Card played = alice->play_card(ledUp,Card::SUIT_HEARTS);

ASSERT_EQUAL(played,c5);

 delete alice;


}

//trump and led same 
//cant follow suit 
TEST(playCard1){

 Player * alice = Player_factory("Alice", "Simple");
Card c1 = Card(Card::RANK_NINE,Card::SUIT_SPADES);
Card c2 = Card(Card::RANK_TEN,Card::SUIT_SPADES);
Card c3 = Card(Card::RANK_JACK,Card::SUIT_SPADES);
Card c4 = Card(Card::RANK_KING,Card::SUIT_HEARTS);
Card c5 = Card(Card::RANK_ACE,Card::SUIT_HEARTS);



alice->add_card(c1);
alice->add_card(c2);
alice->add_card(c3);
alice->add_card(c4);
alice->add_card(c5);


Card ledUp = Card(Card::RANK_QUEEN,Card::SUIT_DIAMONDS);

Card played = alice->play_card(ledUp,Card::SUIT_DIAMONDS);

ASSERT_EQUAL(played,c1);




 delete alice;


}



//trump and led not same 
//can folllow

TEST(playCardNS1){

 Player * alice = Player_factory("Alice", "Simple");
Card c1 = Card(Card::RANK_NINE,Card::SUIT_SPADES);
Card c2 = Card(Card::RANK_TEN,Card::SUIT_SPADES);
Card c3 = Card(Card::RANK_JACK,Card::SUIT_SPADES);
Card c4 = Card(Card::RANK_KING,Card::SUIT_HEARTS);
Card c5 = Card(Card::RANK_ACE,Card::SUIT_HEARTS);


alice->add_card(c1);
alice->add_card(c2);
alice->add_card(c3);
alice->add_card(c4);
alice->add_card(c5);


Card ledUp = Card(Card::RANK_QUEEN,Card::SUIT_HEARTS);

Card played = alice->play_card(ledUp,Card::SUIT_CLUBS);

ASSERT_EQUAL(played,c5);




 delete alice;


}

//not same suit 
//cant follow

TEST(playCardNS2){

 Player * alice = Player_factory("Alice", "Simple");
Card c1 = Card(Card::RANK_NINE,Card::SUIT_SPADES);
Card c2 = Card(Card::RANK_TEN,Card::SUIT_SPADES);
Card c3 = Card(Card::RANK_JACK,Card::SUIT_SPADES);
Card c4 = Card(Card::RANK_KING,Card::SUIT_HEARTS);
Card c5 = Card(Card::RANK_ACE,Card::SUIT_HEARTS);


alice->add_card(c1);
alice->add_card(c2);
alice->add_card(c3);
alice->add_card(c4);
alice->add_card(c5);


Card ledUp = Card(Card::RANK_QUEEN,Card::SUIT_DIAMONDS);

Card played = alice->play_card(ledUp,Card::SUIT_CLUBS);

ASSERT_EQUAL(played,c1);

 delete alice;


}






// Add more tests here

TEST_MAIN()
