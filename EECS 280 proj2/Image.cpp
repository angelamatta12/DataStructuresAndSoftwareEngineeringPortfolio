// Project UID af1f95f547e44c8ea88730dfb185559d
#include <string> 
#include <cassert>
#include "Image.h"

// REQUIRES: img points to an Image
//           0 < width && width <= MAX_MATRIX_WIDTH
//           0 < height && height <= MAX_MATRIX_HEIGHT
// MODIFIES: *img
// EFFECTS:  Initializes the Image with the given width and height.
// NOTE:     Do NOT use new or delete here.
void Image_init(Image* img, int width, int height) {
  assert( 0 < width && width <= MAX_MATRIX_WIDTH);
  assert( 0 < height && height <= MAX_MATRIX_HEIGHT);

//initialize img with specified width and height 

img->height = height;
img->width = width;



Matrix_init(&(img->red_channel),width,height);
Matrix_init(&(img->blue_channel),width,height);
Matrix_init(&(img->green_channel),width,height);

}

// REQUIRES: img points to an Image
//           is contains an image in PPM format without comments
//           (any kind of whitespace is ok)
// MODIFIES: *img
// EFFECTS:  Initializes the Image by reading in an image in PPM format
//           from the given input stream.
// NOTE:     See the project spec for a discussion of PPM format.
// NOTE:     Do NOT use new or delete here.
void Image_init(Image* img, std::istream& is) {
// using input stream initalize img, get width, height and file location 

//read file from stream

//store height 
int height = 0;

//store width 
int width = 0;

//amx value used for each pixel 
int max = 0;

//string for filetype
std::string filetype = " ";


is >> filetype >> width >> height >> max;


//temp pixel var 

Pixel temp;

int red =0;
int blue =0;
int green =0;

//initialize img with height and width 
Image_init(img,width,height);


//for loop for filling values in the red, blue and green streams 
// matrix at to set the values 
for(int rows = 0; rows < height; rows++){
for(int columns = 0; columns < width; columns++){


//not sure if this reads right 
is >> red >> green >> blue;

// populate red at that spot
temp.r = red;
// populate green 
temp.g = green;
//populate blue 
temp.b = blue;

Image_set_pixel(img,rows,columns,temp);


  
}


}



}

// REQUIRES: img points to a valid Image
// EFFECTS:  Writes the image to the given output stream in PPM format.
//           You must use the kind of whitespace specified here.
//           First, prints out the header for the image like this:
//             P3 [newline]
//             WIDTH [space] HEIGHT [newline]
//             255 [newline]
//           Next, prints out the rows of the image, each followed by a
//           newline. Each pixel in a row is printed as three ints
//           for its red, green, and blue components, in that order. Each
//           int is followed by a space. This means that there will be an
//           "extra" space at the end of each line. See the project spec
//           for an example.
void Image_print(const Image* img, std::ostream& os) {
  
  os<<"P3\n" << Image_width(img) << " " << Image_height(img)<<"\n255" <<std::endl;

   

//for loop gies through whole array 
for(int i = 0; i < Image_height(img);i++){
  for(int j = 0; j <Image_width(img); j++){
//need if statement that every_  element 
 Pixel temp = Image_get_pixel(img,i,j);

//this one might have an issue too 
os<< temp.r << 
" " << temp.g << 
" "<< temp.b << " ";

if((j+1)%(Image_width(img)) == 0){

os<<std::endl;

}

  }
  
}





}

// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the width of the Image.
int Image_width(const Image* img) {
  
return img->width;



}

// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the height of the Image.
int Image_height(const Image* img) {
  
return img->height;


}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// EFFECTS:  Returns the pixel in the Image at the given row and column.
Pixel Image_get_pixel(const Image* img, int row, int column) {
  assert( 0 <= row && row < Image_height(img));
  assert( 0 <= column && column < Image_width(img));

int red = *Matrix_at(&(img->red_channel),row,column);

int blue = *Matrix_at(&(img->blue_channel),row,column);

int green = *Matrix_at(&(img->green_channel),row,column);





Pixel out;


//double check that these actually set the values
out.r = red;
out.b = blue;
out.g = green;

return out;


}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// MODIFIES: *img
// EFFECTS:  Sets the pixel in the Image at the given row and column
//           to the given color.
void Image_set_pixel(Image* img, int row, int column, Pixel color) {
  assert( 0 <= row && row < Image_height(img)); // TODO Replace with your implementation!
  assert( 0 <= column && column < Image_width(img)); 


//check to see if these initialized properly 
int red = color.r;
int blue = color.b;
int green = color.g;

*Matrix_at(&(img->red_channel),row,column) = red;

*Matrix_at(&(img->blue_channel),row,column) = blue;

*Matrix_at(&(img->green_channel),row,column) = green;



}

// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  Sets each pixel in the image to the given color.
void Image_fill(Image* img, Pixel color) {
  
int red = color.r;
int blue = color.b;
int green = color.g;

Matrix_fill(&(img->red_channel),red);
Matrix_fill(&(img->blue_channel),blue);
Matrix_fill(&(img->green_channel),green);

  
}
