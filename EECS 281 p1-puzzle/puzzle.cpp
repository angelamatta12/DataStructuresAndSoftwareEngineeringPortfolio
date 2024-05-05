// Project Identifier: A8A3A33EF075ACEF9B08F5B9845569ECCB423725
#include <iostream>
#include <getopt.h>
#include<ctype.h>
#include <vector> 
#include <deque>
#include <string>
#include <utility>
#include <cstring>

//section for checking numColor,width and height
void checkBigThree( bool numColor, bool width, bool height){

if(numColor){
    //error
    std::cerr<<"Error: Invalid numColor";
    exit(1);
}

if(height){
    //error
    std::cerr<<"Error: Invalid height";
     exit(1);
}

if(width){
    //error
    std::cerr<<"Error: Invalid width";
    exit(1);
}

}

//section for checking # of targets and start points
void noMultiTarget(char c, bool flag){
bool checkMultTarget = c == '?' && flag;
if(checkMultTarget){
    std::cerr<<"Error: Puzzle must have exactly one start and one target";
    exit(1);
}
}

void noMultiStart(char c, bool flag){
bool checkMultiStart = c == '@' && flag;
if(checkMultiStart){
        std::cerr<<"Error: Puzzle must have exactly one start and one target";
        exit(1);
}
}


//place for player state setting function
//struct
struct playerStateMaze{
int row;
int column;
char space;
};

//for using cout 
std::ostream& operator<<(std::ostream& os, const playerStateMaze& obj)
{
    // write obj to stream
  os<<"("<<obj.space<<", ("<<obj.row<< ", "<<obj.column <<"))"<<"\n";
    return os;
}

//check where used 
bool operator ==(playerStateMaze p1, playerStateMaze p2){
    return (p1.column == p2.column && p1.row == p2.row);

}

//generate possible directions can go to 

//check if valid index
bool checkSpaceIndex(int locRow, int locColumn, int puzzleRowMax, int puzzleColumnMax ){
//valid index
//row must not be out of bounds
//includes the max number too, ie. if width = 4, index values= {0,1,2,3}
if(locRow >= puzzleRowMax||locRow  <= -1 ){
return false;
}
if(locColumn >= puzzleColumnMax||locColumn  <= -1 ){
return false;
}
return true;
}

//validate can go to space aka 
//not wall or closed door
//can go through door
//can check if it's uppercase in the gen search algorithm and then set to lowercase in a temp var
//pass in temp var 
bool validGoThrough(char space, char currentColor){
//go through open door, go through space and button, need to add a portion for pressed vs. it is current color therefore treat as if open space 
//if is start position but color != ^ and not discovered at that color then valid position 
if(((isalpha(space)&&isupper(space)&& tolower(space) == currentColor) 
|| space == '.'
||  space == '^'
|| (isalpha(space)&&islower(space))
||space == '?')
||(space == '@' && currentColor != '^')){
return true;
}
return false;
}

//can press button 
//both lowercase, no need to worry about that in comparison 
bool validButtonPress(char button, char currentColor){
    if(button != currentColor|| (button != currentColor && button =='^')){
        return true;
    }
return false;
}

//not in vector containing all spaces explored 
bool checkIfVector(playerStateMaze currentColor,playerStateMaze upcomingState, std::vector<std::vector<std::vector<char>>> discovered){
    //does have character with direction, or has '@', '?', '^'
    //TODO handle the possibility that upcoming.space color index could be '^'
    //static_cast<uint32_t>((upcomingState.space) - 'a') + 1
if(currentColor.space =='^'){
    if(isalpha(discovered[0][static_cast<uint32_t>(upcomingState.row)][static_cast<uint32_t>(upcomingState.column)])||
discovered[0][static_cast<uint32_t>(upcomingState.row)][static_cast<uint32_t>(upcomingState.column)] =='@'||
discovered[0][static_cast<uint32_t>(upcomingState.row)][static_cast<uint32_t>(upcomingState.column)] == '^' ){
    return false;
}
}
else{
    //TODO fix color 
if(isalpha(discovered[static_cast<uint32_t>((currentColor.space) - 'a' + 1)][static_cast<uint32_t>(upcomingState.row)][static_cast<uint32_t>(upcomingState.column)])||
discovered[static_cast<uint32_t>((currentColor.space - 'a') + 1)][static_cast<uint32_t>(upcomingState.row)][static_cast<uint32_t>(upcomingState.column)] =='@'||
discovered[static_cast<uint32_t>((currentColor.space - 'a') + 1)][static_cast<uint32_t>(upcomingState.row)][static_cast<uint32_t>(upcomingState.column)] == '^' ){
    return false;
}
}
return true;
}

