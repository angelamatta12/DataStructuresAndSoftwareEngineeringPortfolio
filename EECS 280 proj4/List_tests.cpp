// Project UID c1f28c309e55405daf00c565d57ff9ad

#include "List.h"
#include "unit_test_framework.h"

using namespace std;

// Add your test cases here

TEST(test_stub) {
    // Add test code here
    ASSERT_TRUE(true);
}

//test size with default constructor
//nothing in it 
TEST(def_empty) {
    // Add test code here
    List<int> b;
    ASSERT_TRUE(b.empty());
}

//test size with default constructor
//one thing in it 

//pushback
TEST(def_1item_pushback) {
    // Add test code here
    List<int> b;
    b.push_back(42);
    ASSERT_EQUAL(b.front(),42);
    ASSERT_EQUAL(b.back(),42);
    b.clear();
    ASSERT_TRUE(b.empty());


}


//push front
TEST(def_1item_pushfront) {
    // Add test code here
    List<int> b;
    b.push_front(42);
    ASSERT_EQUAL(b.front(),42);
    ASSERT_EQUAL(b.back(),42);
    b.clear();
    ASSERT_TRUE(b.empty());

}



//two things 

TEST(def_2item_pushback) {
    // Add test code here
    List<int> b;
    b.push_back(42);
    b.push_back(24);
    ASSERT_EQUAL(b.front(),42);
    ASSERT_EQUAL(b.back(),24);
    b.clear();
    ASSERT_TRUE(b.empty());


}


TEST(def_2item_pushfront) {
    // Add test code here
    List<int> b;
    b.push_front(42);
    b.push_front(24);
    ASSERT_EQUAL(b.front(),24);
    ASSERT_EQUAL(b.back(),42);
    b.clear();
    ASSERT_TRUE(b.empty());

}

//delete the one thing to make it empty
TEST(def_1item_delete_using_pback){
    List<int> b;
    b.push_front(42);
    b.pop_back();
    ASSERT_TRUE(b.empty());


}

TEST(def_1item_delete_using_pfront){
    List<int> b;
    b.push_front(42); 
    b.pop_front();
    ASSERT_TRUE(b.empty());

}


//delete the two things to make it empty 

TEST(def_2item_delete_using_pback){
    List<int> b;
    b.push_front(42);
    b.push_front(42);
    b.pop_back();
    ASSERT_FALSE(b.empty());
    b.pop_back();
    ASSERT_TRUE(b.empty());


}

TEST(def_2item_delete_using_pfront){
    List<int> b;
    b.push_front(42); 
    b.push_front(42); 
    b.pop_front();
    ASSERT_FALSE(b.empty());
    b.pop_back();
    ASSERT_TRUE(b.empty());
   

}

//size check 

TEST(def_3item_size_check){
    List<int> b;
    b.push_front(42); 
    b.push_front(42); 
    b.push_front(42); 
    ASSERT_EQUAL(b.size(),3);

//checks for 2 
    b.pop_front();
    ASSERT_EQUAL(b.size(),2);

//checks for 1
    b.pop_back();
    ASSERT_EQUAL(b.size(),1);

//checks for empty
    b.pop_back();
    ASSERT_EQUAL(b.size(),0);
    ASSERT_TRUE(b.empty());
   

}




//using front and back to 
//reassign datum 

TEST(reassign_datum_front_1item){

    List<int> b;
    b.push_front(42); 
    b.front() = 33;
    ASSERT_EQUAL(b.front(),33);
    ASSERT_EQUAL(b.front(),33);
   

}



TEST(reassign_datum_back_1item){

    List<int> b;
    b.push_front(42); 
    b.back() = 33;
    ASSERT_EQUAL(b.back(),33);
    ASSERT_EQUAL(b.front(),33);
   
}

//2 items

TEST(reassign_datum_front_2item){

 List<int> b;
 b.push_back(3);
 b.push_back(90);
 b.back()= 38;
 b.front()=69;
 ASSERT_EQUAL(b.back(),38);
 ASSERT_EQUAL(b.front(),69);


}

//copy constr

