//
//  psll.h
//  project1
//
//  Created by Evan Waxman on 9/13/17.
//  Copyright © 2017 Evan Waxman. All rights reserved.
//

#include <iostream>
#include "list.h"

#ifndef psll_h
#define psll_h

using namespace cop3530;

template <typename L>
class PSLL : public List<L> {
    
public:
    PSLL();
    ~PSLL();
    
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
    
    void print_free_list(void);
    size_t length_free_list(void);
    void allocate_node(void);
    void deallocate_node(void);
    
private:
    Node<L>* head;
    Node<L>* tail;
    Node<L>* headFree;
};

/******************************************
 *   constructor
 ******************************************/
template <typename L>
PSLL<L>::PSLL() {
    head = NULL;
    tail = NULL;
    
    // allocate first free list node
    Node<L>* newNode = new Node<L>();
    newNode->setData(NULL);
    newNode->setNext(NULL);
    headFree = newNode;
    
    // allocate rest of free list
    for (size_t i = 1; i < 10; i++) {
        allocate_node();
    }
}

/******************************************
 *   destructer
 ******************************************/
template <typename L>
PSLL<L>::~PSLL() {
    clear();
    delete head;
    delete headFree;
}

/******************************************
 *   insert
 ******************************************/
template <typename L>
void PSLL<L>::insert(L element, size_t position) {
    Node<L>* curr = head;
    Node<L>* next = head;
    size_t i = 0;
    
    if (is_full()) {  // free list empty?
        allocate_node();
    }
    
    if (length() < position) {
        throw std::runtime_error("SSLL<L>.insert(): insert position is out of list bounds.");
    } else if (position == 0) { // insert at head of list?
        if (head == NULL) {     // insert in an empty list?
            head = headFree;
            tail = headFree;
            headFree = headFree->Next();
            head->setData(element);
            head->setNext(NULL);
        } else {
            curr = headFree;
            headFree = headFree->Next();
            curr->setNext(head);
            head = curr;
            head->setData(element);
        }
    } else {
        if (length() == position) { // insert at end of list?
            tail = headFree;
        }
        //next = next->Next();
        while (++i != position) {
            curr = curr->Next();
            //next = next->Next();
        }
        next = headFree;
        headFree = headFree->Next();
        next->setNext(curr->Next());
        next->setData(element);
        curr->setNext(next);
    }
}

/******************************************
 *   push_back
 ******************************************/
template <typename L>
void PSLL<L>::push_back(L element) {
    if (is_full()) {  // free list empty?
        allocate_node();
    }
    
    if (head == NULL) {
        head = headFree;
        tail = head;
        headFree = headFree->Next();
        head->setData(element);
        head->setNext(NULL);
    } else {
        tail->setNext(headFree);
        tail = headFree;
        headFree = headFree->Next();
        tail->setData(element);
        tail->setNext(NULL);
    }
}

/******************************************
 *   push_front
 ******************************************/
template <typename L>
void PSLL<L>::push_front(L element) {
    if (is_full()) {  // free list empty?
        allocate_node();
    }
    
    if (head == NULL) {     // insert in an empty list?
        head = headFree;
        tail = head;
        headFree = headFree->Next();
        head->setData(element);
        head->setNext(NULL);
    } else {
        Node<L>* curr = headFree;
        headFree = headFree->Next();
        curr->setNext(head);
        head = curr;
        head->setData(element);
    }
}

/******************************************
 *   replace
 ******************************************/
template <typename L>
L PSLL<L>::replace(L element, size_t position) {
    Node<L>* curr = head;
    size_t i = 0;
    L oldData;
    
    if (length() < position) {
        throw std::runtime_error("SSLL<L>.replace(): replace position is out of list bounds.");
    } else if (position == 0) { // replace at start of list?
        oldData = curr->Data();
        curr->setData(element);
    } else {
        while (i++ != position) {
            curr = curr->Next();
        }
        
        oldData = curr->Data();
        curr->setData(element);
    }
    return oldData;
}

/******************************************
 *   remove
 ******************************************/
template <typename L>
L PSLL<L>::remove(size_t position) {
    Node<L>* curr = head;
    Node<L>* next = head;
    next = next->Next();
    L oldData;
    size_t i = 0;
    
    if (length() < position) {
        throw std::runtime_error("SSLL<L>.remove(): remove position is out of list bounds.");
    } else if (position == 0) { // remove at start of list?
        if (head == tail) {
            head = NULL;
            tail = NULL;
        } else {
            head = next;
        }
        oldData = curr->Data();
        curr->setNext(headFree);
        curr->setData(NULL);
        headFree = curr;
    } else {
        position = position - 1;
        while (i++ != position) {
            curr = curr->Next();
            next = next->Next();
        }
        curr->setNext(next->Next());
        if(next == tail) {
            tail = curr;
        }
        
        next->setNext(headFree);
        oldData = next->Data();
        next->setData(NULL);
        headFree = next;
    }
    
    if (length() >= 100 && length_free_list() > 50) {
        deallocate_node();
    }
    
    return oldData;
}

