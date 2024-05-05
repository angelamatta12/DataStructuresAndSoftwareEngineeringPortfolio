// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;

Card testCSR = Card(Card::RANK_JACK,Card::SUIT_CLUBS);
Card testDSR = Card(Card::RANK_JACK,Card::SUIT_DIAMONDS);
Card testSSR = Card(Card::RANK_JACK,Card::SUIT_SPADES);
Card testHSR = Card(Card::RANK_JACK,Card::SUIT_HEARTS);

Card testSSJ = Card(Card::RANK_JACK,Card::SUIT_CLUBS);
Card testSSQ = Card(Card::RANK_QUEEN,Card::SUIT_CLUBS);
Card testSSK = Card(Card::RANK_KING,Card::SUIT_CLUBS);
Card testSSA = Card(Card::RANK_ACE,Card::SUIT_CLUBS);

Card testSSR2 = Card(Card::RANK_QUEEN,Card::SUIT_SPADES);

Card testSSDR = Card(Card::RANK_TWO,Card::SUIT_CLUBS);

//popconstructor
TEST(test_card_ctor) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
}

//default constructor
TEST(test_card_ctor_def) {
    Card c = Card();
    ASSERT_EQUAL(Card::RANK_TWO, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, c.get_suit());
}

//get suit for left bower

TEST(test_card_get_suit_left) {
    Card c = Card(Card::RANK_JACK,Card::SUIT_SPADES);

    ASSERT_EQUAL(Card::RANK_JACK, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_CLUBS, c.get_suit(Card::SUIT_CLUBS));

     
}




//isLeftBower

TEST(left_bower){

Card testDY = Card(Card::RANK_JACK,Card::SUIT_DIAMONDS);
Card testDN = Card(Card::RANK_QUEEN,Card::SUIT_DIAMONDS);

//diamonds

 ASSERT_EQUAL(true, testDY.is_left_bower(Card::SUIT_HEARTS));
 ASSERT_EQUAL(false,testDY.is_left_bower(Card::SUIT_SPADES));
 ASSERT_EQUAL(false,testDN.is_left_bower(Card::SUIT_HEARTS));

//spades


Card testSY = Card(Card::RANK_JACK,Card::SUIT_SPADES);
Card testSN = Card(Card::RANK_QUEEN,Card::SUIT_SPADES);

 ASSERT_EQUAL(true, testSY.is_left_bower(Card::SUIT_CLUBS));
 ASSERT_EQUAL(false,testSN.is_left_bower(Card::SUIT_CLUBS));
 ASSERT_EQUAL(false,testSN.is_left_bower(Card::SUIT_HEARTS));


//hearts

Card testHY = Card(Card::RANK_JACK,Card::SUIT_HEARTS);
Card testHN = Card(Card::RANK_QUEEN,Card::SUIT_HEARTS);

 ASSERT_EQUAL(testHY.is_left_bower(Card::SUIT_DIAMONDS),true);
 ASSERT_EQUAL(testHY.is_left_bower(Card::SUIT_CLUBS),false);
 ASSERT_EQUAL(testHN.is_left_bower(Card::SUIT_DIAMONDS),false);


//clubs

Card testCY = Card(Card::RANK_JACK,Card::SUIT_CLUBS);
Card testCN = Card(Card::RANK_QUEEN,Card::SUIT_CLUBS);

 ASSERT_EQUAL(testCY.is_left_bower(Card::SUIT_SPADES),true);
 ASSERT_EQUAL(testCY.is_left_bower(Card::SUIT_DIAMONDS),false);
 ASSERT_EQUAL(testCN.is_left_bower(Card::SUIT_SPADES),false);

    
}

//face,or ace

TEST(face_ace){

Card testJack = Card(Card::RANK_JACK,Card::SUIT_CLUBS);
Card testKing = Card(Card::RANK_KING,Card::SUIT_CLUBS);
Card testQueen = Card(Card::RANK_QUEEN,Card::SUIT_CLUBS);
Card testAce = Card(Card::RANK_ACE,Card::SUIT_CLUBS);
Card testNone = Card(Card::RANK_TWO,Card::SUIT_CLUBS);


 ASSERT_EQUAL(testJack.is_face_or_ace(),true);
 ASSERT_EQUAL(testKing.is_face_or_ace(),true);
 ASSERT_EQUAL(testQueen.is_face_or_ace(),true);
 ASSERT_EQUAL(testAce.is_face_or_ace(),true);
 ASSERT_EQUAL(testNone.is_face_or_ace(),false);



}



