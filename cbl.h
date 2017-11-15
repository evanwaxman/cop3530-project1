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
    
public:
    template <typename DataL>
    class CBL_Iter {
    public:
        // type aliases required for C++ iterator compatibility
        using value_type = DataL;
        using reference = DataL&;
        using pointer = DataL*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;
        
        // type aliases for prettier code
        using self_type = CBL_Iter;
        using self_reference = CBL_Iter&;
        
    private:
        L* here;
        size_t curr_index;
        size_t size;
        
    public:
        explicit CBL_Iter( L* src = nullptr, size_t h = 0, size_t c = 0, size_t s = 0) : here( &src[h] ), curr_index( c ), size( s ) {}
        CBL_Iter(const CBL_Iter& src) : here( src.here ), curr_index( src.curr_index ), size( src.size ) {}
        
        static self_type make_begin( CBL& n ) {
            self_type i( n.data, n.head, n.head, n.curr_size );
            return i;
        }
        static self_type make_end( CBL& n ) {
            self_type i( n.data, n.head, n.tail, n.curr_size );
            return i;
        }
        
        reference operator*() const { return here[curr_index]; }
        DataL* operator->() const { return here; }
        
        self_reference operator=( CBL_Iter const& src ) {
            if (this != &src) {
                here = src.here;
                curr_index = src.curr_index;
                size = src.size;
            }
            return (*this);
        }
        
        self_reference operator++() {
            curr_index = (++curr_index) % size;
            return (*this);
        } // preincrement
        
        self_type operator++(int) {
            self_type tmp(*this);
            curr_index = (++curr_index) % size;
            return tmp;
        } // postincrement
        
        bool operator==( CBL_Iter<DataL> const& rhs ) const {
            return (here[curr_index] == rhs.here[curr_index]);
        }
        bool operator!=( CBL_Iter<DataL> const& rhs) const {
            return (here[curr_index] != rhs.here[curr_index]);
        }
        
    }; // end CBL_Iter
    
public:
    //--------------------------------------------------
    // type aliases
    //--------------------------------------------------
    //using size_t = std::size_t; // you may comment out this line if your compiler complains
    using value_type = L;
    using iterator = CBL_Iter<L>;
    using const_iterator = CBL_Iter<L const>;
    
    // iterators over a non-const List
    iterator begin() { return iterator::make_begin(*this); }
    iterator end() { return iterator::make_end(*this); }
    
    // iterators over a const List
    const_iterator begin() const { return const_iterator::make_begin(*this); }
    const_iterator end() const { return const_iterator::make_end(*this); }

    
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
}

/******************************************
 *   push_front
 ******************************************/
template <typename L>
void CBL<L>::push_front(L element) {
    return insert(element, 0);
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
    head = 0;
    tail = 0;
}

/******************************************
 *   contains
 ******************************************/
template <typename L>
bool CBL<L>::contains(L element) {
    size_t relative_i = head;
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
    size_t old_size = curr_size;
    curr_size = int(1.5*curr_size);
    L* newArray = new L[curr_size];
    
    size_t i = head;
    while (i % old_size != tail) {
        newArray[i % curr_size] = data[i % old_size];
        i++;
    }
    
    tail = i % curr_size;
    delete[] data;
    data = newArray;
}

/******************************************
 *   reduce_array
 ******************************************/
template <typename L>
void CBL<L>::reduce_array() {
    size_t old_size = curr_size;
    curr_size = int(0.75*curr_size);
    L* newArray = new L[curr_size];
    
    size_t i = head;
    while (i % old_size != tail) {
        newArray[i % curr_size] = data[i % old_size];
        i++;
    }
    
    head = head % curr_size;
    tail = i % curr_size;
    delete[] data;
    data = newArray;
    
    
    /*
    curr_size = int(0.75*curr_size);
    L* newArray = new L[curr_size];
    
    size_t relative_i = head;
    while (relative_i != tail) {
        newArray[relative_i] = data[relative_i];
        inc_index(relative_i);
    }
    
    delete[] data;
    data = newArray;
     */
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