//once validate space, add to deque based on stack or queue
//do this for NESW generated for the current space
//then grab the next current space and repeat the above 

std::vector<std::pair<int,int>> genDirections(playerStateMaze &pCurrent){
//generate the following
//north/up { <color>, <row - 1>, <col> }
std::pair<int,int> north;
 north.first = pCurrent.column;
 north.second = pCurrent.row -1;

//east/right { <color>, <row>, <col + 1> }
std::pair<int,int> east;
 east.first = pCurrent.column+1;
 east.second = pCurrent.row;

//south/down { <color>, <row + 1>, <col> }
std::pair<int,int> south;
 south.first = pCurrent.column;
 south.second = pCurrent.row+1;

//west/left { <color>, <row>, <col - 1> }
std::pair<int,int> west;
 west.first = pCurrent.column-1;
 west.second = pCurrent.row;

 std::vector<std::pair<int,int>> possibleDirections = {north,east,south,west};
  return possibleDirections;
 }


bool validDirection(std::pair<int,int> possibleDirections,int maxRow, int maxColumn, playerStateMaze &pCurrent, 
std::vector<std::vector<std::vector<char>>> &discovered, bool searchFlag, std::deque<playerStateMaze> &search, std::vector<std::vector<char>> puzzle,
char direction, int &lastRow, int &lastColumn
){

//validate that I can go there and add it to the search container 
//make sure that the space I am standing on is not a target first 
bool flag = false;
//create a temp state based on the upcoming direction 
playerStateMaze upComing;
//for printing out when I do list out put, coordinates and current color 
upComing.column = possibleDirections.first;
upComing.row = possibleDirections.second;


//check if it's a valid index 
 if(checkSpaceIndex((possibleDirections.second), (possibleDirections.first), maxRow,maxColumn)){
//create if statement to update this one based on what's up, aka current color 
//TODO update the color index 
upComing.space = pCurrent.space;

//check if the space is not a closed door, not a wall 
if(validGoThrough(puzzle[static_cast<uint32_t>(possibleDirections.second)][static_cast<uint32_t>(possibleDirections.first)],
pCurrent.space)){

if(puzzle[static_cast<uint32_t>(possibleDirections.second)][static_cast<uint32_t>(possibleDirections.first)] == '?'){
    flag = true;
    lastRow = possibleDirections.second;
    lastColumn =possibleDirections.first;
    pCurrent.row = possibleDirections.second;
    pCurrent.column = possibleDirections.first;
   if(pCurrent.space =='^'){
    discovered[0][static_cast<uint32_t>( pCurrent.row )][static_cast<uint32_t>( pCurrent.column )] = direction;
   }
   else{
    //TODO fix color 
    discovered[static_cast<uint32_t>((pCurrent.space) - 'a') + 1][static_cast<uint32_t>(pCurrent.row )][static_cast<uint32_t>(pCurrent.column)] = direction;
   }
    return flag;
}


//check to make sure that the space is not something that has already been discovered
if(checkIfVector(pCurrent,upComing, discovered)){
    // //check if upComing.space is an '^' or not, might need a function for this 
    // //then have it so that it uses the appropriate things !! 
    //mark the direction we traveled to in the bactrace for every space we discover
    if(isalpha(pCurrent.space)&&islower(pCurrent.space)){
        
        discovered[static_cast<uint32_t>((pCurrent.space) - 'a') + 1][static_cast<uint32_t>(upComing.row)][static_cast<uint32_t>(upComing.column)] = direction;
        //add to search container
if(searchFlag){
    search.push_front(upComing);
}
else{
    search.push_back(upComing);
}
    }
    else{
       discovered[0][static_cast<uint32_t>(upComing.row)][static_cast<uint32_t>(upComing.column)] = direction;
       //add to search container
if(searchFlag){
    search.push_front(upComing);
}
else{
    search.push_back(upComing);
}
    }

}
}
}
return flag;
}

void goBackNESW(playerStateMaze &pCurrent, char direction){


//north/up { <color>, <row - 1>, <col> }
//east/right { <color>, <row>, <col + 1> }
//south/down { <color>, <row + 1>, <col> }
//west/left { <color>, <row>, <col - 1> }

switch(direction){

case 'N':
(pCurrent.row)++;
break;

case 'E':
(pCurrent.column)--;
break;

case 'S':
(pCurrent.row)--;
break;

case 'W' :
(pCurrent.column)++;
break;

}

}