//check if R Bower

TEST(right_bower){

Card testJack = Card(Card::RANK_JACK,Card::SUIT_CLUBS);
ASSERT_EQUAL(testJack.is_right_bower(Card::SUIT_CLUBS),true);

ASSERT_EQUAL(testJack.is_right_bower(Card::SUIT_DIAMONDS),false);

}




//check if trump

TEST(trump){

Card testJack = Card(Card::RANK_JACK,Card::SUIT_CLUBS);

//left bower
ASSERT_EQUAL(testJack.is_trump(Card::SUIT_CLUBS),true);

//right bower
ASSERT_EQUAL(testJack.is_trump(Card::SUIT_SPADES),true);


//isnt
ASSERT_EQUAL( testJack.is_trump(Card::SUIT_DIAMONDS),false);




}




TEST(equal_nonequal){

//same rank

//spades
ASSERT_EQUAL(true,(testSSR != testHSR));
ASSERT_EQUAL(true,(testSSR != testDSR));
ASSERT_EQUAL(true,(testSSR != testCSR));
ASSERT_EQUAL(true,(testSSR == testSSR));

ASSERT_EQUAL(false,(testSSR != testSSR));
ASSERT_EQUAL(false,(testSSR == testHSR));
ASSERT_EQUAL(false,(testSSR == testDSR));
ASSERT_EQUAL(false,(testSSR == testCSR));




//hearts
ASSERT_EQUAL(true,(testHSR != testDSR));
ASSERT_EQUAL(true,(testHSR != testCSR));

ASSERT_EQUAL(true,(testHSR != testSSR));

ASSERT_EQUAL(false,(testHSR == testCSR));
ASSERT_EQUAL(false,(testHSR == testDSR));
ASSERT_EQUAL(false,(testHSR == testSSR));
ASSERT_EQUAL(false,(testHSR != testHSR));
ASSERT_EQUAL(true,(testHSR == testHSR));


//clubs
ASSERT_EQUAL(true,(testCSR != testDSR));

ASSERT_EQUAL(false,(testCSR != testCSR));
ASSERT_EQUAL(true,(testCSR == testCSR));
ASSERT_EQUAL(true,(testCSR != testDSR));
ASSERT_EQUAL(true,(testCSR != testHSR));
ASSERT_EQUAL(true,(testCSR != testSSR));

//diamonds
ASSERT_EQUAL(true,(testDSR != testSSR));
ASSERT_EQUAL(true,(testDSR != testHSR));
ASSERT_EQUAL(true,(testDSR != testCSR));

ASSERT_EQUAL(true,(testDSR == testDSR));
ASSERT_EQUAL(false,(testDSR != testDSR));
ASSERT_EQUAL(false,(testDSR == testSSR));
ASSERT_EQUAL(false,(testDSR == testHSR));
ASSERT_EQUAL(false,(testDSR == testCSR));



//Same suit

//jack
ASSERT_EQUAL(true,(testSSJ != testSSQ));
ASSERT_EQUAL(true,(testSSJ != testSSK));
ASSERT_EQUAL(true,(testSSJ != testSSA));
ASSERT_EQUAL(true,(testSSJ == testSSJ));
ASSERT_EQUAL(false,(testSSJ != testSSJ));
ASSERT_EQUAL(false,(testSSJ == testSSQ));
ASSERT_EQUAL(false,(testSSJ == testSSK));
ASSERT_EQUAL(false,(testSSJ == testSSA));

///king
ASSERT_EQUAL(true,(testSSK != testSSA));

ASSERT_EQUAL(true,(testSSK != testSSQ));
ASSERT_EQUAL(true,(testSSK != testSSJ));

ASSERT_EQUAL(true,(testSSK == testSSK));
ASSERT_EQUAL(false,(testSSK != testSSK));

ASSERT_EQUAL(false,(testSSK == testSSQ));
ASSERT_EQUAL(false,(testSSK == testSSJ));

//queen
ASSERT_EQUAL(true,(testSSQ != testSSJ));
ASSERT_EQUAL(true,(testSSQ != testSSK));
ASSERT_EQUAL(true,(testSSQ != testSSA));

ASSERT_EQUAL(true,(testSSQ == testSSQ));
ASSERT_EQUAL(false,(testSSQ != testSSQ));
ASSERT_EQUAL(false,(testSSQ == testSSK));
ASSERT_EQUAL(false,(testSSQ == testSSA));


//ace

ASSERT_EQUAL(true,(testSSA != testSSK));
ASSERT_EQUAL(true,(testSSA != testSSQ));
ASSERT_EQUAL(true,(testSSA != testSSJ));

ASSERT_EQUAL(true,(testSSA == testSSA));
ASSERT_EQUAL(false,(testSSA != testSSA));
ASSERT_EQUAL(false,(testSSA == testSSK));
ASSERT_EQUAL(false,(testSSA == testSSQ));
ASSERT_EQUAL(false,(testSSA == testSSJ));

//same suit diff rank

ASSERT_EQUAL(true,(testSSA != testSSDR));
ASSERT_EQUAL(false,(testSSA == testSSDR));




}