/******************************************
 *   pop_back
 ******************************************/
template <typename L>
L PSLL<L>::pop_back() {
    L oldData = remove(this->length()-1);
    return oldData;
}

/******************************************
 *   pop_front
 ******************************************/
template <typename L>
L PSLL<L>::pop_front() {
    L oldData = remove(0);
    return oldData;
}

/******************************************
 *   item_at
 ******************************************/
template <typename L>
L PSLL<L>::item_at(size_t position) {
    Node<L>* curr = head;
    size_t i = 0;
    
    if (length() <= position) {
        throw std::runtime_error("SSLL<L>.item_at(): item_at position is out of list bounds.");
    } else {
        while (i++ != position) {
            curr = curr->Next();
        }
        return curr->Data();
    }
}

/******************************************
 *   peek_back
 ******************************************/
template <typename L>
L PSLL<L>::peek_back() {
    return tail->Data();
}

/******************************************
 *   peek_front
 ******************************************/
template <typename L>
L PSLL<L>::peek_front() {
    return head->Data();
}

/******************************************
 *   is_empty
 ******************************************/
template <typename L>
bool PSLL<L>::is_empty() {
    if(head == tail) {
        return true;
    } else {
        return false;
    }
}

/******************************************
 *   is_full
 ******************************************/
template <typename L>
bool PSLL<L>::is_full() {
    if (length_free_list()) {
        return false;
    } else {
        return true;
    }
}

/******************************************
 *   length
 ******************************************/
template <typename L>
size_t PSLL<L>::length() {
    Node<L>* curr = head;
    size_t len = 0;
    
    while (curr) {
        curr = curr->Next();
        len++;
    }
    
    return len;
}

/******************************************
 *   clear
 ******************************************/
template <typename L>
void PSLL<L>::clear() {
    size_t len = this->length() - 1;
    for (size_t i = len; i > 0; i--) {
        this->remove(i);
    }
    this->remove(0);
}

/******************************************
 *   contains
 ******************************************/
template <typename L>
bool PSLL<L>::contains(L element) {
    Node<L>* curr = head;
    
    while (curr) {
        if (curr->Data() == element) {
            return true;
        } else {
            curr = curr->Next();
        }
    }
    
    return false;
}

/******************************************
 *   print
 ******************************************/
template <typename L>
void PSLL<L>::print() {
    if (head == NULL) {
        std::cout << "<empty list>" << std::endl;
    } else {
        Node<L>* curr = head;
        
        std::cout << "[";
        while (curr != tail) {
            std::cout << curr->Data() << ", ";
            curr = curr->Next();
        }
        std::cout << curr->Data() << "]" << std::endl;
    }
}

/******************************************
 *   contents
 ******************************************/
template <typename L>
L* PSLL<L>::contents() {
    Node<L>* curr = head;
    size_t i = 0;
    L* contents_array = new L[length()];
    
    while (curr) {
        contents_array[i++] = curr->Data();
        curr = curr->Next();
    }
    return contents_array;
}

/******************************************
 *   print_free_list
 ******************************************/
template <typename L>
void PSLL<L>::print_free_list() {
    if (headFree == NULL) {
        std::cout << "<empty free list>" << std::endl;
    } else {
        Node<L>* curr = headFree;
        size_t i = 0;
        std::cout << "[";
        while (curr) {
            std::cout << i++ << " ";
            curr = curr->Next();
        }
        std::cout << "]" << std::endl;
    }
}

/******************************************
 *   length_free_list
 ******************************************/
template <typename L>
size_t PSLL<L>::length_free_list() {
    Node<L>* curr = headFree;
    size_t len = 0;
    
    while (curr) {
        curr = curr->Next();
        len++;
    }
    
    return len;
}

/******************************************
 *   allocate_node
 ******************************************/
template <typename L>
void PSLL<L>::allocate_node() {
    Node<L>* newNode = new Node<L>;
    newNode->setData(NULL);
    newNode->setNext(headFree);
    headFree = newNode;
}

/******************************************
 *   deallocate_node
 ******************************************/
template <typename L>
void PSLL<L>::deallocate_node() {
    Node<L>* curr = headFree;
    headFree = headFree->Next();
    
    delete curr;
}


#endif /* psll_h */
