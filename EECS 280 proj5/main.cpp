// Project UID db1f506d06d84ab787baf250c265e24e

#include <sstream> 
#include <utility>
#include <iostream>
#include <cassert> //assert
#include <cstddef> //NULL
#include <algorithm>
#include <set>
#include <map>
#include <cmath>
#include <string>
#include "csvstream.h"

using namespace std;

  set<string> unique_words(const std::string &str) {
  istringstream source(str);
  set<string> words;
  string word;
  while (source >> word) {
    words.insert(word);
  }
  return words;
}


class Classifier {
private:


//  total number of posts in training set.
int numPosts;

//  number of unique words in training set. (The vocabulary size.)
int vocabSize;


//keyword key, number value 
// each word,number of posts in training set contain word.
//pick word, scan posts, find word counter++

map<string,int> keywordMap;

//label key, number value
//each label , number of posts with that label.
//pick label, scan posts, find label counter++

map<string,int> labelMap;

map<pair<string,string>,int> labelWordComMap;

map<pair<string,string>,int> trainContent;

public:
 
  // EFFECTS:  Initializes this classifier to be empty.
  Classifier(csvstream & c){



int lineCount = 0; 

//temp maps
map<string, string> row;

//need to see if this puts anything in 
while(c >> row){

//counts how many posts there are with a certain tag and certain keyword pairs
trainContent[{row["tag"],row["content"]}] += 1;

//every line updates 
//updating label 
//rowtag does not update,
//map value is used not the key for the 
//str 
string str = row["tag"];

//how many posts of a certain category(label)
labelMap[str] += 1;

//use the csvstream ability to 
//extract every line using column 
//name as key jjjj
//put through unique words 
//read through set j
//updating keywords

//get the current row's words in a set instead of one string 
set<string> currentRowContent = unique_words(row["content"]);

//counting how many times
//keyword appears in current Row 

//loop through the set and count how many times a certain keyword appears
for(auto& str:currentRowContent){
    
    //need to double check this line 
    //does the string pass correctly ?? 
    string str2 = str;
    keywordMap[str2] += 1;
    labelWordComMap[{row["tag"],str}] += 1;

}

lineCount++;

}

numPosts = lineCount;
vocabSize = keywordMap.size();

  }

//setter 
void setNumPosts(int num){
numPosts = num;

}

void setVocabSize(int num){
vocabSize = num;

}

///getter
int getNumPosts(){

return numPosts;

}

int getVocabSize(){

return vocabSize;

}
  
int getKeyWordMapSize(){

return keywordMap.size();

}

//for pop keyword map 
//need to check to make sure pass by value 
void updateKeyWordMap(const string & s){

keywordMap[s] += 1;

}

//for pop label map 
void updateLabelMap(const string & s){

labelMap[s] += 1;

}


//for pop label map 
void updateLabelWordComboMap(pair <string,string> s){

labelWordComMap[s] +=1;

}

void printPerfom(int r, int t){

cout<< "performance: " << 
r << 
" / " << t <<
 " posts predicted correctly"
 <<endl;
}

int printTestData(vector<pair<string,double>> p,vector<string> c,
vector<string> a){

cout<<endl;

cout<< "test data:" <<endl;

int vectPos = 0;
int right = 0;

while(vectPos < p.size()){

if(a[vectPos] == p[vectPos].first){
right++;
}

cout<< "  correct = "<< a[vectPos] << ", predicted = " << p[vectPos].first
<<", log-probability score = "<< p[vectPos].second<<endl;

cout << "  content = " << c[vectPos]<< endl;

vectPos++;

cout<<endl;


}

return right;
  
}


//perform calculations 
//calculation 

//loop through the two maps to generate a 
//combo 

//loop through the posts in the test data
//get keywords in posts 
//select possible label 

//first calc uses only label 

//second calc refers to test cases 
//a)check if word exists in training set 
//a) check if word was found in posts with chosen label 
//b) make decision based on that

//calc function

//post words stay same whole time
//R: words in post
//M:nothing
//E: returns the highest likely label and
//it's porbablility

pair<string,double> calculationProbability(set<string> s){

double calcedVals = std::numeric_limits<double>::lowest();
string maxLabel;
vector<double> equationVals;

//grab a label for calc

for (const auto &labelMapPair : labelMap) {

double input = ((double)labelMapPair.second/(double)numPosts);

double labelCalc = log(input);

//double check if it is finding the values correctly 
//for each word, check the following 
for(const auto &str: s){

//a)check if word exists in training set 
if(keywordMap.find(str) != keywordMap.end()){


//b) check if word was found in posts with chosen label 
  //yes 
  if(labelWordComMap.find({labelMapPair.first,str}) != labelWordComMap.end()){

   equationVals.push_back(
    log((double)labelWordComMap[{labelMapPair.first,str}]
    /(double)labelMapPair.second));
  }

  //no 
  else{
   equationVals.push_back(log((double)keywordMap[str]/(double)numPosts));

  }


}
//not in training set 
else{

   equationVals.push_back(log(1.0/(double)numPosts));


}


}

double calcV = labelCalc;


for(double & d: equationVals){

calcV += d;

}

//use this to find the max val 

if(calcedVals < calcV){

calcedVals = calcV;
maxLabel = labelMapPair.first;

}
else if (calcedVals == calcV){

if(maxLabel.compare(labelMapPair.first) < 0){

maxLabel = labelMapPair.first;

}

}

equationVals.clear();

    }

//return most likley label and highest val 
return {maxLabel,calcedVals};

}


//need to use functor 
//allows for usage of 
//one function 
//with the slight 
//differences
void printThings(vector<string> cont,
int testSize,vector<string> actual,
vector<pair<string,double>> pred){

cout<< "trained on " << numPosts << " examples" <<endl;

int right1 = printTestData(pred,cont,
actual);

printPerfom(right1, testSize);

}



void printThingsDebug(string file,vector<string> cont,
vector<string> actual,
vector<pair<string,double>> pred){
cout<< "training data:" <<endl;

map<string,string> reading;
csvstream cRead(file);

while(cRead >> reading){

cout<< "  label = "<< reading["tag"] << ", content = " << reading["content"]<<endl;

  
}

cout<< "trained on " << numPosts << " examples" <<endl;
cout<< "vocabulary size = " << vocabSize <<endl;
cout<<endl;


cout<< "classes:" <<endl;

//loop through label map 

for (const auto &labelPair : labelMap){

double input = ((double)labelPair.second/(double)numPosts);

double labelCalc = log(input);


cout<< "  "<< labelPair.first << ", "
<< labelPair.second
  << " examples, log-prior = "
   << labelCalc <<endl;

}
cout<< "classifier parameters:" <<endl;

for (const auto &labelMapPair : labelWordComMap){

 double logLike =  
 log((double)labelWordComMap[labelMapPair.first]
 /(double)labelMap[labelMapPair.first.first]);

cout<< "  "<< labelMapPair.first.first << ":" << 
labelMapPair.first.second
 << ", count = " << 
 labelWordComMap[labelMapPair.first] 
 <<", log-likelihood = " << 
 logLike <<endl;

}


int right2 = printTestData(pred,cont,
actual);

printPerfom(right2, actual.size());

}


};



