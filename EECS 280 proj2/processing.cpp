// Project UID af1f95f547e44c8ea88730dfb185559d

#include <cassert>
#include "processing.h"

using namespace std;

// v DO NOT CHANGE v ------------------------------------------------
// The implementation of rotate_left is provided for you.
// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  The image is rotated 90 degrees to the left (counterclockwise).
void rotate_left(Image* img) {

  // for convenience
  int width = Image_width(img);
  int height = Image_height(img);

  // auxiliary image to temporarily store rotated image
  Image *aux = new Image;
  Image_init(aux, height, width); // width and height switched

  // iterate through pixels and place each where it goes in temp
  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      Image_set_pixel(aux, width - 1 - c, r, Image_get_pixel(img, r, c));
    }
  }

  // Copy data back into original
  *img = *aux;
  delete aux;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------

// v DO NOT CHANGE v ------------------------------------------------
// The implementation of rotate_right is provided for you.
// REQUIRES: img points to a valid Image.
// MODIFIES: *img
// EFFECTS:  The image is rotated 90 degrees to the right (clockwise).
void rotate_right(Image* img){

  // for convenience
  int width = Image_width(img);
  int height = Image_height(img);

  // auxiliary image to temporarily store rotated image
  Image *aux = new Image;
  Image_init(aux, height, width); // width and height switched

  // iterate through pixels and place each where it goes in temp
  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      Image_set_pixel(aux, c, height - 1 - r, Image_get_pixel(img, r, c));
    }
  }

  // Copy data back into original
  *img = *aux;
  delete aux;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------


