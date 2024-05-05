// main.cpp
// Project UID 5366c7e2b77742d5b2142097e51561a5
#include "stats.h"
#include "p1_library.h"
#include <iostream>
#include <vector>

using namespace std;
int main() {
 
// //ask for filename
cout << "enter a filename" << endl;


string fileName;

cin >> fileName;




cout << "enter a column name" << endl;

string columnName;

cin >> columnName;



cout<< "reading column " << columnName<<  " from " << fileName << endl;


vector <double> data = extract_column(fileName,columnName);


// //print summary 

// //gets us summary of data, includes frequency for each number
 vector<vector<double> > vectorSummary = summarize(data);

// //seperate data into frequency and values vectors

vector<double> frequencySummary;
vector<double> valueSummary;

 for (int i = 0; i < vectorSummary.size(); i++) {
       for (int j = 0; j < vectorSummary[i].size(); j++){

           if(j == 0){
               valueSummary.push_back(vectorSummary[i][j]);

        
           }

           else{
                 frequencySummary.push_back(vectorSummary[i][j]);
                

           }
         }

    }


cout << "Summary (value: frequency)" << endl;

for(int i = 0 ; i < frequencySummary.size(); i++){

cout << valueSummary[i] << ": " << frequencySummary[i]<< endl;

}



// //print out following stats



cout << "count = " << count(data) << endl;

cout << "sum = " << sum(data) << endl;

cout << "mean = " << mean(data) << endl;

cout << "stdev = " << stdev(data) << endl;

cout <<"median = " <<median(data) << endl;

cout << "mode = " <<mode(data) <<endl;

cout << "min = " << min(data) <<endl;

cout << "max = " <<max(data) << endl;

// //   0th percentile = 6


cout << "  0th percentile = " << percentile(data,0.0) << endl;

// //  25th percentile = 7

cout << " 25th percentile = " << percentile(data,0.25) << endl;

// //  50th percentile = 8

cout << " 50th percentile = " << percentile(data,0.5) << endl;


// //  75th percentile = 9

cout << " 75th percentile = " << percentile(data,0.75) << endl;


// // 100th percentile = 10

cout << "100th percentile = " << percentile(data,1) << endl;





}

