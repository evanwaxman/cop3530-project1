//
//  cbl.h
//  project1
//
//  Created by Evan Waxman on 11/13/17.
//  Copyright © 2017 Evan Waxman. All rights reserved.
//

#include <iostream>
#include "list.h"

#ifndef cbl_h
#define cbl_h

using namespace cop3530;

template <typename L>
class CBL : public List<L> {
    
private:
    L* data;
    size_t head;
    size_t tail;
    size_t init_size;
    size_t curr_size;
    
public:
    CBL(size_t len = 50);  // constructor
    CBL(const CBL &obj);  // copy constructor
    ~CBL();    // deconstructor
    
    void insert(L element, size_t position) override;
    void push_back(L element) override;
    void push_front(L element) override;
    L replace(L element, size_t position) override;
    L remove(size_t position) override;
    L pop_back(void) override;
    L pop_front(void) override;
    L item_at(size_t position) override;
    L peek_back(void) override;
    L peek_front(void) override;
    bool is_empty(void) override;
    bool is_full(void) override;
    size_t length(void) override;
    void clear(void) override;
    bool contains(L element) override;
    void print(void) override;
    L* contents(void) override;
    
    void enlarge_array(void);
    void reduce_array(void);
    size_t dec_index(size_t &i);
    size_t inc_index(size_t &i);
};  // end CBL class

/******************************************
 *   constructor
 ******************************************/
template <typename L>
CBL<L>::CBL(size_t len) {
    init_size = len;
    curr_size = len;
    head = 0;
    tail = 0;
    data = new L[init_size+1];
}

/******************************************
 *   copy constructor
 ******************************************/
template <typename L>
CBL<L>::CBL(const CBL &obj) {
    init_size = obj.init_size;
    curr_size = obj.curr_size;
    head = obj.head;
    tail = obj.tail;
    *data = *obj.data;
}

/******************************************
 *   deconstructor
 ******************************************/
template <typename L>
CBL<L>::~CBL() {
    delete[] data;
}

/******************************************
 *   insert
 ******************************************/
template <typename L>
void CBL<L>::insert(L element, size_t position) {
    size_t begin = head;
    dec_index(begin);
    
    // conceptual head and tail positions
    size_t concept_head = 0;
    size_t concept_tail = length();
    
    // actual insert position
    size_t actual_position = head;
    for (size_t i=0; i<position; i++) {
        inc_index(actual_position);
    }
    
    if (position > concept_tail) {
        throw std::runtime_error("CBL<L>.insert(): insert position is out of list bounds.");
    } else {
        if (is_full()) {
            enlarge_array();
        }
        
        if (position == concept_tail) {
            data[actual_position] = element;
            inc_index(tail);
        } else if (position == concept_head) {
            data[dec_index(head)] = element;
        } else {
            L* oldArray = data;
            data = new L[curr_size];
            
            size_t relative_i = head;
            while (relative_i != actual_position) {
                data[relative_i] = oldArray[relative_i];
                inc_index(relative_i);
            }
            
            data[actual_position] = element;
            
            while (relative_i != tail) {
                inc_index(relative_i);
                data[relative_i] = oldArray[relative_i-1];
            }
            
            delete[] oldArray;
            inc_index(tail);
        }
    }
}

/******************************************
 *   push_back
 ******************************************/
template <typename L>
void CBL<L>::push_back(L element) {
    return insert(element, length());
    /*
    if (is_full()) {
        enlarge_array();
    }
    data[tail] = element;
    tail++;
    */
}

/******************************************
 *   push_front
 ******************************************/
template <typename L>
void CBL<L>::push_front(L element) {
    //size_t i = head;
    //i = dec_index(i);
    //return insert(element, i);
    
    return insert(element, 0);
    
    /*
    if (is_full()) {
        enlarge_array();
    }
    
    L* oldArray = data;
    data = new L[curr_size];
    
    data[0] = element;
    
    for (size_t i=1; i<tail; i++) {
        data[i] = oldArray[i-1];
    }
    
    delete[] oldArray;
    
    tail++;
    */
}

/******************************************
 *   replace
 ******************************************/
template <typename L>
L CBL<L>::replace(L element, size_t position) {
    L oldData;
    size_t begin = head;
    dec_index(begin);
    
    // conceptual head and tail positions
    size_t concept_head = 0;
    size_t concept_tail = length();
    
    // actual insert position
    size_t actual_position = head;
    for (size_t i=0; i<position; i++) {
        inc_index(actual_position);
    }
    
    if (position > concept_tail) {
        throw std::runtime_error("CBL<L>.replace(): replace position is out of list bounds.");
    } else {
        oldData = data[actual_position];
        data[actual_position] = element;
    }
    
    return oldData;
}

/******************************************
 *   remove
 ******************************************/
template <typename L>
L CBL<L>::remove(size_t position) {
    L oldData;
    
    // conceptual head and tail positions
    size_t concept_head = 0;
    size_t concept_tail = length();
    
    // actual insert position
    size_t actual_position = head;
    for (size_t i=0; i<position; i++) {
        inc_index(actual_position);
    }
    
    if (position > concept_tail) {
        throw std::runtime_error("CBL<L>.remove(): remove position is out of list bounds.");
    }
    
    /*
    if ((head > tail) && (position < head) && (position >= tail)) {
        throw std::runtime_error("CBL<L>.remove(): remove position is out of list bounds.");
    } else if ((head < tail) && (position >= tail)) {
        throw std::runtime_error("CBL<L>.remove(): remove position is out of list bounds.");
    }
    */
     
    size_t end = tail;
    if (position == (concept_tail - 1)) {     // remove at end of list
        oldData = data[dec_index(tail)];
    } else if (position == concept_head) {
        oldData = data[head];
        inc_index(head);
    } else {
        L* oldArray = data;
        data = new L[curr_size];
        
        size_t relative_i = head;
        while (relative_i != actual_position) {
            data[relative_i] = oldArray[relative_i];
            inc_index(relative_i);
        }
        
        oldData = oldArray[actual_position];
        
        while (relative_i != tail) {
            inc_index(relative_i);
            data[relative_i] = oldArray[relative_i+1];
        }
        
        delete[] oldArray;
        dec_index(tail);
    }
    
    if ((curr_size >= 2*init_size) && (tail < (curr_size/2))) {
        reduce_array();
    }
    
    return oldData;
}