// v DO NOT CHANGE v ------------------------------------------------
// The implementation of diff2 is provided for you.
static int squared_difference(Pixel p1, Pixel p2) {
  int dr = p2.r - p1.r;
  int dg = p2.g - p1.g;
  int db = p2.b - p1.b;
  // Divide by 100 is to avoid possible overflows
  // later on in the algorithm.
  return (dr*dr + dg*dg + db*db) / 100;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------


// ------------------------------------------------------------------
// You may change code below this line!



int get_Max(int origMax,int newMax){

if(origMax > newMax){

return origMax;

}

else if(origMax < newMax){


return newMax;

}


return origMax;




}


// REQUIRES: img points to a valid Image.
//           energy points to a Matrix.
// MODIFIES: *energy
// EFFECTS:  energy serves as an "output parameter".
//           The Matrix pointed to by energy is initialized to be the same
//           size as the given Image, and then the energy matrix for that
//           image is computed and written into it.
//           See the project spec for details on computing the energy matrix.
void compute_energy_matrix(const Image* img, Matrix* energy) {
  //init energy matrix
 Matrix_init(energy,Image_width(img),Image_height(img));

  int max = 0;
  int energyCalc = 0;
//use 2d for loop 
  for(int i = 0; i < Image_height(img);i++){
     for(int j =0;j<Image_width(img);j++){

//need to check if it is a border pixel
//0 row  //height-1 row 
//0 column //width-1 column 

if(i != 0 && i!= (Image_height(img)-1) && j != 0 && j != (Image_width(img)-1) ){

//N same column 1 row up S same column 1 row down 
//W same row 1 column left E same row 1 column right 

energyCalc=squared_difference(Image_get_pixel(img,(i-1),j), Image_get_pixel(img,(i+1),j)) 
+ squared_difference(Image_get_pixel(img,i,j-1), Image_get_pixel(img,i,j+1));

*Matrix_at(energy,i,j) = energyCalc;

 
max = get_Max(max,energyCalc);
   

      }

   }

}


Matrix_fill_border(energy,max);

}


// REQUIRES: energy points to a valid Matrix.
//           cost points to a Matrix.
//           energy and cost aren't pointing to the same Matrix
// MODIFIES: *cost
// EFFECTS:  cost serves as an "output parameter".
//           The Matrix pointed to by cost is initialized to be the same
//           size as the given energy Matrix, and then the cost matrix is
//           computed and written into it.
//           See the project spec for details on computing the cost matrix.
void compute_vertical_cost_matrix(const Matrix* energy, Matrix *cost) {
  
//initialize cost matrix

 Matrix_init(cost,Matrix_width(energy),Matrix_height(energy));

for(int rows = 0; rows< Matrix_height(energy);rows++){

for(int columns = 0; columns < Matrix_width(energy);columns++){


//populate first row
if(rows == 0 ){

*Matrix_at(cost,rows,columns) =  *Matrix_at(energy,rows,columns);

}

//check if the location is the first or last column 
//yes then only two above the pixel 
else if (columns == 0){
//need to change this 2 
*Matrix_at(cost,rows,columns) = *Matrix_at(energy,rows,columns) 
+ Matrix_min_value_in_row(cost,(rows-1),columns,columns+2);

}


else if (columns == ((Matrix_width(energy))-1)){

*Matrix_at(cost,rows,columns) = *Matrix_at(energy,rows,columns) 
+Matrix_min_value_in_row(cost,(rows-1),((Matrix_width(energy))-2),(Matrix_width(energy)));


}


//no then the three above the pixel 

else{

//might need to be plus 2 
*Matrix_at(cost,rows,columns) = *Matrix_at(energy,rows,columns) 
+ Matrix_min_value_in_row(cost,(rows-1),(columns-1),(columns+2));


}

}

}


}


// REQUIRES: cost points to a valid Matrix
//           seam points to an array
//           the size of seam is >= Matrix_height(cost)
// MODIFIES: seam[0]...seam[Matrix_height(cost)-1]
// EFFECTS:  seam serves as an "output parameter".
//           The vertical seam with the minimal cost according to the given
//           cost matrix is found and the seam array is filled with the column
//           numbers for each pixel along the seam, with the pixel for each
//           row r placed at seam[r]. While determining the seam, if any pixels
//           tie for lowest cost, the leftmost one (i.e. with the lowest
//           column number) is used.
//           See the project spec for details on computing the minimal seam.
// NOTE:     You should compute the seam in reverse order, starting
//           with the bottom of the image and proceeding to the top,
//           as described in the project spec.
void find_minimal_vertical_seam(const Matrix* cost, int seam[]) {

// First, find the minimum cost pixel in the bottom row.
//index = rows, seam[rows] = column
//bottom row, Matrix_height(cost)-1

//found the column of the minimal cost 
seam[Matrix_height(cost)-1]= 
Matrix_column_of_min_value_in_row(cost,Matrix_height(cost)-1,0,Matrix_width(cost));

if(Matrix_height(cost)==1 &&Matrix_width(cost) == 1){

return;

}


//iterating over the rows, starting with the last row 
//seam[previous row] = column we are currently in 
for(int rows = Matrix_height(cost)-1;rows > 0; rows--){


//check for zero
if(seam[rows] == 0){

seam[rows-1]= 
Matrix_column_of_min_value_in_row(cost,rows-1,(seam[rows]),(seam[rows]+2));


}

else if (seam[rows] == Matrix_width(cost)-1){


seam[rows-1]= 
Matrix_column_of_min_value_in_row(cost,rows-1,(seam[rows]-1),(seam[rows]+1));




}


else{
seam[rows-1]= 
Matrix_column_of_min_value_in_row(cost,rows-1,(seam[rows]-1),(seam[rows]+2));
}




}





}


// REQUIRES: img points to a valid Image with width >= 2
//           seam points to an array
//           the size of seam is == Image_height(img)
//           each element x in seam satisfies 0 <= x < Image_width(img)
// MODIFIES: *img
// EFFECTS:  Removes the given vertical seam from the Image. That is, one
//           pixel will be removed from every row in the image. The pixel
//           removed from row r will be the one with column equal to seam[r].
//           The width of the image will be one less than before.
//           See the project spec for details on removing a vertical seam.
// NOTE:     Use the new operator here to create the smaller Image,
//           and then use delete when you are done with it.
void remove_vertical_seam(Image *img, const int seam[]) {
 

///seam provides coordinates row = index, column = seam[index]

Image* imgCopy = new Image;

Image_init(imgCopy,Image_width(img)-1,Image_height(img));

for(int rows = 0; rows< Image_height(img);rows++){
  
  for(int columns = 0; columns < Image_width(img);columns++){


     //get pixel at that section 
     Pixel temp = Image_get_pixel(img,rows,columns);

     
     if(seam[rows] != columns && seam[rows] > columns){



     //set pixel at that section to copy image 
       Image_set_pixel(imgCopy,rows,columns,temp);


     }

     else if(seam[rows] != columns && seam[rows] < columns){

  
     //set pixel at that section to copy image 
       Image_set_pixel(imgCopy,rows,columns-1,temp);


     }

  }


  }



//copy imgCopy to original 

*img = *imgCopy;

delete imgCopy;


}


// REQUIRES: img points to a valid Image
//           0 < newWidth && newWidth <= Image_width(img)
// MODIFIES: *img
// EFFECTS:  Reduces the width of the given Image to be newWidth by using
//           the seam carving algorithm. See the spec for details.
// NOTE:     Use the new operator here to create Matrix objects, and
//           then use delete when you are done with them.
void seam_carve_width(Image *img, int newWidth) {

assert( 0 < newWidth && newWidth <= Image_width(img));
  
 Matrix *energyCarve = new Matrix;

 Matrix *costCarve = new Matrix;


while(Image_width(img) > newWidth){

// Compute the energy matrix

compute_energy_matrix(img,energyCarve);

// Compute the cost matrix

compute_vertical_cost_matrix(energyCarve,costCarve);

// Find the minimal cost seam

int seamCarve[MAX_MATRIX_HEIGHT];

find_minimal_vertical_seam(costCarve,seamCarve);


// Remove the minimal cost seam

remove_vertical_seam(img,seamCarve);

}

delete energyCarve;
delete costCarve;


}

// REQUIRES: img points to a valid Image
//           0 < newHeight && newHeight <= Image_height(img)
// MODIFIES: *img
// EFFECTS:  Reduces the height of the given Image to be newHeight.
// NOTE:     This is equivalent to first rotating the Image 90 degrees left,
//           then applying seam_carve_width(img, newHeight), then rotating
//           90 degrees right.
void seam_carve_height(Image *img, int newHeight) {
 
assert(0 < newHeight && newHeight <= Image_height(img));


// Rotate the image left by 90 degrees
rotate_left(img);
// Apply seam_carve_width
seam_carve_width(img,newHeight);
// Rotate the image right by 90 degrees
rotate_right(img);



}

// REQUIRES: img points to a valid Image
//           0 < newWidth && newWidth <= Image_width(img)
//           0 < newHeight && newHeight <= Image_height(img)
// MODIFIES: *img
// EFFECTS:  Reduces the width and height of the given Image to be newWidth
//           and newHeight, respectively.
// NOTE:     This is equivalent to applying seam_carve_width(img, newWidth)
//           and then applying seam_carve_height(img, newHeight).
void seam_carve(Image *img, int newWidth, int newHeight) {
  assert( 0 < newWidth && newWidth <= Image_width(img)); 
  assert(0 < newHeight && newHeight <= Image_height(img));

seam_carve_width(img,newWidth);
seam_carve_height(img,newHeight);

  
}
