// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Image_test_helpers.h"
#include "unit_test_framework.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic) {
  Image *img = new Image; // create an Image in dynamic memory

  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(img, 2, 2);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 1, 0, blue);
  Image_set_pixel(img, 1, 1, white);

  // Capture our output
  ostringstream s;
  Image_print(img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete img; // delete the Image
}

// IMPLEMENT YOUR TEST FUNCTIONS HERE
// You are encouraged to use any functions from Image_test_helpers.h as needed.

//initialize 1

TEST(image_init_1){
  Image *img = new Image;
  Image_init(img, 3, 4);


  ASSERT_EQUAL(Image_width(img),3);
  ASSERT_EQUAL(Image_height(img),4);

  delete img;

}


//one pixel
TEST(image_init_1_1px){

  Image *img = new Image;
  Image_init(img, 1, 1);


  ASSERT_EQUAL(Image_width(img),1);
  ASSERT_EQUAL(Image_height(img),1);

  delete img;

}


//initialize 2
TEST(image_init_2){
 Image *img = new Image;

string input = "P3 4 2\t255 255 0 0\n0\n255 0 \n0 0 255 255 255 255 \n";
  std::istringstream ss_input(input);
  Image_init(img, ss_input);

  ASSERT_EQUAL(Image_width(img),4);
  ASSERT_EQUAL(Image_height(img),2);
  
  Pixel colorExpect = {255,255,255};

  Pixel colorImage = Image_get_pixel(img,1,3);

  assert(Pixel_equal(colorExpect,colorImage));


delete img;


}

//one pixel

TEST(image_init_2_1px){


 Image *img = new Image;

  string input = "P3 1 1\t255 255 0 0\n";
  std::istringstream ss_input(input);
  Image_init(img, ss_input);

  ASSERT_EQUAL(Image_width(img),1);
  ASSERT_EQUAL(Image_height(img),1);
  
  Pixel expected = {255,0,0};

  Image *expectedImg = new Image;
  Image_init(expectedImg,1,1);
  Image_set_pixel(expectedImg,0,0,expected);


  Image_equal(expectedImg,img);
   

delete img;
delete expectedImg;



}


//one pixel

TEST(image_print_1px){

 Image *img = new Image;

  string input = "P3 1 1\t255 255 17 22 \n";
  std::istringstream ss_input(input);
  Image_init(img, ss_input);


  // Capture our output
  ostringstream s;
  Image_print(img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n1 1\n255\n";
  correct << "255 17 22 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete img;
  



}



//width
TEST(image_width){
 Image *img = new Image;
  Image_init(img, 17, 22);


  ASSERT_EQUAL(Image_width(img),17);
  

  delete img;



}

//height
TEST(image_height){

Image *img = new Image;
  Image_init(img, 17, 22);


 
  ASSERT_EQUAL(Image_height(img),22);

  delete img;



}

//get pixel
TEST(image_get_and_set_pixel_begin_mid_end){
   Image *img = new Image;

  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};
 

  Image_init(img, 4, 7);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 0, 2, red);
  Image_set_pixel(img, 0, 3, green);
  Image_set_pixel(img, 1, 0, blue);
  Image_set_pixel(img, 1, 1, white);
  Image_set_pixel(img, 1, 2, blue);
  Image_set_pixel(img, 1, 3, white);
  Image_set_pixel(img, 2, 0, red);
  Image_set_pixel(img, 2, 1, green);
  Image_set_pixel(img, 2, 2, red);
  Image_set_pixel(img, 2, 3, green);
  Image_set_pixel(img, 3, 0, blue);
  Image_set_pixel(img, 3, 1, white);
  Image_set_pixel(img, 3, 2, blue);
  Image_set_pixel(img, 3, 3, white);
  Image_set_pixel(img, 4, 0, red);
  Image_set_pixel(img, 4, 1, green);
  Image_set_pixel(img, 4, 2, red);
  Image_set_pixel(img, 4, 3, green);
  Image_set_pixel(img, 5, 0, blue);
  Image_set_pixel(img, 5, 1, white);
  Image_set_pixel(img, 5, 2, blue);
  Image_set_pixel(img, 5, 3, white);
  Image_set_pixel(img, 6, 0, red);
  Image_set_pixel(img, 6, 1, green);
  Image_set_pixel(img, 6, 2, red);
  Image_set_pixel(img, 6, 3, green);
 


  assert(Pixel_equal(Image_get_pixel(img,3,2),blue));
  assert(Pixel_equal(Image_get_pixel(img,0,0),red));
  assert(Pixel_equal(Image_get_pixel(img,6,3),green));
  delete img;





}

//one pixel
TEST(image_get_and_set_pixel_1px){

Image *img = new Image;

Image_init(img, 1, 1);

const Pixel claretViolet={110,28,52};
Image_set_pixel(img, 0, 0, claretViolet);
assert(Pixel_equal(Image_get_pixel(img,0,0),claretViolet));

  delete img;


}



//image fill
TEST(image_fill_pixel){
Image *img = new Image;
Image_init(img, 4, 7);
const Pixel claretViolet={110,28,52};
Image_fill(img,claretViolet);

assert(Pixel_equal(Image_get_pixel(img,3,2),claretViolet));

delete img;

}

//one pixel
TEST(image_fill_pixel_1px){


Image *img = new Image;
Image_init(img, 1, 1);
const Pixel claretViolet={110,28,52};
Image_fill(img,claretViolet);

assert(Pixel_equal(Image_get_pixel(img,0,0),claretViolet));

delete img;



}








// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