TEST(less_than_equal_to_greater_than){


//same rank

//spades
ASSERT_EQUAL(true,(testSSR <= testHSR));
ASSERT_EQUAL(true,(testSSR <= testDSR));
ASSERT_EQUAL(true,(testSSR <= testCSR));

ASSERT_EQUAL(true,(testSSR <= testSSR));
ASSERT_EQUAL(true,(testSSR >= testSSR));

ASSERT_EQUAL(false,(testSSR >= testHSR));
ASSERT_EQUAL(false,(testSSR >= testDSR));
ASSERT_EQUAL(false,(testSSR >= testCSR));



//hearts
ASSERT_EQUAL(true,(testHSR <= testDSR));
ASSERT_EQUAL(true,(testHSR <= testCSR));

ASSERT_EQUAL(true,(testHSR >= testSSR));

ASSERT_EQUAL(false,(testHSR >= testCSR));
ASSERT_EQUAL(false,(testHSR >= testDSR));
ASSERT_EQUAL(false,(testHSR <= testSSR));

ASSERT_EQUAL(true,(testHSR <= testHSR));
ASSERT_EQUAL(true,(testHSR >= testHSR));


//clubs
ASSERT_EQUAL(true,(testCSR <= testDSR));

ASSERT_EQUAL(true,(testCSR <= testCSR));
ASSERT_EQUAL(true,(testCSR >= testCSR));

ASSERT_EQUAL(false,(testCSR >= testDSR));
ASSERT_EQUAL(false,(testCSR <= testHSR));
ASSERT_EQUAL(false,(testCSR <= testSSR));

//diamonds
ASSERT_EQUAL(true,(testDSR >= testSSR));
ASSERT_EQUAL(true,(testDSR >= testHSR));
ASSERT_EQUAL(true,(testDSR >= testCSR));

ASSERT_EQUAL(true,(testDSR >= testDSR));
ASSERT_EQUAL(true,(testDSR <= testDSR));

ASSERT_EQUAL(false,(testDSR <= testSSR));
ASSERT_EQUAL(false,(testDSR <= testHSR));
ASSERT_EQUAL(false,(testDSR <= testCSR));



//Same suit

//jack
ASSERT_EQUAL(true,(testSSJ <= testSSQ));
ASSERT_EQUAL(true,(testSSJ <= testSSK));
ASSERT_EQUAL(true,(testSSJ <= testSSA));
ASSERT_EQUAL(true,(testSSJ <= testSSJ));
ASSERT_EQUAL(true,(testSSJ >= testSSJ));

ASSERT_EQUAL(false,(testSSJ >= testSSQ));
ASSERT_EQUAL(false,(testSSJ >= testSSK));
ASSERT_EQUAL(false,(testSSJ >= testSSA));

///king
ASSERT_EQUAL(true,(testSSK <= testSSA));

ASSERT_EQUAL(true,(testSSK >= testSSQ));
ASSERT_EQUAL(true,(testSSK >= testSSJ));

ASSERT_EQUAL(true,(testSSK >= testSSK));
ASSERT_EQUAL(true,(testSSK <= testSSK));

ASSERT_EQUAL(false,(testSSK <= testSSQ));
ASSERT_EQUAL(false,(testSSK <= testSSJ));

//queen
ASSERT_EQUAL(true,(testSSQ >= testSSJ));
ASSERT_EQUAL(true,(testSSQ <= testSSK));
ASSERT_EQUAL(true,(testSSQ <= testSSA));

ASSERT_EQUAL(true,(testSSQ <= testSSQ));
ASSERT_EQUAL(true,(testSSQ >= testSSQ));
ASSERT_EQUAL(false,(testSSQ >= testSSK));
ASSERT_EQUAL(false,(testSSQ >= testSSA));


//ace

ASSERT_EQUAL(true,(testSSA >= testSSK));
ASSERT_EQUAL(true,(testSSA >= testSSQ));
ASSERT_EQUAL(true,(testSSA >= testSSJ));

ASSERT_EQUAL(true,(testSSA >= testSSA));
ASSERT_EQUAL(true,(testSSA <= testSSA));

ASSERT_EQUAL(false,(testSSA <= testSSK));
ASSERT_EQUAL(false,(testSSA <= testSSQ));
ASSERT_EQUAL(false,(testSSA <= testSSJ));

//same suit diff rank


ASSERT_EQUAL(true,(testSSA >= testSSDR));
ASSERT_EQUAL(false,(testSSA <= testSSDR));



}

