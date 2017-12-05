//
//  cdal.h
//  project1
//
//  Created by Evan Waxman on 9/17/17.
//  Copyright © 2017 Evan Waxman. All rights reserved.
//

#include <iostream>
#include "List.h"

#ifndef cdal_h
#define cdal_h

namespace cop3530 {

    template <typename L>
    class CDAL : public List<L> {
        
    private:
        ArrayNode<L>* data;
        size_t tail;
        
    public:
        CDAL();     // constructor
        CDAL(const CDAL &obj);  // copy constructor
        CDAL(CDAL&& other);     // move constructor
        CDAL& operator=(CDAL&& other) {     // move constructor
            if (this != &other) {
                delete data;
                delete tail;
                
                *data = *other.data;
                tail = other.tail;
                
                other.data = nullptr;
                other.tail = 0;
            }
            
            return *this;
        }
        ~CDAL();    // deconstructor
        
        //bool compare(L d1, L d2) override;
        
        void insert(L element, size_t position) override;
        void push_back(L element) override;
        void push_front(L element) override;
        L replace(L element, size_t position) override;
        L remove(size_t position) override;
        L pop_back(void) override;
        L pop_front(void) override;
        L& item_at(size_t position) override;
        L& peek_back(void) override;
        L& peek_front(void) override;
        bool is_empty(void) override;
        bool is_full(void) override;
        size_t length(void) override;
        void clear(void) override;
        //bool contains(L element) override;
        bool contains(L element, bool (*compare)(const L&, const L&)) override;
        void print(std::ostream&) override;
        L* contents(void) override;
        
    public:
        template <typename DataL>
        class CDAL_Iter {
        public:
            // type aliases required for C++ iterator compatibility
            using value_type = DataL;
            using reference = DataL&;
            using pointer = DataL*;
            using difference_type = std::ptrdiff_t;
            using iterator_category = std::forward_iterator_tag;
            
            // type aliases for prettier code
            using self_type = CDAL_Iter;
            using self_reference = CDAL_Iter&;
            
        private:
            size_t here;
            ArrayNode<L>* node;
            
        public:
            explicit CDAL_Iter(ArrayNode<L>* src = nullptr, size_t i = 0) : here( i ), node( src ) {}
            CDAL_Iter(const CDAL_Iter& src) : here( src.here ), node( src.node ) {}
            
            static self_type make_begin( CDAL& n ) {
                self_type i( n.data, 0 );
                return i;
            }
            static self_type make_end( CDAL& n ) {
                size_t maxArrayBin = (n.tail-1) / ARRAYSIZE;      // get max array bin num
                size_t maxArrayIndex = (n.tail-1) - (maxArrayBin * ARRAYSIZE);    // get index in max bin
                
                ArrayNode<L>* currArrayNode = n.data;
                
                for (size_t i=0; i<maxArrayBin; i++) {
                    currArrayNode = currArrayNode->next;
                }
                
                self_type i( currArrayNode, maxArrayIndex );
                return i;
            }
            
            reference operator*() const { return (node->array[here]); }
            ArrayNode<L>* operator->() const { return node; }
            
            self_reference operator=( CDAL_Iter const& src ) {
                if (this != &src) {
                    here = src.here;
                    node = src.node;
                }
                return (*this);
            }
            
            self_reference operator++() {
                if (here != (ARRAYSIZE-1)) {
                    here++;
                } else {
                    if (node->next) {
                        node = node->next;
                        here = 0;
                    }
                }
                
                return (*this);
            } // preincrement
            
            self_type operator++(int) {
                self_type tmp(*this);
                
                if (here != (ARRAYSIZE-1)) {
                    here++;
                } else {
                    if (node->next) {
                        node = node->next;
                        here = 0;
                    }
                }
                
                return tmp;
            } // postincrement
            
            bool operator==( CDAL_Iter<DataL> const& rhs ) const {
                return (node->array[here] == rhs.node->array[here]);
            }
            bool operator!=( CDAL_Iter<DataL> const& rhs) const {
                return (node->array[here] != rhs.node->array[here]);
            }
            
        }; // end SDAL_Iter
        