TEST(copy_pop){
List<int> a;
a.push_back(4);
a.push_back(5);
a.push_back(3);
List<int>b(a);

ASSERT_EQUAL(a.front(),b.front());
ASSERT_EQUAL(a.back(),b.back());

 List<int>::Iterator iter = a.begin();
 List<int>::Iterator iter1 = b.begin();

++iter;
++iter1;
ASSERT_EQUAL(*iter,*iter1);

}

//clear tests

TEST(clear_vals){

List<int> a;
a.push_back(4);
a.push_back(5);
a.push_back(3);

a.clear();
ASSERT_EQUAL(a.empty(),true);

}



//overloaded assign test


TEST(copy_pop2){
List<int> a;
a.push_back(4);
a.push_back(5);
a.push_back(3);
List<int>b;

b = a;

ASSERT_EQUAL(a.front(),b.front());
ASSERT_EQUAL(a.back(),b.back());
List<int>::Iterator iter = a.begin();
List<int>::Iterator iter1 = b.begin();

++iter;
++iter1;
ASSERT_EQUAL(*iter,*iter1);


}

//insert test 

//beginning 

TEST(insert_begin){
List<int> a;
a.push_back(4);
a.push_back(5);
a.push_back(3);

List<int>::Iterator iter = a.begin();
int in = 20;
a.insert(iter,in);

ASSERT_EQUAL(a.front(),20);



}

//end 
TEST(insert_end){

List<int> a;
a.push_back(4);
a.push_back(5);
a.push_back(3);

List<int>::Iterator iter = a.end();
int in = 20;
a.insert(iter,in);

ASSERT_EQUAL(a.back(),20);



}

//middle 
TEST(insert_middle){


List<int> a;
a.push_back(4);
a.push_back(5);
a.push_back(3);

List<int>::Iterator iter = a.begin();
++iter;
int in = 20;
a.insert(iter,in);

//second element is 20 confirmed by 
//cout however why did this one give me an
//all good but the other didnt??
List<int>::Iterator iter2 = a.begin();
++iter2;


ASSERT_EQUAL(*iter2,20);



}

//delete test

//beginning 

TEST(delete_begin){

List<int> a;
a.push_back(4);
a.push_back(5);
a.push_back(3);

List<int>::Iterator iter = a.begin();

a.erase(iter);

ASSERT_EQUAL(a.front(),5);




}


//end 
TEST(delete_end){

List<int> a;
a.push_back(4);
a.push_back(5);
a.push_back(3);

List<int>::Iterator iter = a.end();

a.erase(iter);

ASSERT_EQUAL(a.back(),5);

List<int>::Iterator iter2 = a.begin();
++iter2;

ASSERT_EQUAL(*iter2,5);


}



//middle 
TEST(delete_middle){

List<int> a;
a.push_back(4);
a.push_back(5);
a.push_back(3);

List<int>::Iterator iter = a.begin();
++iter;

a.erase(iter);


List<int>::Iterator iter2 = a.begin();

++iter2;

ASSERT_EQUAL(*iter2,3);

}


//begin and end test iter

TEST(begin_val){

List<int> a;
a.push_back(4);
a.push_back(5);
a.push_back(3);

List<int>::Iterator iter = a.begin();

ASSERT_EQUAL(*iter,a.front());

}



TEST(end_val){
List<int> a;
a.push_back(4);
a.push_back(5);
a.push_back(3);

List<int>::Iterator iter = a.begin();

++iter;
++iter;

ASSERT_EQUAL(*iter,3);

}


//iterator operator

TEST(opEqual){

List<int> a;
a.push_back(4);
a.push_back(5);
a.push_back(3);

List<int>::Iterator iter = a.begin();
List<int>::Iterator iter2 = a.begin();

ASSERT_EQUAL(iter,iter2);
++iter;
--iter;
ASSERT_EQUAL(iter,iter2);

}


TEST(opNEqual){

List<int> a;
a.push_back(4);
a.push_back(5);
a.push_back(3);

List<int>::Iterator iter = a.begin();
++iter;
++iter;
List<int>::Iterator iter2 = a.begin();

  ASSERT_NOT_EQUAL(iter,iter2);

}




TEST_MAIN()
