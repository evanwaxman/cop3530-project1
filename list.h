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
        virtual L& item_at(size_t position) = 0;
        virtual L& peek_back(void) = 0;
        virtual L& peek_front(void) = 0;
        virtual bool is_empty(void) = 0;
        virtual bool is_full(void) = 0;
        virtual size_t length(void) = 0;
        virtual void clear(void) = 0;
        virtual bool contains(L element, bool (*compare)(const L&, const L&)) = 0;
        //virtual bool contains(L element) = 0;
        virtual void print(std::ostream&) = 0;
        virtual L* contents(void) = 0;
        //virtual bool compare(L d1, L d2) = 0;
        
        virtual ~List() {};
    };
    
    template <typename L>
    struct Node {
        Node* next;
        L data;
    };
    
    template <typename L>
    struct ArrayNode {
        ArrayNode* next;
        L array[ARRAYSIZE];
    };
    
}
#endif /* list_h */