/******************************************
 *   pop_back
 ******************************************/
template <typename L>
L CBL<L>::pop_back() {
    //size_t i = tail;
    //i = dec_index(i);
    return remove(length()-1);
}

/******************************************
 *   pop_front
 ******************************************/
template <typename L>
L CBL<L>::pop_front() {
    return remove(0);
}

/******************************************
 *   item_at
 ******************************************/
template <typename L>
L CBL<L>::item_at(size_t position) {
    // conceptual head and tail positions
    size_t concept_head = 0;
    size_t concept_tail = length();
    
    // actual insert position
    size_t actual_position = head;
    for (size_t i=0; i<position; i++) {
        inc_index(actual_position);
    }
    
    if (position > concept_tail) {
        throw std::runtime_error("CBL<L>.item_at(): item_at position is out of list bounds.");
    } else {
        return data[actual_position];
    }
/*
    if ((head > tail) && (position < head) && (position >= tail)) {
        throw std::runtime_error("CBL<L>.item_at(): item_at position is out of list bounds.");
    } else if ((head < tail) && (position >= tail)) {
        throw std::runtime_error("CBL<L>.item_at(): item_at position is out of list bounds.");
    } else {
        return data[position];
    }
*/
}

/******************************************
 *   peek_back
 ******************************************/
template <typename L>
L CBL<L>::peek_back() {
    size_t i = tail;
    i = dec_index(i);
    return data[i];
}

/******************************************
 *   peek_front
 ******************************************/
template <typename L>
L CBL<L>::peek_front() {
    return data[head];
}

/******************************************
 *   is_empty
 ******************************************/
template <typename L>
bool CBL<L>::is_empty() {
    if (tail == head) {
        return true;
    }
    return false;
}

/******************************************
 *   is_full
 ******************************************/
template <typename L>
bool CBL<L>::is_full() {
    if (length() == (curr_size-1)) {
        return true;
    } else {
        return false;
    }
}

/******************************************
 *   length
 ******************************************/
template <typename L>
size_t CBL<L>::length() {
    if (head > tail) {
        return ((curr_size - head) + tail);
    }else if (head < tail) {
        return (tail - head);
    }else {
        return 0;
    }
}

/******************************************
 *   clear
 ******************************************/
template <typename L>
void CBL<L>::clear() {
/*
    size_t relative_i = tail;
    dec_index(relative_i);
    //for (size_t i = tail-1; i > 0; i--) {
    while (relative_i != head) {
        remove(relative_i);
        dec_index(relative_i);
    }
    remove(head);
 */
    head = 0;
    tail = 0;
}

/******************************************
 *   contains
 ******************************************/
template <typename L>
bool CBL<L>::contains(L element) {
    size_t relative_i = head;
    //for (size_t i=0; i<tail; i++) {
    while (relative_i != tail) {
        if (data[relative_i] == element) {
            return true;
        }
        inc_index(relative_i);
    }
    
    return false;
}

/******************************************
 *   print
 ******************************************/
template <typename L>
void CBL<L>::print() {
    if(is_empty()) {
        std::cout << "<empty list>" << std::endl;
    } else {
        std::cout << "[";
        
        size_t relative_i = head;
        //for (size_t i=0; i<tail; i++) {
        while (relative_i != tail) {
            std::cout << data[relative_i] << ",";
            inc_index(relative_i);
        }
    }
}

/******************************************
 *   contents
 ******************************************/
template <typename L>
L* CBL<L>::contents() {
    //return data;
    return data;
}

/******************************************
 *   enlarge_array
 ******************************************/
template <typename L>
void CBL<L>::enlarge_array() {
    L* newArray = new L[int(1.5*curr_size)];
    
    size_t relative_i = head;
    //for (size_t i=0; i<curr_size; i++) {
    while (relative_i != tail) {
        newArray[relative_i] = data[relative_i];
        inc_index(relative_i);
    }
    
    delete[] data;
    data = newArray;
    curr_size = int(1.5*curr_size);
}

/******************************************
 *   reduce_array
 ******************************************/
template <typename L>
void CBL<L>::reduce_array() {
    curr_size = int(0.75*curr_size);
    L* newArray = new L[curr_size];
    
    size_t relative_i = head;
    while (relative_i != tail) {
        newArray[relative_i] = data[relative_i];
        inc_index(relative_i);
    }
    
    delete[] data;
    data = newArray;
}

/******************************************
 *   dec_index
 ******************************************/
template <typename L>
size_t CBL<L>::dec_index(size_t &i) {
    if (i-- == 0) {
        i = curr_size-1;
    }
    return i;
}

/******************************************
 *   inc_index
 ******************************************/
template <typename L>
size_t CBL<L>::inc_index(size_t &i) {
    if (++i == curr_size) {
        i = 0;
    }
    return i;
}
#endif /* cbl_h */
