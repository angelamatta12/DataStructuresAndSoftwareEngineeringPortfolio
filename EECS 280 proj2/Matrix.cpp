// Project UID af1f95f547e44c8ea88730dfb185559d

#include <cassert>
#include "Matrix.h"

// REQUIRES: mat points to a Matrix
//           0 < width && width <= MAX_MATRIX_WIDTH
//           0 < height && height <= MAX_MATRIX_HEIGHT
// MODIFIES: *mat
// EFFECTS:  Initializes *mat as a Matrix with the given width and height.
// NOTE:     Do NOT use new or delete here.
void Matrix_init(Matrix* mat, int width, int height) {
  

   assert( 0 < width && width <= MAX_MATRIX_WIDTH);
   assert(0 < height && height <= MAX_MATRIX_HEIGHT);

  mat->width= width;
  mat->height= height;


}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: os
// EFFECTS:  First, prints the width and height for the Matrix to os:
//             WIDTH [space] HEIGHT [newline]
//           Then prints the rows of the Matrix to os with one row per line.
//           Each element is followed by a space and each row is followed
//           by a newline. This means there will be an "extra" space at
//           the end of each line.
void Matrix_print(const Matrix* mat, std::ostream& os) {

  os << mat->width << " " << mat->height <<std::endl;

int sizeArray = (mat->height)*(mat->width);

//for loop gies through whole array 
for(int i = 0; i < sizeArray;i++){
//need if statement that every_  element 


os<< mat->data[i] << " ";

if((i+1)%(mat->width) == 0){

os<<std::endl;

}


  
}



}



// REQUIRES: mat points to an valid Matrix
// EFFECTS:  Returns the width of the Matrix.
int Matrix_width(const Matrix* mat) {
  
return mat->width;

}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the height of the Matrix.
int Matrix_height(const Matrix* mat) {
 
return mat->height;


}

// REQUIRES: mat points to a valid Matrix
//           ptr points to an element in the Matrix
// EFFECTS:  Returns the row of the element pointed to by ptr.
int Matrix_row(const Matrix* mat, const int* ptr) {
  
  //use mat to get the starting address aka address of first element in array 

  const int* startAddress = &(mat->data[0]);

  //have address of the element we are looking for in ptr 

  //difference should be the index, may need to adjust by 1 

  int difference = (ptr-startAddress); 


//need our height, how many groups we have to search 

// each row/group has "width" # of elements

int rowLoc = 0;

//get row through integer division, index//width 

//need to make sure it is an integer for the output 

rowLoc = difference / (mat->width);

return rowLoc;


}



// REQUIRES: mat points to a valid Matrix
//           ptr point to an element in the Matrix
// EFFECTS:  Returns the column of the element pointed to by ptr.
int Matrix_column(const Matrix* mat, const int* ptr) {
 
   //use mat to get the starting address 

  const int* startAddress = &(mat->data[0]);


  //have address of the element we are looking for in ptr 

  //difference should be the index, may need to adjust by 1 

  int difference = (ptr-startAddress); 




//need our width, how many groups we have to search 

// each group has "height" # of elements

int columnLoc = 0;



//get index%width for column 

columnLoc = difference % mat->width;

return columnLoc;





}



// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// MODIFIES: (The returned pointer may be used to modify an
//            element in the Matrix.)
// EFFECTS:  Returns a pointer to the element in the Matrix
//           at the given row and column.
int* Matrix_at(Matrix* mat, int row, int column) {
  assert(0 <= row && row < Matrix_height(mat)); 
  assert(0 <= column && column < Matrix_width(mat)); 

    int index = row*(mat->width)+column;

    int *ptr = &(mat->data[index]);

    return ptr;


}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// EFFECTS:  Returns a pointer-to-const to the element in
//           the Matrix at the given row and column.
const int* Matrix_at(const Matrix* mat, int row, int column) {
 
//used in image.cpp, image print 

  assert(0 <= row && row < Matrix_height(mat)); 
  assert(0 <= column && column < Matrix_width(mat)); 


   int index = row*(mat->width)+column;

   const int *ptr = &(mat->data[index]);

   return ptr;

}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element of the Matrix to the given value.
void Matrix_fill(Matrix* mat, int value) {

  int sizeArray = (mat->height)*(mat->width);
  
  for(int i = 0; i< sizeArray;i++){

  mat->data[i]= value;


  }



}



// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element on the border of the Matrix to
//           the given value. These are all elements in the first/last
//           row or the first/last column.
void Matrix_fill_border(Matrix* mat, int value) {


//this does fill all of the first and last values of each matrix row 
for(int i = 1; i < mat->height+1; i++){

//largest index of that row 
int maxRow = ((i) * (mat->width))-1;

//smallest index of that row 
int minRow = ((i) * (mat->width)) - (mat->width);

mat->data[maxRow]=value;
mat->data[minRow]=value;


}


//should iterate over the width to fill in the value for the first row and last row

for(int i = 0; i < mat->width; i++){

//populate all of first row 
  mat->data[i] = value;



//height -1 to get the last row 

//populate all of the last row 
int index = ((mat->height)-1)*(mat->width)+i;

  mat->data[index]=value;

}

}




// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the value of the maximum element in the Matrix
int Matrix_max(const Matrix* mat) {
  //largest value in matrix 

//need to iterate over data array 

int sizeArray = (mat->height) * (mat->width);


int maxValue = mat->data[0]; 

for(int i = 0; i < sizeArray ;i++){

if(maxValue < (mat->data[i])){

maxValue = (mat->data[i]);

}

}

return maxValue;

}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the column of the element with the minimal value
//           in a particular region. The region is defined as elements
//           in the given row and between column_start (inclusive) and
//           column_end (exclusive).
//           If multiple elements are minimal, returns the column of
//           the leftmost one.
int Matrix_column_of_min_value_in_row(const Matrix* mat, int row,
                                      int column_start, int column_end) {
  assert(0 <= row && row < Matrix_height(mat));
  assert(0 <= column_start && column_end <= Matrix_width(mat));
  assert(column_start < column_end);


//have row and the indexes for the start and the end of the column 

//row(width)+ column = index in the array 



int minValue = mat->data[row * (mat->width) + column_start];

const int* ptrColumn = &(mat->data[row * (mat->width) + column_start]);


for(int i = column_start+1; i < column_end;i++){


int index = row * (mat->width) + i;

if(minValue > mat->data[index]){

minValue = mat->data[index];

ptrColumn = &(mat->data[index]);



}



}


//need to call the matrix column one to get the actual thing
//need to turn this into address 


return Matrix_column(mat,ptrColumn);


}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the minimal value in a particular region. The region
//           is defined as elements in the given row and between
//           column_start (inclusive) and column_end (exclusive).
int Matrix_min_value_in_row(const Matrix* mat, int row,
                            int column_start, int column_end) {
 

  assert(0 <= row && row < Matrix_height(mat));
  assert(0 <= column_start && column_end <= Matrix_width(mat));
  assert(column_start < column_end);


int minValue = mat->data[row * (mat->width) + column_start];


for(int i = column_start+1; i < column_end;i++){

int index = row * (mat->width) + i;

if(minValue > mat->data[index]){

minValue = mat->data[index];


}

}


return minValue;



}
