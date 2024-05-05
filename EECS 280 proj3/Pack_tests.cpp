// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Pack.h"
#include "unit_test_framework.h"
#include<fstream>
#include <iostream>

using namespace std;

TEST(test_pack_default_ctor) {
    Pack pack;
    Card first = pack.deal_one();
    ASSERT_EQUAL(Card::RANK_NINE, first.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, first.get_suit());
}


TEST(test_shuffle){

std::string packFile = "Pack.in";

Pack pack;

std::ifstream fin;

fin.open(packFile);

if(!fin.is_open()){
std::cout <<"read" <<std::endl;
std::cout <<"error opening file" << packFile <<std::endl;
}

pack = Pack(fin);

fin.close();

for(int i = 0; i< 20; i++){
 pack.shuffle();
}

 Card first = pack.deal_one();

    ASSERT_EQUAL(Card::RANK_NINE, first.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, first.get_suit());


}



// Add more tests here

TEST_MAIN()
