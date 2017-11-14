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
    
private:
    L* data;
    size_t tail;
    size_t init_size;
    size_t curr_size;
    
public:
    SDAL(size_t len = 50);  // constructor
    SDAL(const SDAL &obj);  // copy constructor
    ~SDAL();    // deconstructor
    
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
    
public:
    template <typename DataL>
    class SDAL_Iter {
    public:
        // type aliases required for C++ iterator compatibility
        using value_type = DataL;
        using reference = DataL&;
        using pointer = DataL*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;
        
        // type aliases for prettier code
        using self_type = SDAL_Iter;
        using self_reference = SDAL_Iter&;
        
    private:
        L* here;
        //size_t index;
        
    public:
        explicit SDAL_Iter( L* start = nullptr ) : here( start ) {}
        SDAL_Iter( L* src, size_t i) : here( &src[i+1] ) {}
        
        static self_type make_begin( SDAL& n ) {
            self_type i( n.data );
            return i;
        }
        static self_type make_end( SDAL& n ) {
            //Node<L>* endptr = nullptr;
            self_type i( n.data, n.tail );
            return i;
        }
        
        value_type operator*() const { return here->Data(); }
        DataL* operator->() const { return here; }
        
        self_reference operator=( SDAL_Iter const& src ) {
            if (this != &src) {
                here = src.here;
            }
            return (*this);
        }
        
        self_reference operator++() {
            if (here) {
                here++;
            }
            return (*this);
        } // preincre ment
        
        self_type operator++(int) {
            self_type tmp(*this);
            this++;
            return tmp;
        } // postincrement
        
        bool operator==( SDAL_Iter<DataL> const& rhs ) const {
            return (here == rhs.here);
        }
        bool operator!=( SDAL_Iter<DataL> const& rhs) const {
            return (here != rhs.here);
        }
        
        // return iterator data function
        value_type data() { return *here; }
        
    }; // end SDAL_Iter
    
public:
    //--------------------------------------------------
    // type aliases
    //--------------------------------------------------
    //using size_t = std::size_t; // you may comment out this line if your compiler complains
    using value_type = L;
    using iterator = SDAL_Iter<L>;
    using const_iterator = SDAL_Iter<L const>;
    
    // iterators over a non-const List
    iterator begin() { return iterator::make_begin(*this); }
    iterator end() { return iterator::make_end(*this); }
    
    // iterators over a const List
    const_iterator begin() const { return const_iterator::make_begin(*this); }
    const_iterator end() const { return const_iterator::make_end(*this); }

};  // end SDAL

/******************************************
 *   constructor
 ******************************************/
template <typename L>
SDAL<L>::SDAL(size_t len) {
    init_size = len;
    curr_size = len;
    tail = 0;
    data = new L[init_size+1];
}

/******************************************
 *   copy constructor
 ******************************************/
template <typename L>
SDAL<L>::SDAL(const SDAL &obj) {
    init_size = obj.init_size;
    curr_size = obj.curr_size;
    tail = obj.tail;
    *data = *obj.data;
}

/******************************************
 *   deconstructor
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
        
        if (position != (tail-1)) {
            L* oldArray = data;
            data = new L[curr_size];
            
            for (size_t i=0; i<position; i++) {
                data[i] = oldArray[i];
            }
            
            data[position] = element;
            
            for (size_t i=position; i<tail; i++) {
                data[i+1] = oldArray[i];
            }
            
            delete[] oldArray;
        } else {
            data[position] = element;
        }
        tail++;
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
    data[tail] = element;
    tail++;
}

/******************************************
 *   push_front
 ******************************************/
template <typename L>
void SDAL<L>::push_front(L element) {
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
    if (length() <= position) {
        throw std::runtime_error("SSLL<L>.replace(): remove position is out of list bounds.");
    } else if (position == (tail-1)) {
        oldData = data[tail-1];
        tail--;
    } else {
        L* oldArray = data;
        oldData = oldArray[position];
        data = new L[curr_size];
        
        for (size_t i=0; i<position; i++) {
            data[i] = oldArray[i];
        }
        
        for (size_t i=position; i<(tail-1); i++) {
            data[i] = oldArray[i+1];
        }
        delete[] oldArray;
        tail--;
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
L SDAL<L>::pop_back() {
    return remove(tail-1);
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
    return data[tail-1];
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
    if (tail) {
        return false;
    }
    return true;
}

/******************************************
 *   is_full
 ******************************************/
template <typename L>
bool SDAL<L>::is_full() {
    //return false;
    
    if (length() == curr_size) {
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
    return tail;
}

/******************************************
 *   clear
 ******************************************/
template <typename L>
void SDAL<L>::clear() {
    for (size_t i = tail-1; i > 0; i--) {
        remove(i);
    }
    remove(0);
    tail = 0;
}

/******************************************
 *   contains
 ******************************************/
template <typename L>
bool SDAL<L>::contains(L element) {
    for (size_t i=0; i<tail; i++) {
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
        
        //std::cout << data[tail] << "]" << std::endl;
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
    L* newArray = new L[int(1.5*curr_size)];
    for (size_t i=0; i<curr_size; i++) {
        newArray[i] = data[i];
    }
    delete[] data;
    data = newArray;
    curr_size = int(1.5*curr_size);
}

/******************************************
 *   reduce_array
 ******************************************/
template <typename L>
void SDAL<L>::reduce_array() {
    curr_size = int(0.75*curr_size);
    L* newArray = new L[curr_size];
    for (size_t i=0; i<tail; i++) {
        newArray[i] = data[i];
    }
    delete[] data;
    data = newArray;
}

#endif /* sdal_h */
