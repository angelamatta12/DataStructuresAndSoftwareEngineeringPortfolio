// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Matrix_test_helpers.h"
#include "unit_test_framework.h"
#include <cassert>

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }

  delete mat; // delete the Matrix
}

// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.h as needed.

//test initialization

TEST(test_init_basic){

//standard call width greater than height 
Matrix *mat = new Matrix;
const int width = 8;
const int height = 3;
Matrix_init(mat,width,height);

assert(Matrix_width(mat) == 8);

assert(Matrix_height(mat) == 3);

delete mat;




}


TEST(test_init_edge1){



//width and height equal max

Matrix *mat5 = new Matrix;
const int width = 500;
const int height = 500;
Matrix_init(mat5,width,height);

assert(Matrix_width(mat5) == 500);

assert(Matrix_height(mat5) == 500);

delete mat5;



}

TEST(test_init_edge2){

//width and height equal min

Matrix *mat6 = new Matrix;
const int width = 1;
const int height = 1;
Matrix_init(mat6,width,height);

assert(Matrix_width(mat6) == 1);

assert(Matrix_height(mat6) == 1);

delete mat6;



}

// TEST(test_init_break1){


// //break it call 1


// Matrix *mat3 = new Matrix;
// const int width = 0;
// const int height = 0;
// Matrix_init(mat3,width,height);

// assert(mat3->width = 0);

// assert(mat3->width = 0);

// delete mat3;

// }

// TEST(test_init_break2){


// //break it call 2 


// Matrix *mat4 = new Matrix;
// const int width = 501;
// const int height = 501;
// Matrix_init(mat4,width,height);

// assert(mat4->width = 501);

// assert(mat4->width = 501);

// delete mat4;

// }



//test print

TEST(test_print){

 Matrix *mat = new Matrix;
  Matrix_init(mat, 2, 4);

  *Matrix_at(mat, 0, 0) = 42;
  *Matrix_at(mat, 0, 1) = 0;
  *Matrix_at(mat, 1, 0) = 0;
  *Matrix_at(mat, 1, 1) = 0;
  *Matrix_at(mat, 2, 0) = 0;
  *Matrix_at(mat, 2, 1) = 0;
  *Matrix_at(mat, 3, 0) = 0;
  *Matrix_at(mat, 3, 1) = 0;
  ostringstream expected;
  expected << "2 4\n"
           << "42 0 \n"
           << "0 0 \n"
           << "0 0 \n"
           << "0 0 \n";
  ostringstream actual;
  Matrix_print(mat, actual);

//cout<<"expected" << expected.str() <<"end of expected"<<std::endl;
//cout<<"actual" << actual.str() <<"end of actual"<<std::endl;

  ASSERT_EQUAL(expected.str(), actual.str());

  delete mat;


}

//test matrix width 

TEST(test_matrix_width){


Matrix *mat = new Matrix;
const int width = 10;
const int height = 13;
Matrix_init(mat,width,height);

assert(Matrix_width(mat) == 10);

//assert(mat->height= 1);

delete mat;


}

//test matrix height 

TEST(test_matrix_height){


Matrix *mat = new Matrix;
const int width = 10;
const int height = 13;
Matrix_init(mat,width,height);

assert(Matrix_height(mat) == 13);

delete mat;


}

//test matrix row 

TEST(test_matrix_row){

Matrix *mat = new Matrix;
const int width = 10;
const int height = 13;
Matrix_init(mat,width,height);


*Matrix_at(mat, 7, 6) = 22;

const int *ptr = Matrix_at(mat, 7, 6);

ASSERT_EQUAL(Matrix_row(mat, ptr), 7);

delete mat;

}

TEST(test_matrix_row_end){


Matrix *mat = new Matrix;
const int width = 9;
const int height = 17;
Matrix_init(mat,width,height);


*Matrix_at(mat, 16, 8) = 22;

const int *ptr = Matrix_at(mat, 16, 8);

ASSERT_EQUAL(Matrix_row(mat, ptr), 16);
delete mat;


}

TEST(test_matrix_row_begin){

Matrix *mat = new Matrix;
const int width = 10;
const int height = 13;
Matrix_init(mat,width,height);


*Matrix_at(mat, 0, 0) = 42;

const int *ptr = Matrix_at(mat, 0, 0);

ASSERT_EQUAL(Matrix_row(mat, ptr), 0);

delete mat;

}


TEST(test_matrix_row_one){



Matrix *mat = new Matrix;
const int width = 1;
const int height = 1;
Matrix_init(mat,width,height);


*Matrix_at(mat, 0, 0) = 17;

const int *ptr = Matrix_at(mat, 0, 0);

ASSERT_EQUAL(Matrix_row(mat, ptr), 0);
delete mat;

}

