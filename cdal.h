//
//  cdal.h
//  project1
//
//  Created by Evan Waxman on 9/17/17.
//  Copyright © 2017 Evan Waxman. All rights reserved.
//

#include <iostream>
#include "list.h"

#ifndef cdal_h
#define cdal_h

using namespace cop3530;

template <typename L>
class CDAL : public List<L> {
    
public:
    CDAL();
    ~CDAL();
    
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
    
private:
    ArrayNode<L>* data;
    size_t tail;
};

/******************************************
 *   constructor
 ******************************************/
template <typename L>
CDAL<L>::CDAL() {
    data = nullptr;
    tail = NULL;
}

/******************************************
 *   destructer
 ******************************************/
template <typename L>
CDAL<L>::~CDAL() {
    //clear();
    ArrayNode<L>* curr = data;
    ArrayNode<L>* prev = curr;
    
    while (curr) {
        curr = curr->Next();
        delete prev;
        prev = curr;
    }
}

/******************************************
 *   insert
 ******************************************/
template <typename L>
void CDAL<L>::insert(L element, size_t position) {
    if (length() < position) {
        throw std::runtime_error("CDAL<L>.insert(): insert position is out of list bounds.");
    } else {
        // create position parameters
        size_t posArrayBin = position / ARRAYSIZE;      // get position array bin num
        size_t posArrayIndex = position - (posArrayBin * ARRAYSIZE);    // get index in position bin
        size_t maxArrayBin = tail / ARRAYSIZE;      // get max array bin num
        size_t maxArrayIndex = tail - (maxArrayBin * ARRAYSIZE);    // get index in max bin
        
        // create first node if list is empty
        if (data == nullptr) {
            ArrayNode<L>* newNode = new ArrayNode<L>();
            data = newNode;
            newNode->setNext(nullptr);
            
            // add new first element
            newNode->editElement(0,element);
            
            tail = 0;
        } else {
            // create node to iterate through list
            ArrayNode<L>* currArrayNode = data;         // point to first array
            
            // iterate through list until positionArrayBin - 1 is reached
            if (posArrayBin != 0) {
                for (size_t i=0; i<posArrayBin-1; i++) {
                    currArrayNode = currArrayNode->Next();
                }
                // check if posArrayBin exists, if not create new arrayNode
                if (currArrayNode->Next() == nullptr) {
                    ArrayNode<L>* newNode = new ArrayNode<L>();
                    newNode->setNext(nullptr);
                    currArrayNode->setNext(newNode);
                }
            
                currArrayNode = currArrayNode->Next();
            }
                
            // keep track of last element in array
            L tempElement1 = currArrayNode->Element(ARRAYSIZE-1);
            
            // shift array elements 1 to the right
            for (size_t i=ARRAYSIZE-2; i>posArrayIndex; --i) {
                currArrayNode->editElement(i+1,currArrayNode->Element(i));
            }
            currArrayNode->editElement(posArrayIndex+1,currArrayNode->Element(posArrayIndex));
            
            // insert new element into array
            currArrayNode->editElement(posArrayIndex,element);
            
            // check if curr array was last array and new element causes overflow (edge case)
            if (maxArrayBin == posArrayBin && maxArrayIndex == (ARRAYSIZE-1)) {
                ArrayNode<L>* newArrayNode = new ArrayNode<L>();
                currArrayNode->setNext(newArrayNode);
                currArrayNode = currArrayNode->Next();
                currArrayNode->setNext(nullptr);
                
                // insert last element from previous array into first element of curr array
                currArrayNode->editElement(0,tempElement1);
            } else {    // iterate through the rest of the arrays, shifting elements to the right 1 index
                // point currArrayNode to next array
                currArrayNode = currArrayNode->Next();
                
                // iterate through each arrayNode
                for (size_t i=posArrayBin+1; i<=maxArrayBin; i++) {
                    // keep track of last element in array
                    L tempElement2 = currArrayNode->Element(ARRAYSIZE-1);
                    
                    // shift array elements 1 to the right
                    for (size_t j=ARRAYSIZE-2; j>0; --j) {
                        currArrayNode->editElement(j+1,currArrayNode->Element(j));
                    }
                    currArrayNode->editElement(1,currArrayNode->Element(0));
                    
                    // insert last element from previous array into first element of curr array
                    currArrayNode->editElement(0,tempElement1);
                    
                    // keep track of last element so it can be inserted into first index of next array
                    tempElement1 = tempElement2;
                    
                    if (i == maxArrayBin) {
                        // if max index is at end of array, allocate new array
                        if (maxArrayIndex == (ARRAYSIZE-1)) {
                            ArrayNode<L>* newArrayNode = new ArrayNode<L>();
                            currArrayNode->setNext(newArrayNode);
                            currArrayNode = currArrayNode->Next();
                            currArrayNode->setNext(nullptr);
                            currArrayNode->editElement(0,tempElement1);
                        }
                    } else {
                        currArrayNode = currArrayNode->Next();
                    }
                }
            }
        
            tail += 1;
        }
    }
}

