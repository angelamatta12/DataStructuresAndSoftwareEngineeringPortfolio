/* stats_tests.cpp
 *
 * Unit tests for the simple statistics library
 * Project UID 5366c7e2b77742d5b2142097e51561a5
 *
 * EECS 280 Project 1
 *
 * Protip #1: Write tests for the functions BEFORE you implement them!  For
 * example, write tests for median() first, and then write median().  It sounds
 * like a pain, but it helps make sure that you are never under the illusion
 * that your code works when it's actually full of bugs.
 *
 * Protip #2: Instead of putting all your tests in main(),  put each test case
 * in a function!
 */


#include "stats.h"
#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>
using namespace std;

void test_sum_small_data_set();
void testSummarize();
void testCount();
void testMean();
void testMedian();
void testMode();
void testMin();
void testMax();
void testStd();
// void testStd1();
void testPercent();



// Add prototypes for you test functions here.

int main() {
  test_sum_small_data_set();
  // Call your test functions here
   testSummarize();
    testCount();
    testMean();
    testMedian();
    testMode();
    testMin();
    testMax();
   testStd();
  //  testStd1();
  testPercent();


  return 0;
}

void test_sum_small_data_set() {
 cout << "test_sum_small_data_set" << endl;

 vector<double> data;
 data.push_back(1);
 data.push_back(2);
  data.push_back(3);

 assert(sum(data) == 6);

  cout << "PASS!" << endl;
}

// Add the test function implementations here.

//test if function inserts vector appropriately 
//note, 
void testSummarize() {
vector <vector <double> > vect0;

vector <double> addVec;

vector<double> vect1;

vect1.push_back(3);
vect1.push_back(2);
vect1.push_back(1);
vect1.push_back(4);
vect1.push_back(2);
vect1.push_back(3);
vect1.push_back(1);
vect1.push_back(2);

addVec.push_back(1);
addVec.push_back(2);

vect0.push_back(addVec);

addVec.clear();



addVec.push_back(2);
addVec.push_back(3);

vect0.push_back(addVec);

addVec.clear();



addVec.push_back(3);
addVec.push_back(2);

vect0.push_back(addVec);

addVec.clear();




addVec.push_back(4);
addVec.push_back(1);

vect0.push_back(addVec);

addVec.clear();



summarize(vect1);






cout << "PASS!" << endl;


}



//test count 

void testCount() {


vector<double> vect1;

vect1.push_back(3);
vect1.push_back(2);
vect1.push_back(1);
vect1.push_back(4);
vect1.push_back(2);
vect1.push_back(3);
vect1.push_back(1);
vect1.push_back(2);

assert(count(vect1) == 8 );




}




void testMean() {
vector<double> vect0;

vector<double> vect1;

vect1.push_back(3);
vect1.push_back(2);
vect1.push_back(1);
vect1.push_back(4);
vect1.push_back(2);
vect1.push_back(3);
vect1.push_back(1);
vect1.push_back(2);

assert(mean(vect1) == 2.25 );




}


void testMedian() {
vector<double> vect0;

vector<double> vect1;

vect1.push_back(3);
vect1.push_back(2);
vect1.push_back(1);
vect1.push_back(4);
vect1.push_back(2);
vect1.push_back(3);
vect1.push_back(1);
vect1.push_back(2);

assert(median(vect1) == 2);

//yes 


//odd number test case 

vect0.push_back(2);
vect0.push_back(1);
vect0.push_back(4);
vect0.push_back(2);
vect0.push_back(3);
vect0.push_back(1);
vect0.push_back(2);

assert(median(vect0)== 2);

vector<double> testMed;

testMed.push_back(3);

assert(median(testMed)==3);

}



void testMode() {
vector<double> vect0;

vector<double> vect1;

vect1.push_back(3);
vect1.push_back(2);
vect1.push_back(1);
vect1.push_back(4);
vect1.push_back(2);
vect1.push_back(3);
vect1.push_back(1);
vect1.push_back(2);

assert(mode(vect1) == 2);
cout << "PASS!" << endl;

//tie case 
vect1.push_back(5);
vect1.push_back(1);
vect1.push_back(2);
vect1.push_back(3);
vect1.push_back(4);
vect1.push_back(3);
vect1.push_back(4);

assert(mode(vect1) == 3);
cout << "PASS!" << endl;




vector<double> testMed;

testMed.push_back(3);

assert(mode(testMed)==3);



}





void testMin() {
vector<double> vect0;

vector<double> vect1;

vect1.push_back(3);
vect1.push_back(2);
vect1.push_back(1);
vect1.push_back(4);
vect1.push_back(2);
vect1.push_back(3);
vect1.push_back(1);
vect1.push_back(2);

assert(min(vect1) == 1);
cout << "PASS!" << endl;



}




void testMax() {
vector<double> vect0;

vector<double> vect1;

vect1.push_back(3);
vect1.push_back(2);
vect1.push_back(1);
vect1.push_back(4);
vect1.push_back(2);
vect1.push_back(3);
vect1.push_back(1);
vect1.push_back(2);

assert(max(vect1) == 4);
cout << "PASS!" << endl;



}




void testStd() {
vector<double> vect0;

vector<double> vect1;

const double epsilon = 0.00001;

vect1.push_back(3);
vect1.push_back(2);
vect1.push_back(1);
vect1.push_back(4);
vect1.push_back(2);
vect1.push_back(3);
vect1.push_back(1);
vect1.push_back(2);


double valCheck = (stdev(vect1) - 1.0350983390135);


if (abs(valCheck) < epsilon) {
    cout << "equal" << endl;

  } 
  else {
    cout << "not equal" << endl;
  }






}




void testPercent(){

  vector <double> testSingle;

vector<double> vect1;

vect1.push_back(3);
vect1.push_back(2);
vect1.push_back(1);
vect1.push_back(4);
vect1.push_back(5);
vect1.push_back(6);


//0th percent 

assert(percentile(vect1,0) == 1);

//100th percent

assert(percentile(vect1, 1) == 6);


//0.25

assert(percentile(vect1, 0.25) == 2.25);

//0.5

assert(percentile(vect1, 0.5) == 3.5);

//0.75


assert(percentile(vect1, 0.75) == 4.75);




//single element 

testSingle.push_back(1);


//0th percent 

assert(percentile(testSingle,0) == 1);

//100th percent

assert(percentile(testSingle, 1) == 1);


// //0.25

assert(percentile(testSingle, 0.25) == 1);

// //0.5

assert(percentile(testSingle, 0.5) == 1);

// //0.75

assert(percentile(testSingle, 0.75) == 1);




}