//test matrix column

TEST(test_matrix_column){


Matrix *mat = new Matrix;
const int width = 9;
const int height = 17;
Matrix_init(mat,width,height);


*Matrix_at(mat, 16, 8) = 22;

const int *ptr = Matrix_at(mat, 16, 8);

ASSERT_EQUAL(Matrix_column(mat, ptr), 8);
delete mat;

}


TEST(test_matrix_column_end){


Matrix *mat = new Matrix;
const int width = 9;
const int height = 17;
Matrix_init(mat,width,height);


*Matrix_at(mat, 16, 8) = 22;

const int *ptr = Matrix_at(mat, 16, 8);

ASSERT_EQUAL(Matrix_column(mat, ptr), 8);
delete mat;


}

TEST(test_matrix_column_begin){

Matrix *mat = new Matrix;
const int width = 10;
const int height = 13;
Matrix_init(mat,width,height);


*Matrix_at(mat, 0, 0) = 42;

const int *ptr = Matrix_at(mat, 0, 0);

ASSERT_EQUAL(Matrix_column(mat, ptr), 0);

delete mat;

}


TEST(test_matrix_column_one){



Matrix *mat = new Matrix;
const int width = 1;
const int height = 1;
Matrix_init(mat,width,height);


*Matrix_at(mat, 0, 0) = 17;

const int *ptr = Matrix_at(mat, 0, 0);

ASSERT_EQUAL(Matrix_column(mat, ptr), 0);
delete mat;

}


//test matrix at that returns ptr

TEST(test_matrix_at_1){

Matrix *mat = new Matrix;
const int width = 10;
const int height = 13;
Matrix_init(mat,width,height);


*Matrix_at(mat, 7, 6) = 42;

//matrix at takes these and pops the location in data, if it worked then 
//should be able to reverse it 

int *ptr = Matrix_at(mat, 7, 6);

//should give us 7 as row, 6 as column 

assert(Matrix_row(mat,ptr) == 7);
assert(Matrix_column(mat,ptr) == 6);


delete mat;


}


//test matrix at that returns constant ptr

TEST(test_matrix_at_2){

 Matrix* mat = new Matrix;
const int width = 10;
const int height = 13;
Matrix_init(mat,width,height);


*Matrix_at(mat, 7, 6) = 42;

const Matrix* mat1 = mat;

const int *ptr = Matrix_at(mat1, 7, 6);


assert(Matrix_row(mat,ptr) == 7);
assert(Matrix_column(mat,ptr) == 6);


delete mat;




}

//test matrix fill

TEST(test_matrix_fill){

  Matrix *mat = new Matrix;
  Matrix_init(mat, 5, 5);

  Matrix_fill(mat, 77);

  int *ptr = Matrix_at(mat, 2, 3);

  assert(*ptr == 77);


  delete mat;
}



TEST(test_matrix_fill_one){

  Matrix *mat = new Matrix;
  Matrix_init(mat, 1, 1);

  Matrix_fill(mat, 9);

  int *ptr = Matrix_at(mat, 0, 0);

  assert(*ptr == 9);


  delete mat;
}

//test matrix fill border

TEST(test_matrix_fill_border){

  Matrix *mat = new Matrix;
  Matrix_init(mat, 4, 3);

  Matrix_fill_border(mat, 9);

  int *ptr = Matrix_at(mat, 2, 1);

  assert(*ptr == 9);


  delete mat;


}

TEST(test_matrix_fill_border_one){



  Matrix *mat = new Matrix;
  Matrix_init(mat, 1, 1);

  Matrix_fill_border(mat, 9);

  int *ptr = Matrix_at(mat, 0, 0);

  assert(*ptr == 9);

  delete mat;
}

TEST(test_matrix_fill_border_one_row){


  Matrix *mat = new Matrix;
  Matrix_init(mat, 1, 8);

  Matrix_fill(mat, 9);

  int *ptr = Matrix_at(mat, 6, 0);

  assert(*ptr == 9);


  delete mat;


}

TEST(test_matrix_fill_border_two_row){


  Matrix *mat = new Matrix;
  Matrix_init(mat, 2, 6);

  Matrix_fill(mat, 9);

  int *ptr = Matrix_at(mat, 1, 1);

  assert(*ptr == 9);

  int *ptr2 = Matrix_at(mat, 2, 1);

  assert(*ptr2 == 9);


  delete mat;


}



//test matrix max

