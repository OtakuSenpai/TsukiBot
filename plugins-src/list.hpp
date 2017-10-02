#ifndef LIST_HPP
#define LIST_HPP

#include <stdlib.h>

/*
                      I'm a little bit unsure about why you wrote it given the 
                      existence of std::forward_list. However, the general 
                      issues I took with it were insufficient const 
                      correctness, a lack of support for move semantics, a lack 
                      of support for in-place construction, your copy 
                      constructors are EXTREMELY fragile (read: shallow copy of 
                      reference-uncounted pointers), some screwiness in the 
                      nature of your interface (empty is usually used to test 
04:00 < TheDaemoness> emptiness, not cause it, and create seems like it should 
                      be a protected member function). I also don't see any 
                      iterator-creating member functions. Finally... you're 
                      using C++ in this class anyway. Why not nullptr?
*/

// Need TO-DOs :-
// 1)Initializer lists ( vector<int> a{1,2,3};
// 2) Move semantics(currently...it does shallow copy)
// 

template<class T>
class List {

  public:
  
    List() {
      root = NULL;  
    }
    
    List(const size_t& size) {
      size_t tempCounter = size;
      try {
        root = (Node*) calloc(1,sizeof(Node));
        if(!root) throw "Error in class List,cannot create a new Node!\n";
        Node *temp,*prev = root; --tempCounter;
        while(tempCounter != 0) {
		  temp = (Node*) calloc(1,sizeof(Node));
		  prev->_next = temp; prev = temp;
		  --tempCounter;
	    }	       
      }    
      catch(const char* e) {
        printf("Caught exception: \n %s",e);    	
      }
    }
    
    List(const List& other) {
      root = other.root;    
    }

    List(const List* other) {
      root = other->root;     
    }
    
    List& operator= (const List& other) {
      try {
        List* temp = (List*) calloc(1,sizeof(List));
        if(!temp) throw "Error in class List,couldn't create a new node.\n";        
        else { 
          temp._data = other._data;
          temp._next = other._next;        
          return &temp;   
        }    
      }
      catch(const char* e) {
        printf("Caught exception: \n %s",e);    	
      }    
    }
    
    T& operator [] (const size_t& pos) {
	  bool found = false;
	  try {
        if(this->size() < pos)
          throw "Error in class List,trying to search in list which doesnt have that many elements.\n";
        if(root != NULL){
          Node *looper = root;
          for(int i = 0; i<this->size() && looper != NULL; ++i) {
            if(i == pos){
             T& retV = looper->_data; found = true;
             return retV;            
            }
            looper = looper->_next;        
          } 
        }
        else if(!found)
          throw "Error in class List,couldn't find the data at the specified position.\n";  
        else 
          throw "Error in class List,trying to search in an empty list.\n";  
      }
      catch(const char* e) {
        printf("Caught exception: \n %s",e);      
      }              
    }
    
    // Need to add const correctness
    // So tht the class can be used as a const reference or object
    T& operator [] const (const size_t& pos) { 
	  bool found = false;
	  try {
        if(this->size() < pos)
          throw "Error in class List,trying to search in list which doesnt have that many elements.\n";
        if(root != NULL){
          Node *looper = root;
          for(int i = 0; i<this->size() && looper != NULL; ++i) {
            if(i == pos){
             T& retV = looper->_data; found = true;
             return retV;            
            }
            looper = looper->_next;        
          } 
        }
        else if(!found)
          throw "Error in class List,couldn't find the data at the specified position.\n";  
        else 
          throw "Error in class List,trying to search in an empty list.\n";  
      }
      catch(const char* e) {
        printf("Caught exception: \n %s",e);      
      }              
    }	
     
    ~List() { empty(); }   
    
    void pushFront(const T& val) {
      try {
        if(root != NULL) {
          Node *temp = (Node*) calloc(1,sizeof(Node));
          if(!temp) throw "Error in class List,couldn't create a new node.\n";
          else {
            temp->_data = val;
            temp->_next = root;
            root = temp;
          }      
        }
        else create(val);        
      }
      catch(const char* e) {
        printf("Caught exception: \n %s",e);      
      }       
    }    
    
    void pushBack(const T& val) {
      try {
        if(root != NULL) {
          Node *looper = root;
          Node *temp = (Node*) calloc(1,sizeof(Node));
          if(!temp) throw "Error in class List,couldn't create a new node.\n";
          else {
            while(looper->_next != NULL) looper = looper->_next;
            looper->_next = temp;
            temp->_next = NULL; temp->_data = val;
          }
        }
        else create(val);
      }
      catch(const char* e) {
        printf("Caught exception: \n %s",e);      
      }     
    }    
    
    void popFront() {
      try {
        if(root != NULL) {
          Node* temp = root;
          root = root->_next;
          free(temp); temp = NULL;        
        }
        else 
          throw "Error in class List,trying to perform action in an empty list!\n";
      }
      catch(const char* e) {
        printf("Caught exception: \n %s",e);      
      }      
    }    
    
