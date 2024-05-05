#ifndef LIST_H
#define LIST_H
/* List.h
 *
 * doubly-linked, double-ended list with Iterator interface
 * Project UID c1f28c309e55405daf00c565d57ff9ad
 * EECS 280 Project 4
 */

#include <sstream> 
#include <utility>
#include <iostream>
#include <cassert> //assert
#include <cstddef> //NULL


//logic is fine but I dont undertand how it stores the values 

template <typename T>
class List {
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:

//got from notes 
  //EFFECTS:  returns true if the list is empty
  bool empty() const{
  return first == nullptr;
  }


//CHECK
//where should I declare the mem var 
  //EFFECTS: returns the number of elements in this List
  //HINT:    Traversing a list is really slow.  Instead, keep track of the size
  //         with a private member variable.  That's how std::list does it.
  int size() const{
   return numElements;
  }



//got from the notes 
  //need to access list item at ind 0 
  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
  T & front(){
    //make sure 
  assert(!empty());
  return first->datum;

  }



//CHECK
  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
  T & back(){

 assert(!empty());
 return last->datum;


  }



  //EFFECTS:  inserts datum into the front of the list
  void push_front(const T &datum){

   Node *p = new Node;
   p->datum = datum;

  if(empty()){
   p->next = nullptr;
   p->prev = nullptr;
   first = p;
   last = p;
   numElements++;  
   return;
  }

   p->next = first;
   p->prev = nullptr;
   first->prev = p;
   first = p; 
   numElements++;  


  }



  //prev might not be set up right
  //need to see how other elements are 
  //to be updated when it comes to their
  //prev and next ptr
  //EFFECTS:  inserts datum into the back of the list
  void push_back(const T &datum){

   Node *p = new Node;
   p->datum = datum;
  
   
   //need to check this 
   if(empty()){
   p->next = nullptr;
   p->prev = nullptr;
   last = p;
   first = p; 
   numElements++;
   return;
   }

   p->prev = last;
   p->next = nullptr;
   last->next = p;
   last = p;
   numElements++;

  }




  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the front of the list
  //when 2->1 node is first and last the same 
  void pop_front(){
  assert(!empty());
  //the next one in the list should be the first one 

   if(numElements == 1 ){

     delete first;
     first = nullptr;
     last = nullptr;
     numElements--;
     return;

   }

    Node *new_first = first->next;  // temporary keeps track of new first
    delete first;
    first = new_first;
    first->prev = nullptr;
    numElements--;


 
  }



//CHECK 
  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the back of the list
    //when 2->1 node is first and last the same 
  void pop_back(){
  assert(!empty());
  //the node that comes before last should be new last 
  
   if(numElements == 1 ){
    //both elements point to same thing
    delete last;
    last = nullptr;
    first = nullptr;
    numElements--;
    return;

   }
 
  Node *new_last = last->prev;  // temporary keeps track of new last
  delete last;
  last = new_last;
  last->next= nullptr;
  numElements--;

  }


  //CHECK
  //NOTE MAY NEED TO SET FIRST AND LAST TO NULL TEST 
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes all items from the list
  void clear(){

   while(!empty()){
    pop_back();
   }


  }

  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you can omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists


//default constructor

List():first(nullptr),last(nullptr),numElements(0){

}

//CHECK THIS 
//destructor

~List(){

clear();

}


//copy constructor 

List(const List &other){

numElements = 0;

first = nullptr;
last = nullptr;

copy_all(other);

}


//overloaded assignment operator 
//note the change in operator heading definition
List & operator = (const List &rhs) {

if(this == &rhs){ return *this;}

if(!empty()){
clear();

}

//clear the non empty list and populate it with the members of the other list 
copy_all(rhs);

  return *this;

}



private:
  //a private type
  struct Node {
    Node *next;
    Node *prev;
    T datum; //value at the node 
  };