/******************************************
 *   push_back
 ******************************************/
template <typename L>
void CDAL<L>::push_back(L element) {
/*
    if (is_full()) {
        add_array();
    }
    ArrayNode<L>* curr = data;
    
    while (curr) {
        curr = curr->Next();
    }
    tail += 1;
    curr[tail] = element;
 */
    insert(element, tail+1);
}

/******************************************
 *   push_front
 ******************************************/
template <typename L>
void CDAL<L>::push_front(L element) {
    insert(element, 0);
}

/******************************************
 *   replace
 ******************************************/
template <typename L>
L CDAL<L>::replace(L element, size_t position) {
    if (length() < position) {
        throw std::runtime_error("CDAL<L>.insert(): insert position is out of list bounds.");
    } else {
        // create position parameters
        size_t posArrayBin = position / ARRAYSIZE;      // get position array bin num
        size_t posArrayIndex = position - (posArrayBin * ARRAYSIZE);    // get index in position bin
        
        // create ArrayNode curr
        ArrayNode<L>* currArrayNode = data;
        
        // iterate through list until posArrayBin is found
        for (size_t i=0; i<posArrayBin; i++) {
            currArrayNode = currArrayNode->Next();
        }
        
        // replace element
        currArrayNode->editElement(posArrayIndex, element);
        
        return currArrayNode->Element(posArrayIndex);
    }
}

/******************************************
 *   remove
 ******************************************/
template <typename L>
L CDAL<L>::remove(size_t position) {
    if (length() < position) {
        throw std::runtime_error("CDAL<L>.insert(): insert position is out of list bounds.");
    } else {
        // create position parameters
        size_t posArrayBin = position / ARRAYSIZE;      // get position array bin num
        size_t posArrayIndex = position - (posArrayBin * ARRAYSIZE);    // get index in position bin
        size_t maxArrayBin = tail / ARRAYSIZE;      // get max array bin num
        size_t maxArrayIndex = tail - (maxArrayBin * ARRAYSIZE);    // get index in max bin
        
        // create curr and next array node to iterate through list
        ArrayNode<L>* currArrayNode = data;         // point to first array
        ArrayNode<L>* nextArrayNode = currArrayNode->Next();    // point to second array
        
        // iterate through list until positionArrayBin - 1 is reached
        for (size_t i=0; i<posArrayBin; i++) {
            currArrayNode = currArrayNode->Next();
            nextArrayNode = nextArrayNode->Next();
        }
        
        L removedElement = currArrayNode->Element(posArrayIndex);
        
        // shift array elements 1 to the left
        for (size_t i=posArrayIndex; i<(ARRAYSIZE-1); i++) {
            currArrayNode->editElement(i,currArrayNode->Element(i+1));
        }
        
        // check if next array is null
        if (nextArrayNode != nullptr) {
            // replace last element of curr array with first element in next array
            currArrayNode->editElement((ARRAYSIZE-1),nextArrayNode->Element(0));
        } else {
            // replace last element of curr array with NULL value
            currArrayNode->editElement((ARRAYSIZE-1),NULL);
            tail -= 1;
            
            return removedElement;
        }
        
        // continue shifting elements after posArrayBin to the left 1 bit
        for (size_t i=posArrayBin+1; i<maxArrayBin; i++) {
            currArrayNode = currArrayNode->Next();
            nextArrayNode = nextArrayNode->Next();
            
            // shift array elements 1 to the left
            for (size_t j=0; j<(ARRAYSIZE-1); j++) {
                currArrayNode->editElement(j,currArrayNode->Element(j+1));
            }
            
            // replace last element of curr array with first element in next array
            currArrayNode->editElement((ARRAYSIZE-1),nextArrayNode->Element(0));
        }
        
        // check if last array is now null after shifting
        if (maxArrayIndex != 0) {
            // finish shifting last array
            currArrayNode = currArrayNode->Next();
            nextArrayNode = nextArrayNode->Next();
            for (size_t j=0; j<maxArrayIndex; j++) {
                currArrayNode->editElement(j,currArrayNode->Element(j+1));
            }
            currArrayNode->editElement(maxArrayIndex,NULL);
        } else {
            // delete array and arrayNode
            delete nextArrayNode;
        }
        
        tail -= 1;
        
        return removedElement;
    }
}

/******************************************
 *   pop_back
 ******************************************/
template <typename L>
L CDAL<L>::pop_back() {
    return remove(tail);
}

/******************************************
 *   pop_front
 ******************************************/
template <typename L>
L CDAL<L>::pop_front() {
    return remove(0);
}