TEST(less_than_greater_than){


//same rank

//spades
ASSERT_EQUAL(true,(testSSR < testHSR));
ASSERT_EQUAL(true,(testSSR < testDSR));
ASSERT_EQUAL(true,(testSSR < testCSR));

ASSERT_EQUAL(false,(testSSR < testSSR));
ASSERT_EQUAL(false,(testSSR > testSSR));

ASSERT_EQUAL(false,(testSSR > testHSR));
ASSERT_EQUAL(false,(testSSR > testDSR));
ASSERT_EQUAL(false,(testSSR > testCSR));



//hearts
ASSERT_EQUAL(true,(testHSR < testDSR));
ASSERT_EQUAL(true,(testHSR < testCSR));

ASSERT_EQUAL(true,(testHSR > testSSR));

ASSERT_EQUAL(false,(testHSR > testCSR));
ASSERT_EQUAL(false,(testHSR > testDSR));
ASSERT_EQUAL(false,(testHSR < testSSR));

ASSERT_EQUAL(false,(testHSR < testHSR));
ASSERT_EQUAL(false,(testHSR > testHSR));


//clubs
ASSERT_EQUAL(true,(testCSR < testDSR));

ASSERT_EQUAL(false,(testCSR < testCSR));
ASSERT_EQUAL(false,(testCSR > testCSR));

ASSERT_EQUAL(false,(testCSR > testDSR));
ASSERT_EQUAL(false,(testCSR < testHSR));
ASSERT_EQUAL(false,(testCSR < testSSR));

//diamonds
ASSERT_EQUAL(true,(testDSR > testSSR));
ASSERT_EQUAL(true,(testDSR > testHSR));
ASSERT_EQUAL(true,(testDSR > testCSR));

ASSERT_EQUAL(false,(testDSR > testDSR));
ASSERT_EQUAL(false,(testDSR < testDSR));

ASSERT_EQUAL(false,(testDSR < testSSR));
ASSERT_EQUAL(false,(testDSR < testHSR));
ASSERT_EQUAL(false,(testDSR < testCSR));



//Same suit

//jack
ASSERT_EQUAL(true,(testSSJ < testSSQ));
ASSERT_EQUAL(true,(testSSJ < testSSK));
ASSERT_EQUAL(true,(testSSJ < testSSA));
ASSERT_EQUAL(false,(testSSJ < testSSJ));
ASSERT_EQUAL(false,(testSSJ > testSSJ));

ASSERT_EQUAL(false,(testSSJ > testSSQ));
ASSERT_EQUAL(false,(testSSJ > testSSK));
ASSERT_EQUAL(false,(testSSJ > testSSA));

///king
ASSERT_EQUAL(true,(testSSK < testSSA));

ASSERT_EQUAL(true,(testSSK > testSSQ));
ASSERT_EQUAL(true,(testSSK > testSSJ));

ASSERT_EQUAL(false,(testSSK > testSSK));
ASSERT_EQUAL(false,(testSSK < testSSK));

ASSERT_EQUAL(false,(testSSK < testSSQ));
ASSERT_EQUAL(false,(testSSK < testSSJ));

//queen
ASSERT_EQUAL(true,(testSSQ > testSSJ));
ASSERT_EQUAL(true,(testSSQ < testSSK));
ASSERT_EQUAL(true,(testSSQ < testSSA));

ASSERT_EQUAL(false,(testSSQ < testSSQ));
ASSERT_EQUAL(false,(testSSQ > testSSQ));
ASSERT_EQUAL(false,(testSSQ > testSSK));
ASSERT_EQUAL(false,(testSSQ > testSSA));


//ace

ASSERT_EQUAL(true,(testSSA > testSSK));
ASSERT_EQUAL(true,(testSSA > testSSQ));
ASSERT_EQUAL(true,(testSSA > testSSJ));

ASSERT_EQUAL(false,(testSSA > testSSA));
ASSERT_EQUAL(false,(testSSA < testSSA));

ASSERT_EQUAL(false,(testSSA < testSSK));
ASSERT_EQUAL(false,(testSSA < testSSQ));
ASSERT_EQUAL(false,(testSSA < testSSJ));

//same suit diff rank


ASSERT_EQUAL(true,(testSSA > testSSDR));
ASSERT_EQUAL(false,(testSSA < testSSDR));



}


