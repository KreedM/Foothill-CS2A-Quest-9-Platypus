// Derek Meng

// String_List.h

#ifndef String_List_h
#define String_List_h

#include <iostream>
#include <sstream>

class String_List {
  private:
    struct Node {
      std::string data;
      Node *next;
      Node(std::string s = "") : data(s), next(nullptr) {}
    }; 

    Node *_head, *_tail, *_prev_to_current;
    size_t _size;

  public:
    String_List() {
      _head = new struct Node("_SENTINEL_");
      _tail = _head;
      _prev_to_current = _head;
      _size = 0;
    }

    ~String_List() {
      clear();
      delete _head;
    }

    String_List* insert_at_current(std::string s) {
      //if(s.compare(_head->data) == 0) 
      //  _head->data += "_";

      Node *temp = new Node(s);
      temp -> next = _prev_to_current -> next;
      _prev_to_current -> next = temp;

      if(_prev_to_current == _tail) 
        _tail = temp;
      
      ++_size;

      return this;
    }

    String_List* push_back(std::string s) {
      Node *temp = _prev_to_current;
      _prev_to_current = _tail;
      insert_at_current(s);
      _prev_to_current = temp;

      return this;
    }

    String_List* push_front(std::string s) {
      Node *temp = _prev_to_current;
      _prev_to_current = _head;
      insert_at_current(s);
      _prev_to_current = temp;

      return this;
    }

    String_List* advance_current() {
      if(_prev_to_current -> next == nullptr)
        return nullptr;
      else {
        _prev_to_current = _prev_to_current -> next;
            
        return this;   
      }   
    }

    std::string get_current() const {
      if(_prev_to_current -> next == nullptr)
        return "_SENTINEL_";
      else 
        return _prev_to_current -> next -> data;
    }

    String_List* remove_at_current() {
      if(_prev_to_current -> next != nullptr) {
        Node *temp = _prev_to_current -> next;
        _prev_to_current -> next = temp -> next;

        if(_tail == temp) 
          _tail = _prev_to_current;

        delete temp;
        --_size;

        return this;
      }
      else
        return nullptr;
    }

    size_t get_size() const {
      return _size;
    }

    String_List* rewind() {
      _prev_to_current = _head;
      
      return this;
    }

    void clear() {
      rewind(); //Already resets _prev_to_current
     
      while(remove_at_current() != nullptr) {} //Also resets _tail and takes care of _head
    }

    std::string& find_item(std::string s) const { 
      Node *index = _head -> next;

      while(index != nullptr) {
        if((index -> data).compare(s) == 0) 
          return index -> data;

        index = index -> next;
      }

      static std::string sentinel = "_SENTINEL_";
      return sentinel;
    }

    std::string to_string() const {
      std::ostringstream oss;
      
      oss << "# String_List - " << _size << " entries total. Starting at cursor:\n";

      char its = 0;
      Node *index = _head -> next;

      while(index != nullptr) {
        oss << index -> data << "\n";

        if(++its == 25) {
          oss << "...\n";
          break;
        }

        index = index -> next;
      }
      
      return oss.str();
    }

    friend class Tests; // Don't remove this line
};

#endif /* String_List_h */