/******************************************
 *   item_at
 ******************************************/
template <typename L>
L CDAL<L>::item_at(size_t position) {
    if (position > tail) {
        throw std::runtime_error("CDAL<L>.item_at(): item_at position is out of list bounds.");
    } else {
        // create position parameters
        size_t posArrayBin = position / ARRAYSIZE;      // get position array bin num
        size_t posArrayIndex = position - (posArrayBin * ARRAYSIZE);    // get index in position bin
        
        // create curr and next array node to iterate through list
        ArrayNode<L>* currArrayNode = data;         // point to first array
        
        // iterate through list until positionArrayBin - 1 is reached
        for (size_t i=0; i<posArrayBin; i++) {
            currArrayNode = currArrayNode->Next();
        }
        
        return currArrayNode->Element(posArrayIndex);
    }
}

/******************************************
 *   peek_back
 ******************************************/
template <typename L>
L CDAL<L>::peek_back() {
    return item_at(tail);
}

/******************************************
 *   peek_front
 ******************************************/
template <typename L>
L CDAL<L>::peek_front() {
    return item_at(0);
}

/******************************************
 *   is_empty
 ******************************************/
template <typename L>
bool CDAL<L>::is_empty() {
    if (data == nullptr) {
        return true;
    } else {
        return false;
    }
}

/******************************************
 *   is_full
 ******************************************/
template <typename L>
bool CDAL<L>::is_full() {
    return false;
}

/******************************************
 *   length
 ******************************************/
template <typename L>
size_t CDAL<L>::length() {
    return (tail + 1);
}

/******************************************
 *   clear
 ******************************************/
template <typename L>
void CDAL<L>::clear() {
    size_t maxArrayBin = tail / ARRAYSIZE;      // get max array bin num
    
    ArrayNode<L>* currArrayNode = data;
    ArrayNode<L>* prevArrayNode = data;
    
    for (size_t i=0; i<=maxArrayBin; i++) {
        currArrayNode = currArrayNode->Next();
        delete prevArrayNode;
        prevArrayNode = currArrayNode;
    }
    
    data = nullptr;
    tail = NULL;
}

/******************************************
 *   contains
 ******************************************/
template <typename L>
bool CDAL<L>::contains(L element) {
    size_t maxArrayBin = tail / ARRAYSIZE;      // get max array bin num
    size_t maxArrayIndex = tail - (maxArrayBin * ARRAYSIZE);    // get index in max bin
    
    ArrayNode<L>* currArrayNode = data;
    
    for (size_t i=0; i<maxArrayBin; i++) {
        for (size_t j=0; j<=ARRAYSIZE; j++) {
            if (currArrayNode->Element(j) == element) {
                return true;
            }
        }
        currArrayNode = currArrayNode->Next();
    }
    
    for (size_t j=0; j<=maxArrayIndex; j++) {
        if (currArrayNode->Element(j) == element) {
            return true;
        }
    }
    
    return false;
}

/******************************************
 *   print
 ******************************************/
template <typename L>
void CDAL<L>::print() {
    if (data == nullptr) {
        std::cout << "<empty list>" << std::endl;
    } else {
        ArrayNode<L>* currArrayNode = data;
        
        size_t maxArrayBin = tail / ARRAYSIZE;      // get max array bin num
        size_t maxArrayIndex = tail - (maxArrayBin * ARRAYSIZE);    // get index in max bin
        
        std::cout << "[";
        for (size_t i=0; i<maxArrayBin; i++) {
            for (size_t j=0; j<ARRAYSIZE; j++) {
                std::cout << currArrayNode->Element(j) << ", ";
            }
            currArrayNode = currArrayNode->Next();
        }
        
        // print out last array bin, stopping at tail
        for (size_t i=0; i<maxArrayIndex; i++) {
            std::cout << currArrayNode->Element(i) << ", ";
        }
        
        std::cout << currArrayNode->Element(maxArrayIndex) << "]" << std::endl;
    }
}

/******************************************
 *   contents
 ******************************************/
template <typename L>
L* CDAL<L>::contents() {
    ArrayNode<L>* currArrayNode = data;
    
    L* contentArray = new L[tail+1];
    
    size_t maxArrayBin = tail / ARRAYSIZE;      // get max array bin num
    size_t maxArrayIndex = tail - (maxArrayBin * ARRAYSIZE);    // get index in max bin
    
    size_t index = 0;
    
    for (size_t i=0; i<maxArrayBin; i++) {
        for (size_t j=0; j<ARRAYSIZE; j++) {
            contentArray[index++] = currArrayNode->Element(j);
        }
        currArrayNode = currArrayNode->Next();
    }
    
    for (size_t j=0; j<=maxArrayIndex; j++) {
        contentArray[index++] = currArrayNode->Element(j);
    }
    
    return contentArray;
}

#endif /* cdal_h */