//suit next

TEST(suit_next_test){

ASSERT_EQUAL("Hearts",Suit_next("Diamonds"));
ASSERT_EQUAL("Diamonds",Suit_next("Hearts"));

ASSERT_EQUAL("Spades",Suit_next("Clubs"));
ASSERT_EQUAL("Clubs",Suit_next("Spades"));


}



TEST(print_card){
std::cout << testDSR;
//standard card

//Card::RANK_JACK,Card::SUIT_DIAMONDS



//bower


}



///NOTE BOWERS ARE THE HIGHEST !!!!!!


TEST(cardless){

//Card::RANK_QUEEN,Card::SUIT_CLUBS

Card QueenHearts = Card(Card::RANK_QUEEN,Card::SUIT_HEARTS);
Card JackHearts = Card(Card::RANK_JACK,Card::SUIT_HEARTS);

ASSERT_EQUAL(Card_less(QueenHearts,JackHearts,Card::SUIT_HEARTS),true);
ASSERT_EQUAL(Card_less(JackHearts,QueenHearts,Card::SUIT_HEARTS),false);
ASSERT_EQUAL(Card_less(testDSR, testSSK, testSSQ,"Clubs"),true);



//cardless

//trump = led

//b trump, a nope
ASSERT_EQUAL(Card_less(testDSR, testSSK, testSSQ,"Clubs"),true);


//a trump, b nope
ASSERT_EQUAL(Card_less(testSSK, testDSR, testSSQ,"Clubs"),false);


//both trump
ASSERT_EQUAL(Card_less(testSSA,  testSSK, testSSQ,"Clubs"),false);



//neither trump 
ASSERT_EQUAL(Card_less(testDSR, testHSR, testSSQ,"Clubs"),false);



//bower 
ASSERT_EQUAL(Card_less(testHSR, testSSR, testSSQ,"Clubs"),true);








//trump != led




//b trump, a nope
ASSERT_EQUAL(Card_less(testSSA, testSSR, testSSQ,"Spades"),true);


//a trump, b nope
ASSERT_EQUAL(Card_less(testSSR, testSSA, testSSQ,"Spades"),false);


//both trump
ASSERT_EQUAL(Card_less(testSSR2, testSSR, testSSQ,"Spades"),true);


//neither trump 
ASSERT_EQUAL(Card_less(testHSR, testDSR, testSSQ,"Spades"),true);


//b led, a nope
ASSERT_EQUAL(Card_less(testHSR, testSSJ, testSSQ,"Spades"),true);

//a led, b nope
ASSERT_EQUAL(Card_less(testSSJ, testHSR, testSSQ,"Spades"),false);


//both led 
ASSERT_EQUAL(Card_less(testSSA, testSSK, testSSQ,"Spades"),false);


//neither led
ASSERT_EQUAL(Card_less(testDSR, testHSR , testSSQ,"Spades"),false);

//bower 
ASSERT_EQUAL(Card_less(testHSR, testCSR, testSSQ,"Spades"),true);



}










// Add more test cases here

TEST_MAIN()