TEST(test_matrix_max){


  Matrix *mat = new Matrix;
  Matrix_init(mat, 2, 6);

   *Matrix_at(mat, 0, 0) = 22;
   *Matrix_at(mat, 1, 0) = 11;
   *Matrix_at(mat, 2, 0) = 30; 
   *Matrix_at(mat, 3, 0) = 18;
   *Matrix_at(mat, 4, 0) = 10;
   *Matrix_at(mat, 5, 0) = 15;
   *Matrix_at(mat, 0, 1) = 17;
   *Matrix_at(mat, 1, 1) = 23;
   *Matrix_at(mat, 2, 1) = 35;
   *Matrix_at(mat, 3, 1) = 60;
   *Matrix_at(mat, 4, 1) = 71;
   *Matrix_at(mat, 5, 1) = 19;


   assert(Matrix_max(mat)==71);


  delete mat;



}


TEST(test_matrix_max_one){

  Matrix *mat = new Matrix;
  Matrix_init(mat, 1, 1);
  *Matrix_at(mat, 0, 0) = 22;
  assert(Matrix_max(mat)==22);

    delete mat;

}



TEST(test_matrix_max_multi){

 
  Matrix *mat = new Matrix;
  Matrix_init(mat, 2, 6);

   
   *Matrix_at(mat, 0, 0) = 22;
   *Matrix_at(mat, 1, 0) = 11;
   *Matrix_at(mat, 2, 0) = 30; 
   *Matrix_at(mat, 3, 0) = 18;
   *Matrix_at(mat, 4, 0) = 71;
   *Matrix_at(mat, 5, 0) = 15;
   *Matrix_at(mat, 0, 1) = 17;
   *Matrix_at(mat, 1, 1) = 23;
   *Matrix_at(mat, 2, 1) = 35;
   *Matrix_at(mat, 3, 1) = 60;
   *Matrix_at(mat, 4, 1) = 71;
   *Matrix_at(mat, 5, 1) = 19;



   assert(Matrix_max(mat)==71);

    delete mat;

}




//test column of min 

TEST(test_matrix_min_column){

  Matrix *mat = new Matrix;
  Matrix_init(mat, 2, 6);

   
   *Matrix_at(mat, 0, 0) = 22;
   *Matrix_at(mat, 1, 0) = 11;   //this one 
   *Matrix_at(mat, 2, 0) = 30; 
   *Matrix_at(mat, 3, 0) = 18;
   *Matrix_at(mat, 4, 0) = 71;
   *Matrix_at(mat, 5, 0) = 15;
   *Matrix_at(mat, 0, 1) = 17;
   *Matrix_at(mat, 1, 1) = 23; //this one 
   *Matrix_at(mat, 2, 1) = 35;
   *Matrix_at(mat, 3, 1) = 60;
   *Matrix_at(mat, 4, 1) = 71;
   *Matrix_at(mat, 5, 1) = 19;


  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat,1,0,2),0);



delete mat;

}

//multiple min 
TEST(test_matrix_min_column_multiple){



  Matrix *mat = new Matrix;
  Matrix_init(mat, 2, 6);

   
   *Matrix_at(mat, 0, 0) = 22;
   *Matrix_at(mat, 1, 0) = 11; //looking at this one 
   *Matrix_at(mat, 2, 0) = 30; 
   *Matrix_at(mat, 3, 0) = 18;
   *Matrix_at(mat, 4, 0) = 11;
   *Matrix_at(mat, 5, 0) = 71;
   *Matrix_at(mat, 0, 1) = 17;
   *Matrix_at(mat, 1, 1) = 11; //looking at this one 
   *Matrix_at(mat, 2, 1) = 35;
   *Matrix_at(mat, 3, 1) = 60;
   *Matrix_at(mat, 4, 1) = 71;
   *Matrix_at(mat, 5, 1) = 19;

   ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat,1,0,2),0);

delete mat;

}

//test min value in row 

TEST(test_min_val_row){


  Matrix *mat = new Matrix;
  Matrix_init(mat, 2, 6);

   
   *Matrix_at(mat, 0, 0) = 22;
   *Matrix_at(mat, 1, 0) = 11;
   *Matrix_at(mat, 2, 0) = 30; 
   *Matrix_at(mat, 3, 0) = 18;
   *Matrix_at(mat, 4, 0) = 71;
   *Matrix_at(mat, 5, 0) = 15;
   *Matrix_at(mat, 0, 1) = 17;
   *Matrix_at(mat, 1, 1) = 23;
   *Matrix_at(mat, 2, 1) = 35;
   *Matrix_at(mat, 3, 1) = 60;
   *Matrix_at(mat, 4, 1) = 71;
   *Matrix_at(mat, 5, 1) = 19;

    ASSERT_EQUAL(Matrix_min_value_in_row(mat,1,0,2),11);

delete mat;

}





// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