    public:
        //--------------------------------------------------
        // type aliases
        //--------------------------------------------------
        //using size_t = std::size_t; // you may comment out this line if your compiler complains
        using value_type = L;
        using iterator = CDAL_Iter<L>;
        using const_iterator = CDAL_Iter<L const>;
        
        // iterators over a non-const List
        iterator begin() { return iterator::make_begin(*this); }
        iterator end() { return iterator::make_end(*this); }
        
        // iterators over a const List
        const_iterator begin() const { return const_iterator::make_begin(*this); }
        const_iterator end() const { return const_iterator::make_end(*this); }
    };  // end CDAL


    /******************************************
     *   constructor
     ******************************************/
    template <typename L>
    CDAL<L>::CDAL() {
        data = nullptr;
        tail = 0;
    }

    /******************************************
     *   copy constructor
     ******************************************/
    template <typename L>
    CDAL<L>::CDAL(const CDAL &obj) {
        //data = new ArrayNode<L>*;
        *data = *obj.data;
        tail = obj.tail;
    }

    /******************************************
     *   move constructor
     ******************************************/
    template <typename L>
    CDAL<L>::CDAL(CDAL&& other) {
        *data = *other.data;
        tail = other.tail;
        
        other.data = nullptr;
        other.tail = 0;
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
            curr = curr->next;
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
            size_t maxArrayBin = (tail-1) / ARRAYSIZE;      // get max array bin num
            size_t maxArrayIndex = (tail-1) - (maxArrayBin * ARRAYSIZE);    // get index in max bin
            
            // create first node if list is empty
            if (data == nullptr) {
                ArrayNode<L>* newNode = new ArrayNode<L>();
                data = newNode;
                newNode->next = nullptr;
                
                // add new first element
                newNode->array[0] = element;
                
                //tail = 0;
            } else {
                // create node to iterate through list
                ArrayNode<L>* currArrayNode = data;         // point to first array
                
                // iterate through list until positionArrayBin - 1 is reached
                if (posArrayBin != 0) {
                    for (size_t i=0; i<posArrayBin-1; i++) {
                        currArrayNode = currArrayNode->next;
                    }
                    // check if posArrayBin exists, if not create new arrayNode
                    if (currArrayNode->next == nullptr) {
                        ArrayNode<L>* newNode = new ArrayNode<L>();
                        newNode->next = nullptr;
                        currArrayNode->next = newNode;
                    }
                
                    currArrayNode = currArrayNode->next;
                }
                
                // keep track of last element in array
                L tempElement1 = currArrayNode->array[ARRAYSIZE-1];
                
                // shift array elements 1 to the right
                for (size_t i=ARRAYSIZE-2; i>posArrayIndex; --i) {
                    currArrayNode->array[i+1] = currArrayNode->array[i];
                }
                currArrayNode->array[posArrayIndex+1] = currArrayNode->array[posArrayIndex];
                
                // insert new element into array
                currArrayNode->array[posArrayIndex] = element;
                
                // check if curr array was last array and new element causes overflow (edge case)
                if (maxArrayBin == posArrayBin && maxArrayIndex == (ARRAYSIZE-1)) {
                    ArrayNode<L>* newArrayNode = new ArrayNode<L>();
                    currArrayNode->next = newArrayNode;
                    currArrayNode = currArrayNode->next;
                    currArrayNode->next = nullptr;
                    
                    // insert last element from previous array into first element of curr array
                    currArrayNode->array[0] = tempElement1;
                } else {    // iterate through the rest of the arrays, shifting elements to the right 1 index
                    // point currArrayNode to next array
                    currArrayNode = currArrayNode->next;
                    
                    // iterate through each arrayNode
                    for (size_t i=posArrayBin+1; i<=maxArrayBin; i++) {
                        // keep track of last element in array
                        L tempElement2 = currArrayNode->array[ARRAYSIZE-1];
                        
                        // shift array elements 1 to the right
                        for (size_t j=ARRAYSIZE-2; j>0; --j) {
                            currArrayNode->array[j+1] = currArrayNode->array[j];
                        }
                        currArrayNode->array[1] = currArrayNode->array[0];
                        
                        // insert last element from previous array into first element of curr array
                        currArrayNode->array[0] = tempElement1;
                        
                        // keep track of last element so it can be inserted into first index of next array
                        tempElement1 = tempElement2;
                        
                        if (i == maxArrayBin) {
                            // if max index is at end of array, allocate new array
                            if (maxArrayIndex == (ARRAYSIZE-1)) {
                                ArrayNode<L>* newArrayNode = new ArrayNode<L>();
                                currArrayNode->next = newArrayNode;
                                currArrayNode = currArrayNode->next;
                                currArrayNode->next = nullptr;
                                currArrayNode->array[0] = tempElement1;
                            }
                        } else {
                            currArrayNode = currArrayNode->next;
                        }
                    }
                }
            }
            tail += 1;
        }
    }

    /******************************************
     *   push_back
     ******************************************/
    template <typename L>
    void CDAL<L>::push_back(L element) {
        insert(element, tail);
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
                currArrayNode = currArrayNode->next;
            }
            
            // store old element in temp
            L temp = currArrayNode->array[posArrayIndex];
            
            // replace element
            currArrayNode->array[posArrayIndex] = element;
            
            //return currArrayNode->Element(posArrayIndex);
            return temp;
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
            size_t maxArrayBin = (tail-1) / ARRAYSIZE;      // get max array bin num
            size_t maxArrayIndex = (tail-1) - (maxArrayBin * ARRAYSIZE);    // get index in max bin
            
            // create curr and next array node to iterate through list
            ArrayNode<L>* currArrayNode = data;         // point to first array
            ArrayNode<L>* nextArrayNode = currArrayNode->next;    // point to second array
            
            // iterate through list until positionArrayBin - 1 is reached
            for (size_t i=0; i<posArrayBin; i++) {
                currArrayNode = currArrayNode->next;
                nextArrayNode = nextArrayNode->next;
            }
            
            L removedElement = currArrayNode->array[posArrayIndex];
            
            // shift array elements 1 to the left
            for (size_t i=posArrayIndex; i<(ARRAYSIZE-1); i++) {
                currArrayNode->array[i] = currArrayNode->array[i+1];
            }
            
            // check if next array is null
            if (nextArrayNode != nullptr) {
                // replace last element of curr array with first element in next array
                currArrayNode->array[ARRAYSIZE-1] = nextArrayNode->array[0];
            } else {
                // replace last element of curr array with NULL value
                currArrayNode->array[ARRAYSIZE-1] = 0;
                tail--;
                
                return removedElement;
            }
            
            // continue shifting elements after posArrayBin to the left 1 bit
            for (size_t i=posArrayBin+1; i<maxArrayBin; i++) {
                currArrayNode = currArrayNode->next;
                nextArrayNode = nextArrayNode->next;
                
                // shift array elements 1 to the left
                for (size_t j=0; j<(ARRAYSIZE-1); j++) {
                    currArrayNode->array[j] = currArrayNode->array[j+1];
                }
                
                // replace last element of curr array with first element in next array
                currArrayNode->array[ARRAYSIZE-1] = nextArrayNode->array[0];
            }
            
            // check if last array is now null after shifting
            if (maxArrayIndex != 0) {
                // finish shifting last array
                currArrayNode = currArrayNode->next;
                nextArrayNode = nextArrayNode->next;
                for (size_t j=0; j<maxArrayIndex; j++) {
                    currArrayNode->array[j] = currArrayNode->array[j+1];
                }
                currArrayNode->array[maxArrayIndex] = 0;
            } else {
                // delete array and arrayNode
                delete nextArrayNode;
            }
            
            tail--;
            
            return removedElement;
        }
    }

    /******************************************
     *   pop_back
     ******************************************/
    template <typename L>
    L CDAL<L>::pop_back() {
        return remove(tail-1);
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
    L& CDAL<L>::item_at(size_t position) {
        if (position > (tail-1)) {
            throw std::runtime_error("CDAL<L>.item_at(): item_at position is out of list bounds.");
        } else {
            // create position parameters
            size_t posArrayBin = position / ARRAYSIZE;      // get position array bin num
            size_t posArrayIndex = position - (posArrayBin * ARRAYSIZE);    // get index in position bin
            
            // create curr and next array node to iterate through list
            ArrayNode<L>* currArrayNode = data;         // point to first array
            
            // iterate through list until positionArrayBin - 1 is reached
            for (size_t i=0; i<posArrayBin; i++) {
                currArrayNode = currArrayNode->next;
            }
            
            return currArrayNode->array[posArrayIndex];
        }
    }

    /******************************************
     *   peek_back
     ******************************************/
    template <typename L>
    L& CDAL<L>::peek_back() {
        return item_at(tail-1);
    }

    /******************************************
     *   peek_front
     ******************************************/
    template <typename L>
    L& CDAL<L>::peek_front() {
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
        return tail;
    }

    /******************************************
     *   clear
     ******************************************/
    template <typename L>
    void CDAL<L>::clear() {
        size_t maxArrayBin = (tail-1) / ARRAYSIZE;      // get max array bin num
        
        ArrayNode<L>* currArrayNode = data;
        ArrayNode<L>* prevArrayNode = data;
        
        for (size_t i=0; i<=maxArrayBin; i++) {
            currArrayNode = currArrayNode->next;
            delete prevArrayNode;
            prevArrayNode = currArrayNode;
        }
        
        data = nullptr;
        tail = 0;
    }

    /******************************************
     *   contains
     ******************************************/
    template <typename L>
    bool CDAL<L>::contains(L element, bool (*compare)(const L&, const L&)) {
    //bool CDAL<L>::contains(L element) {
        size_t maxArrayBin = (tail-1) / ARRAYSIZE;      // get max array bin num
        size_t maxArrayIndex = (tail-1) - (maxArrayBin * ARRAYSIZE);    // get index in max bin
        
        ArrayNode<L>* currArrayNode = data;
        
        for (size_t i=0; i<maxArrayBin; i++) {
            for (size_t j=0; j<=ARRAYSIZE; j++) {
                if ((compare)(currArrayNode->array[j], element)) {
                    return true;
                }
            }
            currArrayNode = currArrayNode->next;
        }
        
        for (size_t j=0; j<=maxArrayIndex; j++) {
            if ((compare)(currArrayNode->array[j], element)) {
                return true;
            }
        }
        
        return false;
    }

    /******************************************
     *   print
     ******************************************/
    template <typename L>
    void CDAL<L>::print(std::ostream&) {
        if (data == nullptr) {
            std::cout << "<empty list>" << std::endl;
        } else {
            ArrayNode<L>* currArrayNode = data;
            
            size_t maxArrayBin = (tail-1) / ARRAYSIZE;      // get max array bin num
            size_t maxArrayIndex = (tail-1) - (maxArrayBin * ARRAYSIZE);    // get index in max bin
            
            std::cout << "[";
            for (size_t i=0; i<maxArrayBin; i++) {
                for (size_t j=0; j<ARRAYSIZE; j++) {
                    std::cout << currArrayNode->array[j] << ", ";
                }
                currArrayNode = currArrayNode->next;
            }
            
            // print out last array bin, stopping at tail
            for (size_t i=0; i<maxArrayIndex; i++) {
                std::cout << currArrayNode->array[i] << ", ";
            }
            
            std::cout << currArrayNode->array[maxArrayIndex] << "]" << std::endl;
        }
    }

    /******************************************
     *   contents
     ******************************************/
    template <typename L>
    L* CDAL<L>::contents() {
        ArrayNode<L>* currArrayNode = data;
        
        L* contentArray = new L[tail];
        
        size_t maxArrayBin = (tail-1) / ARRAYSIZE;      // get max array bin num
        size_t maxArrayIndex = (tail-1) - (maxArrayBin * ARRAYSIZE);    // get index in max bin
        
        size_t index = 0;
        
        for (size_t i=0; i<maxArrayBin; i++) {
            for (size_t j=0; j<ARRAYSIZE; j++) {
                contentArray[index++] = currArrayNode->array[j];
            }
            currArrayNode = currArrayNode->next;
        }
        
        for (size_t j=0; j<=maxArrayIndex; j++) {
            contentArray[index++] = currArrayNode->array[j];
        }
        
        return contentArray;
    }
}

#endif /* cdal_h */
