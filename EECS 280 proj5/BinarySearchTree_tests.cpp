// Project UID db1f506d06d84ab787baf250c265e24e

#include "BinarySearchTree.h"
#include "unit_test_framework.h"


// TEST(test_stub) {
//     // Add your tests here
//     ASSERT_TRUE(true);
// }

//checking size



//purely all 
//numerical 

TEST(test_set_1) {


//empty boi
  BinarySearchTree<int> tree;

  ASSERT_TRUE(tree.size()== 0);
  ASSERT_TRUE(tree.height()== 0);
//insert 1 val 

  tree.insert(10);

  ASSERT_TRUE(tree.size()== 1);
  ASSERT_TRUE(tree.height()== 1);


//insert multiple val 
tree.insert(9);
tree.insert(8);
tree.insert(12);
tree.insert(11);
tree.insert(13);


  ASSERT_TRUE(tree.size()== 6);
  ASSERT_TRUE(tree.height()== 3);


//test correct invar 

ASSERT_TRUE(tree.check_sorting_invariant());

BinarySearchTree<int>::Iterator itMax = tree.max_element();

BinarySearchTree<int>::Iterator itMin = tree.min_element();

BinarySearchTree<int>::Iterator itBegin = tree.begin();


ASSERT_TRUE(*(itBegin) == 8);

//find min 

ASSERT_TRUE(*(itMax) == 13);


//find max 
ASSERT_TRUE(*(itMin) == 8);


//find min > than 

BinarySearchTree<int>::Iterator itFindMinGreat = tree.min_greater_than(7);
BinarySearchTree<int>::Iterator itFindMinGreatNo = tree.min_greater_than(20);
BinarySearchTree<int>::Iterator itEnd = tree.end();

ASSERT_TRUE(*(itFindMinGreat ) == 8);
ASSERT_TRUE(itFindMinGreatNo == itEnd);

}




//finding min/max


TEST(test_min_max){

//empty 
BinarySearchTree<int> tree;

BinarySearchTree<int>::Iterator itMax = tree.max_element();

BinarySearchTree<int>::Iterator itMin = tree.min_element();

BinarySearchTree<int>::Iterator itEnd = tree.end();


//how do I check if 
//both nullptr 
ASSERT_TRUE(itMax == itEnd);

ASSERT_TRUE(itMin == itEnd);
//one item

tree.insert(100);

 itMax = tree.max_element();
 itMin = tree.min_element();

ASSERT_TRUE(itMax != itEnd);

ASSERT_TRUE(itMin != itEnd);

ASSERT_TRUE(*itMax == *itMin);





}


//copy construct




TEST_MAIN()
