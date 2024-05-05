// // stats.cpp
// // Project UID 5366c7e2b77742d5b2142097e51561a5
// #include "stats.h"
// #include "p1_library.h"
// #include <cassert>
// #include <vector>
// #include <iostream>   
// #include <cmath>
 

// using namespace std;


// //primary variables
// //summarize function variables

// vector<vector< double> > outVectorSet;

// vector<int> frequency;

// vector<int> value;

// vector<vector<double> > summarize(vector<double> v) {

// assert(!(v.empty()));



// //sort the vector of doubles 

// sort(v);


// //grab value
// for(int i = 0; i < v.size(); i++){ 

// //initialize count everytime to 0  


// int count = 0;
// //check if value exists in values vector 

// //not in values vector
// if( find(value.begin(), value.end(), v[i]) != value.end() ){


// //add it to vector 

// value.push_back(v[i]);

// //loop to count
// for(int j = 0; j < v.size(); j++ ){

// if(v[i] == v[j]){

// count++;

// }


// }

// //add count to frequency vector 

// frequency.push_back(count);

// }



// }




// //create the pairs
//  vector< pair <double,double> > vectPairs;

// //loop through the vector of vectors to get each value that is going to be added to the pairs


//            //gets the row 
//           for (int i = 0; i < value.size(); i++) {

//                     vectPairs.push_back(make_pair(value.at(i),frequency.at(i))); 

//                 }  

// //sort the vector pairs by the value 
// //sort(vectPairs.begin(), vectPairs.end());

// //display the pairs

//  for (int i=0; i<vectPairs.size(); i++)
 
//     {

//         cout << "Hello World" << endl;
//         //   cout << vectPairs[i].first << " " << vectPairs[i].second << endl;
//         //   v.clear();
//         //   v.push_back(vectPairs[i].first);
//         //   v.push_back(vectPairs[i].second);
//         //   outVectorSet.push_back(v);

//     }


// return outVectorSet;


// }





// // int count(vector<double> v) {
// // return v.size();
// // }




// // double sum(vector<double> v) {

// // assert(!(v.empty()));

// // double vectorSum = 0;

// // for(int i = 0; i< v.size();i++){

// // vectorSum += v[i];

// // }
// // return vectorSum;
// // }





// // double mean(vector<double> v) {
// // double vectorMean = 0.0;

// // int meanSum = sum(v);

// // vectorMean = meanSum/count(v);

// // return vectorMean;
// // }






// double median(vector<double> v) {
// //must sort vector to ensure tha
// sort(v);

// if(v.size()%2 != 0){

// return v.at((v.size()/2));

// }

// vector <double> calcMedian;

// calcMedian.push_back(v.at(((v.size()/2)-1)));
// calcMedian.push_back(v.at(((v.size()/2))));


// return mean(calcMedian);
// }






// double mode(vector<double> v){


// //gets us summary of data, includes frequency for each number
// vector<vector<double> > vectorSummary = summarize(v);

// //seperate data into frequency and values vectors

// vector<double> frequencyMode;
// vector<double> valueMode;

//  for (int i = 0; i < vectorSummary.size(); i++) {
//         for (int j = 0; j < vectorSummary[i].size(); j++){

//            if(j == 0){
//                valueMode.push_back(vectorSummary[i][j]);
        
//            }

//            else{

//                   frequencyMode.push_back(vectorSummary[i][j]);

//            }

//         }

//     }

// //grab the largest number in frequency, need to check if there are two largest numbers, if only count worked :( (vector library count not stats.cpp)


// //make copy of frequency vector 
// vector<double> frequencyCopy;
// frequencyCopy = frequencyMode;

// //grab largest val of copy 
// double largestFrequency = max(frequencyCopy);
// vector<int> largeFrequencyList;

// //for checking if there are multiple values with the same frequency 
// for(int i = 0; i < frequencyMode.size();i++ ){

// if(largestFrequency == frequencyMode[i]){

// largeFrequencyList.push_back(i);


// }


// }



// //no need to check if largeFrequency list has size > 1 

// //no then just return the value at that index in values vector

// //yes, then just return the value at the first index listed in the frequency list, with using summarize the list should already be sorted in asc so would be smallest value 

// //either way return first val

// return value[largeFrequencyList[0]];



// }






// double min(vector<double> v) {
    
// //assert(!(v.empty()));

// sort(v);


// return(v.at(0));
// }




// double max(vector<double> v) {

// //assert(!(v.empty()));

// sort(v);


// return(v.at((v.size()-1)));

// }




// double stdev(vector<double> v){

// //first calc mean 

// double meanStdev = mean(v);

// double standardDev = 0.0;

// for(int i = 0; i< v.size();i++){

// standardDev += pow((v[i] - meanStdev), 2);


// }



// return sqrt(standardDev/ v.size());


// }



// double percentile(vector<double> v, double p){


// //sort vector 
// sort(v);

// return 0.0;




// }