void printList(std::vector<std::vector<std::vector<char>>> visitedBacktrace, playerStateMaze &pLastAtTarget){

//grab the location where the target is 
//check the direction listed 
playerStateMaze temp;
temp.row = pLastAtTarget.row;
temp.column = pLastAtTarget.column;
//this is the last color, not the space that the player landed on (in this case '?')
temp.space = pLastAtTarget.space;
size_t colorLayerNumber;

std::vector<playerStateMaze> listPrint;

//based on direction listed do the math to get the previous space you were on 
//ARRGGHHHH, need to use the '^' or cast character :(((
    if(temp.space == '^'){
        colorLayerNumber = 0; 
    }
    else{
        colorLayerNumber = static_cast<uint32_t>((temp.space) - 'a') + 1;
    }

while(visitedBacktrace[colorLayerNumber][static_cast<uint32_t>(temp.row)][static_cast<uint32_t>(temp.column)] != '@'){
    std::vector<playerStateMaze>::iterator it;
    it = listPrint.begin();
    it = listPrint.insert ( it , temp );
//color stuff
//check if the space at those coordinates with the current color  has a different color 
//look in bactrace to see if at that space with the current color if == button or ^ then do the button things backwards 
if(visitedBacktrace[colorLayerNumber][static_cast<uint32_t>(temp.row)][static_cast<uint32_t>(temp.column)] == '^'|| (isalpha(visitedBacktrace[colorLayerNumber][static_cast<uint32_t>(temp.row)][static_cast<uint32_t>(temp.column)]) && islower(visitedBacktrace[colorLayerNumber][static_cast<uint32_t>(temp.row)][static_cast<uint32_t>(temp.column)]))){
//yes 
    temp.space = visitedBacktrace[colorLayerNumber][static_cast<uint32_t>(temp.row)][static_cast<uint32_t>(temp.column)];
 
 if(visitedBacktrace[colorLayerNumber][static_cast<uint32_t>(temp.row)][static_cast<uint32_t>(temp.column)] == '^'){
        colorLayerNumber = 0; 
    }
    else{
        colorLayerNumber = static_cast<uint32_t>(visitedBacktrace[colorLayerNumber][static_cast<uint32_t>(temp.row)][static_cast<uint32_t>(temp.column)] - 'a') + 1;
    }

//use continue to start the loop over again 
continue;
}
// direction stuff 
//check what direction is listed 
//math was done to get here, undo the math to get back 
goBackNESW(temp,visitedBacktrace[colorLayerNumber][static_cast<uint32_t>(temp.row)][static_cast<uint32_t>(temp.column)]);
}

 temp.space = '^';
 std::vector<playerStateMaze>::iterator it;
    it = listPrint.begin();
    it = listPrint.insert ( it , temp );

for(playerStateMaze s:listPrint){
std::cout<< s;
}

}

using namespace std;

