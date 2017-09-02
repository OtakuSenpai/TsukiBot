#ifndef TRYX_LINKEDLIST_HPP
#define TRYX_LINKEDLIST_HPP

#include <stdio.h>
#include <stdlib.h>
#include "config.hpp"

/* Like the fact that you're using ints for your indices and not handling negative values in any shape 
or form, like the fact that at() can be called with a value equal to this->size(), 
that many of the member functions here pass by value instead of const reference, that you catch 
exceptions thrown and only print an error message, that it doesn't implement begin() or end() or 
any variant thereof (unless you have versions of std::begin/end in which case I take that point back) 
making it impossible to use with standard algorithms... 
Oh, and the create function. Why isn't that a constructor?
(Also, I'd normally make a note about const correctness, but you don't seem to have any intention
 of using const TryxLists, so... it would be a moot argument).
search, for instance, could be const. Same with at and retDataAtPos since they return copies.
*/

template<typename T,typename U>
class List {
  public:
    TRYX_API_EXP List() {
      root = nullptr;
    }
      
    TRYX_API_EXP List(const T& param1,const U& param2) {
      if(root == nullptr) {
        Node* nn = new Node(param1,param2);
        if(!nn) throw "Error in class List,can't create another node.\n";  
        else root = nn; 
      }
      else throw "Error in class List,list already exists.\n";
    }

    TRYX_API_EXP ~List() { deleteList(); }
      
    TRYX_API_EXP size_t size() const {
      Node* temp = root;
      size_t count = 0;
      while(temp != nullptr) {
        count++; temp = temp->next;
      }
      return count;
    }
      
    TRYX_API_EXP U at (const size_t& pos) {
      U retValue;
      if(this->size() < pos) 
        throw "Error in class List, searching out of bounds.\n";
      else if(root != nullptr) {
        Node* current = root;
        int temp = 0;
          
        while(current != nullptr) {
          if(temp == pos) {
            retValue = current->_data;
            break;
          } 
          ++temp;
          current = current->next;
        }
      }
      else 
        throw "Error in class List, can't return an empty list.\n";
        
      return retValue;
    }
    
    TRYX_API_EXP int search (const T& searchItem) const {
      int pos = 0;
      if(root != nullptr) {
        Node* current = root;
        while(current != nullptr) {
          if(current->_name == searchItem) break;
          ++pos;
          current = current->next;
        }
      }
      else 
        throw "Error in class List, searching on an empty list.\n";    
      return pos;  
    }
      
    TRYX_API_EXP U retDataAtPos (const T& identifier) const {
      int pos = search(identifier);
      Node* current = root;
      for(int j = 0; j<pos; j++) 
        current = current->next;
      if(identifier == current->_name)
        return current->_data;
      else 
        throw "Error in class List,couldn't find the entry in the list.";
    }
      
    TRYX_API_EXP void reverse() const {
      Node* prev   = nullptr;
      Node* current = root;
      Node* next;
      while(current != nullptr) {
        next = current->next;  
        current->next = prev;   
        prev = current;
        current = next;
      }
      root = prev;
    } 
       
    TRYX_API_EXP void uniqueIt() const {
      Node *ptr1, *ptr2, *dup;
      ptr1 = root;
 
      while (ptr1 != nullptr && ptr1->next != nullptr) {
        ptr2 = ptr1;
 
      while (ptr2->next != nullptr) {
        if (ptr1->_data == ptr2->next->_data) {
          dup = ptr2->next;
            ptr2->next = ptr2->next->next;
            delete dup;
          }
        else ptr2 = ptr2->next;
      }
      ptr1 = ptr1->next;
      }
    } 
       
    TRYX_API_EXP void pushBack(const T& param1,const U& param2) {
      if(root != nullptr) {
        Node* nn = new Node(param1,param2);
        if(!nn) throw "Error in class List,can't create another node.\n";
        else {          
          Node* temp = root;
          while(temp->next != nullptr) temp = temp->next;
            temp->next = nn; nn->next = nullptr;
        }   
      }
      else List(param1,param2);
    }
      
    TRYX_API_EXP void popBack() {
      if(root != nullptr) {
        Node* current = root;
        Node* prev;
        while(1) {
          if(current->next == nullptr) break;
          prev = current;
          current = current->next;
        }
        prev->next = nullptr;
        delete current;
      }
      else throw "Error in class List,list has not been created.\n";
    }
      
    TRYX_API_EXP void pop(const T& param1) {
      Node *old, *current;
      if(root != nullptr) {
        current = root;	
        while(current != nullptr) {
          if(current->_name == param1) {
            if(current == root)
              root = current->next;
            else old->next = current->next;
            delete current; current = nullptr;
            return;
          }
          else {
            old = current;
            current = current->next;
          }
        }
      }
      else throw "Error in class List,parameter to be deleted not found.";
    }
      
    TRYX_API_EXP void deleteList() const {
    	if(root == nullptr) throw "Error in class List, deleting an empty list.\n";
    	else {
        Node* current = root;
        Node* next;
        while (current != nullptr) {
          next = current->next;
          delete current;
          current = next;
        }
        root = nullptr;
      }
    } 
        
  private:
      
    struct Node {
      T _name;
      U _data;
      Node* next;
        
      TRYX_API_EXP Node() {}    
      TRYX_API_EXP Node(T t,U u) : _name(t), _data(u) {}
      TRYX_API_EXP Node(const Node* other) {
        try {
          _name = other._name;
         _data = other._data;
         next = other.next;
        }
        catch(const char* e) { 
          printf("Error in class List,caught exception: \n");
          printf("%s", e); 
        }           
      }
      TRYX_API_EXP Node* operator=(const Node* other) {
        try {
          free();
          Node* temp = new Node(other);
          return temp;
        }
        catch(const char* e) { 
          printf("Error in class List,caught exception: \n");
          printf("%s", e); 
        }
      }
      TRYX_API_EXP void free() {
        free(next); 
      }
      ~Node() {}
    };  
    
      Node* root;
  };

}

#endif
