#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include "Matrix.h"
#include "Image.h"
#include "processing.h"
#include <cassert>
#include <string>

 
// Project UID af1f95f547e44c8ea88730dfb185559d

int main(int argc, char *argv[]){
//argc gives number of args passed


if(!(argc ==4 || argc ==5)){

std::cout << "Error, inappropriate input,"
<< "please input the correct number of arguments"<< std::endl;

return 1;
}



std::stringstream stringToFile;
//first get the name of file being read 

std::string fileRead;

fileRead = argv[1];


//get name of file being written to 
std::string fileWrite; 

fileWrite = argv[2];



//get width

int widthNew = atoi(argv[3]);

//get height(not always supplied)
int heightNew;

if(argc == 5){
  heightNew = atoi(argv[4]);
}


//open file being read
std::ifstream fin;

//check that it was open successfully 
fin.open(fileRead);

if(!fin.is_open()){
std::cout <<"read" <<std::endl;
std::cout <<"error opening file" << fileRead <<std::endl;
return 1; 

}



//use Imginit #2 to initialize img obj (read one being the original)
Image *imgOriginal = new Image;
Image_init(imgOriginal,fin);



//close file being read 
fin.close();


if(widthNew < 0 ||  widthNew > Image_width(imgOriginal) || 
(argc == 5 && heightNew < 0 )|| (argc == 5 && heightNew > Image_height(imgOriginal))){
std::cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
<< "WIDTH and HEIGHT must be less than or equal to original" << std::endl;
     return 1;

}

//width and height being given are the newWidth and newHeight 
//call seam carve with the new width and height

if(heightNew != 0){
seam_carve(imgOriginal,widthNew,heightNew);
}
else{

seam_carve_width(imgOriginal,widthNew);

}

//now seam gone, save changes so that the 
//new img is equal to the changes 

std::ofstream fout;

fout.open(fileWrite);

if(!fout.is_open()){
std::cout <<"write" <<std::endl;

std::cout <<"error opening file" << fileWrite <<std::endl;
return 1; 

}

Image_print(imgOriginal,fout);

//write to file here

delete imgOriginal;

fout.close();

return 0;


}