int main(int argc, char *argv[]) {
std::ios_base::sync_with_stdio(false);

std::pair<char,int> defaultIndexColor;
defaultIndexColor.first ='^';
defaultIndexColor.second= 0;

struct option longOpts[] = {
{ "stack", no_argument, NULL, 's' },
{ "queue", no_argument, NULL, 'q' },
{ "output", required_argument, NULL, 'o' },
{ "help", no_argument, NULL, 'h' },
{nullptr,0,nullptr,'\0'},
};

opterr = false;

//use for saving the output type if specified 
char *outputArg = nullptr;
int opt = 0, index = 0;
bool stackCheck = false;
bool queueCheck = false;

while ((opt = getopt_long(argc, argv, "sqo:h", longOpts, &index)) != -1) {
    switch (opt) {
//stack check 
        case 's':
          if(queueCheck || stackCheck){
            //throw error 
            std::cerr<<"Error: Can not have both stack and queue";
            exit(1);
          }
            stackCheck = true;
            break;

//queue check 
        case 'q':
            if(queueCheck || stackCheck){
            //throw error 
                std::cerr<<"Error: Can not have both stack and queue";
                exit(1);
            }
                queueCheck = true;
                break;

//output check 
        case 'o':
        //validate what is optarg first 
            if( strcmp(optarg,"map") != 0  &&  strcmp(optarg,"list") != 0){
            //break it, throw error, check if this one work 
                std::cerr<<"Error: Invalid output mode";
                exit(1);
                }
                outputArg = optarg;
                break;

//may need to alter this one. cout being used to write to file!!! 
        case 'h':
            cout << "You want help? This program accepts:\n";
            cout << " -s, --stack or -q, --queue only one maybe present and is required \n";
            cout << " -o, --output ARG This choice needs an argument either list or map, if specified \n";
            cout << " -h, --help This help page\n";
            exit(0);
            break;

        default:
//throw an error 
        std::cerr<<"Error: Unknown option";
        exit(1);
} // switch
} // while


if(!stackCheck){
    if(!queueCheck){
        std::cerr<<"Error: Must have at least one of stack or queue";
        exit(1);
    }
}


//populate deque and 2D vector section
uint32_t numColors;
int width;
int height;

std::cin>> numColors >> height >> width;
bool numColorCheck = numColors>26;
bool widthCheck = width < 1;
bool heightCheck = height < 1; 

checkBigThree(numColorCheck,widthCheck,heightCheck);

char placeholder;
bool hasTarget = false;
bool hasStart = false;
int rowNumber = 0;
int columnNumber = 0; 

//search container
deque<playerStateMaze> searchContainer;

//actual puzzle
//use a 2D vector with value as color 
vector < vector < char > > puzzle(static_cast<uint32_t>(height), vector< char >(static_cast<uint32_t>(width),' '));

//3D vector contains already discovered places 
//vector<vector<vector<char>> >visitedBacktrace;

char maxLetter =  static_cast<char>('a' + numColors - 1);
uint32_t maxNumberColor = static_cast<uint32_t>((tolower(maxLetter)) - 'a') + 2;

vector<vector<vector<char>>> visitedBacktrace(static_cast<uint32_t>(maxNumberColor), vector<vector<char>>(static_cast<uint32_t>(height), vector<char>(static_cast<uint32_t>(width))));

std::string tossComment;

//player state
playerStateMaze playerState;

bool findAllCommentsFlag = true;

//check if the get rid of 
//cin into selected data type
while(std::cin>>placeholder){

//keep track of row and column for finding start point 
    if(!(rowNumber< height)){
        rowNumber = 0;
    }

   if(!(columnNumber < width)){
    columnNumber = 0;
    rowNumber++;
   }

//possible pain point argh
   while(findAllCommentsFlag){
if(placeholder == '/'){

    getline(cin,tossComment);
    if( (tossComment.substr(0,1) ) == "/"){
       std::cin>>placeholder;
    }
}
else{
findAllCommentsFlag = false;
}
   }

//check for invalid puzzle section 

if(placeholder == '@'||placeholder == '?'){
//multi target and multi starts 
noMultiStart(placeholder,hasStart);
noMultiTarget(placeholder,hasTarget);

//need to check to ensure this isnt local aka this actually changes the flags
if(placeholder == '@'){
    hasStart = true;
    //get start position,save in deque 
    playerState.column = columnNumber;
    playerState.row = rowNumber;
    playerState.space = '^';
    visitedBacktrace[static_cast<uint32_t>(defaultIndexColor.second)][static_cast<uint32_t>(rowNumber)][static_cast<uint32_t>(columnNumber)] = '@';
    searchContainer.push_back(playerState);
}
else{
    hasTarget = true;
}
}

//check no over the amount of numColors

//calc based on numColors what the max character allowed is, min char is always A 
// compare the last stored char in question to the max character with compareTo
// need to ensure what exactly compareTo is, ensure the number outputted is not greater than numColors
//less than 0 allowed, using compare, that tells me it comes before the max char 

//if above happens aka invalid character, throw error 
//need to see how to handle upper and lower case, suggestion save the last thing 
//in a temp var, same with the conversion for the max var then toLower, then compare and throw error 

if(isalpha(placeholder)){
    
    //char lowComp = static_cast<char>('a' + numColors -1);
    uint32_t currentLetterNum =  static_cast<uint32_t>((tolower(placeholder)) - 'a') + 1;
    if(currentLetterNum > numColors){
       std::cerr << "Error: Invalid door in map";
       exit(1);
    }
    
}

else{
//check if character in the first place is a valid one aka after all these, check if 
//. or ^
if(placeholder != '.' && placeholder != '^' && placeholder != '#' && placeholder != '@' && placeholder != '?'){
    std::cerr <<"Error: Invalid character in map \n";
    exit(1);
}

}

puzzle[static_cast<uint32_t>(rowNumber)][static_cast<uint32_t>(columnNumber)] = placeholder;

columnNumber++;
}

bool searchValid = false;
int lastRow = 0;
int lastColumn = 0;
    while(!searchContainer.empty()){
//grab the "next" value in the search container and use it for the next steps  
          playerStateMaze temp;
         temp = searchContainer.back();
         searchContainer.pop_back();
//dont change the color, that is for the button presses! 
           playerState.column = temp.column;
           playerState.row = temp.row;
           playerState.space = temp.space;

//check if standing on a button and do button stuff first 
//if standing on a button 
if((islower(puzzle[static_cast<uint32_t>(playerState.row)][static_cast<uint32_t>(playerState.column)])
&&isalpha(puzzle[static_cast<uint32_t>(playerState.row)][static_cast<uint32_t>(playerState.column)]))|| 
puzzle[static_cast<uint32_t>(playerState.row)][static_cast<uint32_t>(playerState.column)] == '^'){
//check if it is a button that can be pressed, other wise it gets treated as an open space(same color as current color)
    playerStateMaze temp;
    temp.row = playerState.row;
    temp.column = playerState.column;
    //could be a ^ or letter
    temp.space = puzzle[static_cast<uint32_t>(playerState.row)][static_cast<uint32_t>(playerState.column)];
    size_t colorLayerNumber;
    if(isalpha(temp.space)){
        colorLayerNumber =  static_cast<uint32_t>(temp.space - 'a') + 1;
    }
    else{
        colorLayerNumber=0;
    }

if(validButtonPress(puzzle[static_cast<uint32_t>(playerState.row)][static_cast<uint32_t>(playerState.column)], playerState.space)
&& !isalpha(visitedBacktrace[colorLayerNumber][static_cast<uint32_t>(temp.row)][static_cast<uint32_t>(temp.column)])&& visitedBacktrace[static_cast<uint32_t>(colorLayerNumber)][static_cast<uint32_t>(temp.row)][static_cast<uint32_t>(temp.column)]!='^'){

//check if '^' or alphanumeric(letter)
//add to visited and to search container then have the loop start another round 
if(puzzle[static_cast<uint32_t>(playerState.row)][static_cast<uint32_t>(playerState.column)] == '^'){
visitedBacktrace[static_cast<uint32_t>(defaultIndexColor.second)][static_cast<uint32_t>(playerState.row)][static_cast<uint32_t>(playerState.column)] = playerState.space;
}
else{
    //cast playerState.space to int for the index, when doing bactrace, any position that holds a character
    //should save character in separate var to chang to int then using the casted char as the index, look up the direction 
    // that we traveled to get to spot 
    //TODO fix color 
visitedBacktrace[static_cast<uint32_t>((puzzle)[static_cast<uint32_t>(playerState.row)][static_cast<uint32_t>(playerState.column)] - 'a') + 1][static_cast<uint32_t>(playerState.row)][static_cast<uint32_t>(playerState.column)] = playerState.space;
}
if(queueCheck){
           searchContainer.push_front(temp);
          }
       else{
           searchContainer.push_back(temp);
       }
//after the button press, have the loop start all over again 
    continue;
}
else{
    if(isalpha(visitedBacktrace[colorLayerNumber][static_cast<uint32_t>(temp.row)][static_cast<uint32_t>(temp.column)])
    && isupper(visitedBacktrace[colorLayerNumber][static_cast<uint32_t>(temp.row)][static_cast<uint32_t>(temp.column)])){

       temp = searchContainer.back();
         searchContainer.pop_back();
//dont change the color, that is for the button presses! 
           playerState.column = temp.column;
           playerState.row = temp.row;
           playerState.space = temp.space;
    }
}
}

//if space is button and matches currentColor do NESW, in all other cases where not standing on button do NESW 
//if standing on button whose space has already been discovered, need to start the loop all over again  

        //generate possible directions 
          std::vector<std::pair<int,int>> possibleDirections = genDirections(playerState);
          std::vector<char> direction = {'N','E', 'S', 'W'};
         //validate each direction, all valid directions are to be put into the search container and the discover container
         size_t count = 0;
         bool flagFound = false;
         while(count < possibleDirections.size() && !flagFound){
          flagFound = validDirection(possibleDirections[count],height, width,playerState,visitedBacktrace, queueCheck, searchContainer,puzzle,direction[count],lastRow,lastColumn);
         count++;
         }
         if(flagFound){
            searchValid = true;
            break;
         }
}
     if (searchValid)
     {
        if(strcmp(outputArg,"map")==0){
           
        }
        else{
            printList(visitedBacktrace,playerState);
        }
     }
     else{
        std::cout<<"No solution. \n Discovered:";
        for(size_t row = 0; row< static_cast<uint32_t>(height); row++){
           for(size_t column = 0; column< static_cast<uint32_t>(width); column++){
             std::cout<< puzzle[row][column];
           }
            std::cout<< "\n";
        }
     }



return 0;
} // main()