    void popBack() {
      try {
        if(root != NULL) {
          Node *prev,*looper = root;
          while(looper->next != NULL) {
            prev = looper;          	
          	looper = looper->_next;
          }
          free(looper); looper->_next = NULL;
          prev->_next = NULL;        
        }
        else 
          throw "Error in class List,trying to perform action in an empty list!\n";
      }
      catch(const char* e) {
        printf("Caught exception: \n %s",e);      
      }           
    }
    
    void reverse() {
      try {      
        if(root != NULL) {        
          Node *prev = NULL,looper = root,next;
          while(looper != NULL) {
            next = looper->_next;
            looper->_next = prev;
            prev = looper;
            looper = next;
          }
          root = prev;
        }  
        else 
          throw "Error in class List,trying to perform action in an empty list!\n";
      }
      catch(const char* e) {
        printf("Caught exception: \n %s",e);      
      }           
    }
     
    void uniqueIt() {
      try {
        if(root != NULL) {  
          Node *ptr1, *ptr2, *dup;
          ptr1 = root;
 
          while (ptr1 != NULL && ptr1->_next != NULL) {
            ptr2 = ptr1;
 
            while (ptr2->_next != NULL) {
              if (ptr1->_data == ptr2->_next->_data) {
                dup = ptr2->_next;
                ptr2->_next = ptr2->_next->_next;
                free(dup); dup = NULL;
              }
              else ptr2 = ptr2->_next;
            }
            ptr1 = ptr1->_next;
          }
        }
        else if(root == NULL)
          throw "Error in class List,trying to perform action in an empty list!\n";
      }
      catch(const char* e) {
        printf("Caught exception: \n %s",e);      
      }           
    } 
    
    size_t size() const {
      if(root != NULL) {
        Node *looper = root;
        size_t count = 0;
        while(looper != NULL) {
          ++count; looper = looper->_next;          
        }
        return count;        
      }
      else if(root == NULL) return 0;      
    }        
    
    T& at(const size_t& pos) {
      try {
        T retValue;
        if(this->size() < pos) 
          throw "Error in class List,trying to search in list which doesnt have that many elements.\n";
        if(root != NULL) {
          Node *looper = root;
          size_t count = 0;
          while(looper != NULL) {
            if(count == pos) {
              retValue = looper->_data;
              break;           
            }
            ++count; looper = looper->_next;         
          }         
        }
        else if(!retValue)
          throw "Error in class List,couldn't find the data at the specified position.\n";
        else if(root == NULL)
          throw "Error in class List,trying to search in an empty list.\n";
        return retValue;  
      }
      catch(const char* e) {
        printf("Caught exception: \n %s",e);      
      }           
    }
    
    T& at const (const size_t& pos) {
      try {
        T retValue;
        if(this->size() < pos) 
          throw "Error in class List,trying to search in list which doesnt have that many elements.\n";
        if(root != NULL) {
          Node *looper = root;
          size_t count = 0;
          while(looper != NULL) {
            if(count == pos) {
              retValue = looper->_data;
              break;           
            }
            ++count; looper = looper->_next;         
          }         
        }
        else if(!retValue)
          throw "Error in class List,couldn't find the data at the specified position.\n";
        else if(root == NULL) 
          throw "Error in class List,trying to search in an empty list.\n";
        return retValue;  
      }
      catch(const char* e) {
        printf("Caught exception: \n %s",e);      
      }           
    }
    
    void empty() {
      if(root != NULL) {    
        Node* current = root;
        Node* next;
        while (current != NULL) {
          next = current->_next;
          delete current;
          current = next;
        }
        root = NULL; 
	  }
	}     
    
  protected:
    
    void create(const T& value) {
	  try {	
        if(root == NULL) {
          Node *nn = (Node*) calloc(1,sizeof(Node));
          if(!nn) throw "Error in class List,cannot create a new Node!\n";
          nn->_data = value; 
          nn->_next = NULL;
          root = nn; 
        }
        else throw "tryxlist.hpp : line 33,list already exists.\n";
      }
      catch(const char* e) {
        printf("Caught exception: \n %s",e);      
      }  
    }
    
    struct Node { 
      T _data;
      Node* _next;
      
      Node() {}
      Node(const T& val) : _data(val) {}
      Node(const Node& other) {
        _data = other._data;
        _next = other._next;                
      }
      
      Node(const Node* other) {
        _data = other->_data;
        _next = other->_next;                  
      }
      
      Node& operator= (const Node& other) {
        try{
          free();
          Node *temp = (Node*)calloc(1,sizeof(other));
          if(!temp) throw "Error in class List,couldn't create a new node.\n";
          return &temp;
        } 
        catch(const char* e) {
          printf("Caught exception: \n %s",e);                  
        }     
      }
      
      void free() { delete _next; _next = NULL; }  
      T& getData() { return _data; }
      
      ~Node() {}       
    };
    Node *root = NULL;            
};

#endif
