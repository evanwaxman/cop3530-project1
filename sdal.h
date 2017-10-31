//
//  sdal.h
//  project1
//
//  Created by Evan Waxman on 9/16/17.
//  Copyright © 2017 Evan Waxman. All rights reserved.
//

#include <iostream>
#include "list.h"


#ifndef sdal_h
#define sdal_h

using namespace cop3530;

template <typename L>
class SDAL : public List<L> {
    
public:
    SDAL(size_t len = 50);
    ~SDAL();
    
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
    
private:
    L* array;
    L* data;
    size_t tail;
    size_t size;
};

/******************************************
 *   constructor
 ******************************************/
template <typename L>
SDAL<L>::SDAL(size_t len) {
    array = new L[size];
    tail = 0;
    data = NULL;
    size = len;
}

/******************************************
 *   constructor
 ******************************************/
template <typename L>
SDAL<L>::~SDAL() {
    delete[] data;
}

/******************************************
 *   insert
 ******************************************/
template <typename L>
void SDAL<L>::insert(L element, size_t position) {
    if (length() < position) {
        throw std::runtime_error("SSLL<L>.replace(): replace position is out of list bounds.");
    } else {
        if (is_full()) {
            enlarge_array();
        }
        
        if (position != tail) {
            L* oldArray = data;
            data = new L[size];
            
            for (size_t i=0; i<position; i++) {
                data[i] = oldArray[i];
            }
            
            data[position] = element;
            
            for (size_t i=position; i<length(); i++) {
                data[i+1] = oldArray[i];
            }
            
            delete[] oldArray;
        } else {
            data[position] = element;
        }
        tail = tail+1;
    }
}

/******************************************
 *   push_back
 ******************************************/
template <typename L>
void SDAL<L>::push_back(L element) {
    if (is_full()) {
        enlarge_array();
    }
    tail = tail+1;
    data[tail] = element;
}

/******************************************
 *   push_front
 ******************************************/
template <typename L>
void SDAL<L>::push_front(L element) {
    if (is_full()) {
        enlarge_array();
    } else if (is_empty()) {
        data = array;
        data[0] = element;
        return;
    }
    
    tail = tail+1;
    L* oldArray = data;
    data = new L[size];
    
    data[0] = element;
    
    size_t limit = length();
    for (size_t i=1; i<limit; i++) {
        data[i] = oldArray[i-1];
    }
    
    delete[] oldArray;
}

/******************************************
 *   replace
 ******************************************/
template <typename L>
L SDAL<L>::replace(L element, size_t position) {
    L oldData;
    if (length() < position) {
        throw std::runtime_error("SSLL<L>.replace(): replace position is out of list bounds.");
    } else {
        oldData = data[position];
        data[position] = element;
    }
    
    return oldData;
}

/******************************************
 *   remove
 ******************************************/
template <typename L>
L SDAL<L>::remove(size_t position) {
    L oldData;
    if (length() < position) {
        throw std::runtime_error("SSLL<L>.replace(): replace position is out of list bounds.");
    } else if (position == tail) {
        oldData = data[tail];
        tail -= 1;
    } else {
        L* oldArray = data;
        oldData = oldArray[position];
        //tail -= 1;
        data = new L[size];
        
        size_t limit = length();
        for (size_t i=0; i<position; i++) {
            data[i] = oldArray[i];
        }
        
        for (size_t i=position; i<limit; i++) {
            data[i] = oldArray[i+1];
        }
        tail -= 1;
    }
    
    if ((size >= 100) && (tail <50)) {
        reduce_array();
    }
    
    return oldData;
}

/******************************************
 *   pop_back
 ******************************************/
template <typename L>
L SDAL<L>::pop_back() {
    return remove(tail);
}

/******************************************
 *   pop_front
 ******************************************/
template <typename L>
L SDAL<L>::pop_front() {
    return remove(0);
}

/******************************************
 *   item_at
 ******************************************/
template <typename L>
L SDAL<L>::item_at(size_t position) {
    return data[position];
}

/******************************************
 *   peek_back
 ******************************************/
template <typename L>
L SDAL<L>::peek_back() {
    return data[tail];
}

/******************************************
 *   peek_front
 ******************************************/
template <typename L>
L SDAL<L>::peek_front() {
    return data[0];
}

/******************************************
 *   is_empty
 ******************************************/
template <typename L>
bool SDAL<L>::is_empty() {
    if (!length()) {
        return true;
    } else {
        return false;
    }
}

/******************************************
 *   is_full
 ******************************************/
template <typename L>
bool SDAL<L>::is_full() {
    if (length() == size) {
        return true;
    } else {
        return false;
    }
}

/******************************************
 *   length
 ******************************************/
template <typename L>
size_t SDAL<L>::length() {
    if (data == NULL) {
        return 0;
    } else {
        return (tail+1);
    }
}

/******************************************
 *   clear
 ******************************************/
template <typename L>
void SDAL<L>::clear() {
    for (size_t i = tail; i > 0; i--) {
        remove(i);
    }
    remove(0);
}

/******************************************
 *   contains
 ******************************************/
template <typename L>
bool SDAL<L>::contains(L element) {
    for (size_t i=0; i<=tail; i++) {
        if (data[i] == element) {
            return true;
        }
    }
    
    return false;
}

/******************************************
 *   print
 ******************************************/
template <typename L>
void SDAL<L>::print() {
    if(is_empty()) {
        std::cout << "<empty list>" << std::endl;
    } else {
        std::cout << "[";
        
        for (size_t i=0; i<tail; i++) {
            std::cout << data[i] << ",";
        }
        
        std::cout << data[tail] << "]" << std::endl;
    }
}

/******************************************
 *   contents
 ******************************************/
template <typename L>
L* SDAL<L>::contents() {
    return data;
}

/******************************************
 *   enlarge_array
 ******************************************/
template <typename L>
void SDAL<L>::enlarge_array() {
    L* newArray = new L[int(1.5*size)];
    for (size_t i=0; i<size; i++) {
        newArray[i] = data[i];
    }
    delete[] data;
    data = newArray;
}

/******************************************
 *   reduce_array
 ******************************************/
template <typename L>
void SDAL<L>::reduce_array() {
    size = int(0.75*size);
    L* newArray = new L[size];
    for (size_t i=0; i<=tail; i++) {
        newArray[i] = data[i];
    }
    delete[] data;
    data = newArray;
}

#endif /* sdal_h */
