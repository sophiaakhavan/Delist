#include <iostream>
#include "delist.h"

/*
NOTE:
compile:
g++ -g delist.cpp delist_test.cpp -o delist_test
valgrind:
valgrind --tool=memcheck --leak-check=yes ./delist_test
*/



using namespace std;


// Constructs an empty Double-Ended List
  DEList::DEList()
  {
    head=NULL;
    tail=NULL;
    _size=0;
  }

// Destructor to clean-up memory of current list
  DEList::~DEList()
  {
//     while(!empty())
//     {
//       pop_front();
//     }
    DEItem* temp=head;
    while(_size>0)
    {
      head=head->next;
      delete temp;
      temp=head;
      _size--;
    }
    delete head;
  }

// returns a Boolean 'true' if the list is empty
  bool DEList::empty()
  {
    return head == NULL && tail == NULL; //head/tail pointer is null if list is empty
    
  }

// returns number of items in the list
  int DEList::size()
  {
    return _size;
  }

// returns front item or -1 if empty list
  int DEList::front()
  {
    if(!empty())
    {
      return head->val;
    }
    else
    {
      return -1; //note to self: throw exception usually instead
    }
  }

// returns back item or -1 if empty list
  int DEList::back()
  {
    if(!empty())
    {
      return tail->val;
    }
    else
    {
      return -1;
    }
  }

// Adds a new integer to the front of the list
  void DEList::push_front(int new_val)
  {
    
    DEItem* newItem = new DEItem;
    newItem->val=new_val; //newItem has value new_val
    newItem->prev=NULL; //first element prev always NULL
    //empty or not needs to be checked bc first element has a prev if !empty
    //also bc tail gets updated if it is empty
    if(empty())
    {
      newItem->next=NULL;
      head=newItem;
      tail=newItem;

    }
    else
    {
      newItem->next=head;
      head->prev=newItem; //first element's previous becomes newItem
      head=newItem; //THEN update head
      
      //tail doesnt change
    }
    
    _size++; //make size() def easier
  }

// Adds a new integer to the back of the list
  void DEList::push_back(int new_val)
  {
    DEItem* newItem = new DEItem;
    newItem->val=new_val;
    newItem->next=NULL;
    //to make sure we dont try to dereference a null pointer if list is empty
    if(empty())
    {
      newItem->prev=NULL;
      head=newItem;
      tail=newItem;
    }
    else
    {
      newItem->prev=tail; //prev is our original last element
      tail->next=newItem; //making the original last element's next be newItem
      tail=newItem; //set new tail
      
    }
    _size++;
  }

// Removes the front item of the list (if it exists)
  void DEList::pop_front()
  {
    
    if(!empty())
    {
      if(size()==1) //special case when only one element
      {
        head = NULL; //new head points to null
        tail = NULL;
      }
      else
      {
        DEItem* temp;
        temp=head->next; //move head to next element
        temp->prev=NULL;
        delete head; //clear original head
        head=temp; //set new head
      }
      

      _size--; //our size decreases
    }
  }

// Removes the back item of the list (if it exists)
  void DEList::pop_back()
  {
    if(!empty())
    {
      if(size()==1) //special case if only one element
      {
        head=NULL;
        tail=NULL;
      }
      else
      {
        DEItem* temp;
        temp = tail->prev; //second to last element
        temp->next=NULL;
        delete tail; //clear original tail
        tail=temp; //set new tail
      }
      
      _size--;
    }
  }