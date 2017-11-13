//
//  ssll.h
//  hw2
//
//  Created by Evan Waxman on 9/12/17.
//  Copyright © 2017 Evan Waxman. All rights reserved.
//

#include <iostream>
#include "list.h"


#ifndef ssll_h
#define ssll_h
using namespace cop3530;

template <typename L>
class SSLL : public List<L> {
    
private:
    Node<L>* head;
    Node<L>* tail;
    
public:
    SSLL();   // constuctor
    SSLL(const SSLL &obj);  // copy constructor
    ~SSLL();    // deconstructor
    
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
    
public:
    template <typename DataL>
    class SSLL_Iter {
    public:
        // type aliases required for C++ iterator compatibility
        using value_type = DataL;
        using reference = DataL&;
        using pointer = DataL*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;
        
        // type aliases for prettier code
        using self_type = SSLL_Iter;
        using self_reference = SSLL_Iter&;
        
    private:
        Node<DataL>* here;
        
        
    public:
        explicit SSLL_Iter( Node<L>* start = nullptr ) : here( start ) {}
        SSLL_Iter( const SSLL_Iter& src ) : here( src.here ) {}
        
        static self_type make_begin( SSLL& n ) {
            self_type i( n.head );
            return i;
        }
        static self_type make_end( SSLL& n ) {
            Node<L>* endptr = nullptr;
            self_type i( endptr );
            return i;
        }
        
        value_type operator*() const { return here->Data(); }
        
        //Node<DataL>* operator->() const { return here; }
        Node<DataL>* operator->() const { return &(operator*()); }
        
        self_reference operator=( SSLL_Iter const& src ) {
            if (this != &src) {
                here = src.here;
            }
            return (*this);
        }
        
        self_reference operator++() {
            if (here->Data()) {
                here = here->Next();
            }
            return (*this);
        } // preincre ment
        
        self_type operator++(int) {
            self_type tmp(*this);
            this = this->Next();
            return tmp;
        } // postincrement
        
        bool operator==( SSLL_Iter<DataL> const& rhs ) const {
            return (here == rhs.here);
        }
        bool operator!=( SSLL_Iter<DataL> const& rhs) const {
            return (here != rhs.here);
        }
    }; // end SSLL_Iter

public:
    //--------------------------------------------------
    // type aliases
    //--------------------------------------------------
    //using size_t = std::size_t; // you may comment out this line if your compiler complains
    using value_type = L;
    using iterator = SSLL_Iter<L>;
    using const_iterator = SSLL_Iter<L const>;
    
    // iterators over a non-const List
    iterator begin() { return iterator::make_begin(*this); }
    iterator end() { return iterator::make_end(*this); }
    
    // iterators over a const List
    const_iterator begin() const { return const_iterator::make_begin(*this); }
    const_iterator end() const { return const_iterator::make_end(*this); }
    
}; // end SSLL

/******************************************
 *   constructor
 ******************************************/
template <typename L>
SSLL<L>::SSLL() {
    head = nullptr;
    tail = nullptr;
}

/******************************************
 *   copy constructor
 ******************************************/
template <typename L>
SSLL<L>::SSLL(const SSLL &obj) {
    *head = *obj.head;
    *tail = *obj.tail;
}

/******************************************
 *   destructer
 ******************************************/
template <typename L>
SSLL<L>::~SSLL() {
    clear();
    delete head;
}

/******************************************
 *   insert
 ******************************************/
template <typename L>
void SSLL<L>::insert(L element, size_t position) {
    Node<L>* newNode = new Node<L>();
    Node<L>* curr = head;
    size_t i = 0;
    
    if (length() < position) {
        throw std::runtime_error("SSLL<L>.insert(): insert position is out of list bounds.");
    } else if (position == 0) { // insert at head of list?
        if (head == NULL) {    // insert in an empty list?
            head = newNode;
            tail = newNode;
            newNode->setData(element);
            newNode->setNext(NULL);
        } else {
            newNode->setNext(head);
            newNode->setData(element);
            head = newNode;
        }
    } else {
        if (length() == position) { // insert at end of list?
            tail = newNode;
        }
        while (++i != position) {
            curr = curr->Next();
        }
        newNode->setNext(curr->Next());
        newNode->setData(element);
        curr->setNext(newNode);
        
    }
}

/******************************************
 *   push_back
 ******************************************/
template <typename L>
void SSLL<L>::push_back(L element) {
    Node<L>* newNode = new Node<L>();
    
    newNode->setData(element);
    newNode->setNext(NULL);
    
    if (head == NULL) {     // list empty?
        head = newNode;
        tail = newNode;
    } else {
        tail->setNext(newNode);
        tail = newNode;
    }
}

/******************************************
 *   push_front
 ******************************************/
template <typename L>
void SSLL<L>::push_front(L element) {
    Node<L>* newNode = new Node<L>();
    
    newNode->setData(element);
    
    if (head == NULL) {     // list empty?
        head = newNode;
        tail = newNode;
        newNode->setNext(NULL);
    } else {
        newNode->setNext(head);
        head = newNode;
    }
}

/******************************************
 *   replace
 ******************************************/
template <typename L>
L SSLL<L>::replace(L element, size_t position) {
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
L SSLL<L>::remove(size_t position) {
    Node<L>* curr = head;
    Node<L>* next = head;
    next = next->Next();
    L oldData;
    size_t i = 0;
    
    if (length() < position) {
        throw std::runtime_error("SSLL<L>.remove(): remove position is out of list bounds.");
    } else if (position == 0) { // remove at start of list?
        head = next;
        oldData = curr->Data();
        delete curr;
        return oldData;
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
        
        oldData = next->Data();
        delete next;
        return oldData;    }
}

/******************************************
 *   pop_back
 ******************************************/
template <typename L>
L SSLL<L>::pop_back() {
    L oldData = remove(this->length()-1);
    return oldData;
}

/******************************************
 *   pop_front
 ******************************************/
template <typename L>
L SSLL<L>::pop_front() {
    L oldData = remove(0);
    return oldData;
}

/******************************************
 *   item_at
 ******************************************/
template <typename L>
L SSLL<L>::item_at(size_t position) {
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
L SSLL<L>::peek_back() {
    return tail->Data();
}

/******************************************
 *   peek_front
 ******************************************/
template <typename L>
L SSLL<L>::peek_front() {
    return head->Data();
}

/******************************************
 *   is_empty
 ******************************************/
template <typename L>
bool SSLL<L>::is_empty() {
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
bool SSLL<L>::is_full() {
    return false;
}

/******************************************
 *   length
 ******************************************/
template <typename L>
size_t SSLL<L>::length() {
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
void SSLL<L>::clear() {
    //size_t len = this->length() - 1;
    size_t len = this->length();
    
    if (len > 0) {
        for (size_t i = len-1; i > 1; i--) {
            this->remove(i);
        }
        this->remove(0);
    }
}

/******************************************
 *   contains
 ******************************************/
template <typename L>
bool SSLL<L>::contains(L element) {
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
void SSLL<L>::print() {
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
L* SSLL<L>::contents() {
    Node<L>* curr = head;
    size_t i = 0;
    L* contents_array = new L[length()];
    
    while (curr) {
        contents_array[i++] = curr->Data();
        curr = curr->Next();
    }
    return contents_array;
}

//}

#endif /* ssll_h */