  //REQUIRES: list is empty
  //EFFECTS:  copies all nodes from other to this
  void copy_all(const List<T> &other){

  assert(empty());

  for(Node* p=other.first; p; p=p->next) {
      
      //front should stay the same whole time 
   push_back(p->datum);

    }

  }


  Node *first;   // points to first Node in list, or nullptr if list is empty
  Node *last;    // points to last Node in list, or nullptr if list is empty
  int numElements;//size of list 



public:
  ////////////////////////////////////////
  class Iterator {
    //OVERVIEW: Iterator interface to List

    // You should add in a default constructor, destructor, copy constructor,
    // and overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you can omit them. A user
    // of the class must be able to create, copy, assign, and destroy Iterators.

    // Your iterator should implement the following public operators: *,
    // ++ (prefix), default constructor, == and !=.

  public:


//     // This operator will be used to test your code. Do not modify it.
//     // Requires that the current element is dereferenceable.

    Iterator& operator--() {
      assert(node_ptr);
      node_ptr = node_ptr->prev;
      return *this;
    }

// //*
//     //derefe operator
//     //should we by default 
    T & operator*() {
     assert(node_ptr);
     return node_ptr->datum;

    }

// //++
  Iterator & operator++() {
   assert(node_ptr);  
   node_ptr = node_ptr->next;
   return *this;
    }


// //bools 
bool operator==(Iterator rhs ) const{
  return node_ptr == rhs.node_ptr;

    }

   bool operator!=(Iterator rhs ) const{
    return node_ptr != rhs.node_ptr;
    }

  private:
    Node *node_ptr; //current Iterator position is a List node
    // add any additional necessary member variables here
    //need the size of the list or else could go out of bounds, but should it be here 
    size_t num_elements;
   
    // add any friend declarations here
    friend class List;

    // construct an Iterator at a specific position, should be internal
    Iterator(Node *p):node_ptr(p){}

    //default constr, may need to move this one to the public section 
    Iterator():node_ptr(nullptr){}
 
//according to lecture, we should not implement 
//the big 3, just use default!!!!!

  };
  
  //List::Iterator
  ////////////////////////////////////////

//return iterator pointing to first node 
  // return an Iterator pointing to the first element
  Iterator begin() const {
    return Iterator(first);
  }


//return iterator to last node + 1 not last node 
  // return an Iterator pointing to "past the end"
  Iterator end() const{

  return Iterator();
  
  }







  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: may invalidate other list iterators
  //EFFECTS: Removes a single element from the list container
  void erase(Iterator i){

//cant be empty here 

  assert(!empty());

//split into cases
//beginning
if(i == begin()){

pop_front();
return;

}
//end
else if( i == end()){

pop_back();
return;


}




//B) adjust the next of the node
//that comes before the one we just deleted

i.node_ptr->prev->next =i.node_ptr->next; 

//C) adjust the prev of the node that comes 
// after the one we just deleted
i.node_ptr->next->prev = i.node_ptr->prev; 


//at node that the iterator is pointing to 
//A) must delete it 

delete (i.node_ptr);

numElements--;


  }



  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: inserts datum before the element at the specified position.
  void insert(Iterator i, const T &datum){


//can be empty 
 
if(i == begin()){

push_front(datum);
return;

}
//end
else if( i == end()){

push_back(datum);
return;

}

//iterator i 
//points to the prev 
//points to the next 
//need to access the nodes that are pointed
//at then edit their prev and their next 


//at node that the iterator is pointing to 
//A) must add it at that point 
//B) adjust the next of the node
//that comes before the one we just added 
//points to new node 

//check this later 

Node *p = new Node();
p->datum = datum;
p->next= i.node_ptr;
p->prev= i.node_ptr->prev;

i.node_ptr->prev->next = p;

//C) adjust the prev of the node that comes 
// after the one we just added
//points to the new node 

i.node_ptr->prev = p;

numElements++;

  }



};//List


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.


#endif // Do not remove this. Write all your code above this line.
