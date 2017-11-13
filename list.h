//
//  list.h
//  project1
//
//  Created by Evan Waxman on 9/10/17.
//  Copyright © 2017 Evan Waxman. All rights reserved.
//

#ifndef list_h
#define list_h

#define ARRAYSIZE 50

namespace cop3530 {
    
    template <typename L>
    class List {
        
    public:
        virtual void insert(L element, size_t position) = 0;
        virtual void push_back(L element) = 0;
        virtual void push_front(L element) = 0;
        virtual L replace(L element, size_t position) = 0;
        virtual L remove(size_t position) = 0;
        virtual L pop_back(void) = 0;
        virtual L pop_front(void) = 0;
        virtual L item_at(size_t position) = 0;
        virtual L peek_back(void) = 0;
        virtual L peek_front(void) = 0;
        virtual bool is_empty(void) = 0;
        virtual bool is_full(void) = 0;
        virtual size_t length(void) = 0;
        virtual void clear(void) = 0;
        virtual bool contains(L element) = 0;
        virtual void print(void) = 0;
        virtual L* contents(void) = 0;
        virtual ~List() {};
    };
    
    template <typename L>
    class Node {
    private:
        L data;
        Node* next;
        
    public:
        Node() {};
        void setData(L new_data) { data = new_data; };
        void setNext(Node* new_next) { next = new_next; };
        L Data() { return data; };
        Node* Next() { return next; };
    };
    
    template <typename L>
    class ArrayNode {
    private:
        L array[ARRAYSIZE];
        ArrayNode* next;
        
    public:
        ArrayNode() {};
        //void setArray(L* new_array) { array = new_array; };
        void setNext(ArrayNode* new_next) { next = new_next; };
        L Element(size_t position) { return array[position]; };
        L* ElementAddr(size_t position) { return &array[position]; };
        void editElement(size_t position, L element) { array[position] = element; };
        ArrayNode* Next() { return next; };
    };
    
}
#endif /* list_h */