int main(int argc, char *argv[]) {

cout.precision(3);

//number 1
// check for all errors 
if(argc!=3 && argc != 4){

cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
return 1;


}

else if(argc == 4 && strcmp(argv[3],"--debug") != 0 ){

cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
return 1;

}

//number 2 
//open training csv file
try{
csvstream cStream(argv[1]);


//number 3
//create classifier obj 
Classifier postClass = Classifier(cStream);

//number 4
// read training csv file
//gather information 
//from csv file for training classifier

//number 5
//store training information 
//using classifier section


//open test data 
//read test data 
//use while loop 
// pass in test data 


map<string, string> row;


csvstream cStreamTest(argv[2]);
vector<pair<string,double>> predictions;
vector<string> actualTags;
vector<string> actualContent;

int numTest = 0;

while(cStreamTest >> row){

set<string> testPostContent = unique_words(row["content"]);
actualContent.push_back(row["content"]);
predictions.push_back(postClass.calculationProbability(testPostContent));
actualTags.push_back(row["tag"]);
numTest++;

}

if(argc == 3){
postClass.printThings(actualContent,numTest,actualTags,predictions);
}

else{

postClass.printThingsDebug(argv[1],actualContent,actualTags,predictions);

}


}

//idk if this is how you do exceptions
catch(csvstream_exception e){

cout << "Error opening file: " << argv[1] << endl;
return 1;

}

return 0;

}
