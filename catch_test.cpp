//
//  catch_test.cpp
//  project1
//
//  Created by Evan Waxman on 11/8/17.
//  Copyright © 2017 Evan Waxman. All rights reserved.
//

#include <stdio.h>
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include <iostream>
#include "List.h"
#include "SSLL.h"
#include "PSLL.h"
#include "SDAL.h"
#include "CDAL.h"
#include "CBL.h"

//#define TEST_SSLL 1
//#define TEST_PSSL 1
//#define TEST_SDAL 1
//#define TEST_CDAL 1
#define TEST_CBL 1

//using namespace cop3530;

/******************************************
 *   push_back
 ******************************************/
char push_back(cop3530::List<char>* list, char element) {
    list->push_back(element);
    return list->peek_back();
}

/******************************************
 *   push_front
 ******************************************/
char push_front(cop3530::List<char>* list, char element) {
    list->push_front(element);
    return list->peek_front();
}

/******************************************
 *   insert
 ******************************************/
char insert(cop3530::List<char>* list, char element, size_t position) {
    list->insert(element, position);
    return list->item_at(position);
}

/******************************************
 *   replace
 ******************************************/
char replace(cop3530::List<char>* list, char element, size_t position) {
    return list->replace(element, position);
}

/******************************************
 *   remove
 ******************************************/
char remove(cop3530::List<char>* list, size_t position) {
    return list->remove(position);
}

/******************************************
 *   pop_back
 ******************************************/
char pop_back(cop3530::List<char>* list) {
    return list->pop_back();
}

/******************************************
 *   pop_front
 ******************************************/
char pop_front(cop3530::List<char>* list) {
    return list->pop_front();
}

/******************************************
 *   item_at
 ******************************************/
char item_at(cop3530::List<char>* list, size_t position) {
    return list->item_at(position);
}

/******************************************
 *   peek_back
 ******************************************/
char peek_back(cop3530::List<char>* list) {
    return list->peek_back();
}

/******************************************
 *   peek_front
 ******************************************/
char peek_front(cop3530::List<char>* list) {
    return list->peek_front();
}

/******************************************
 *   is_empty
 ******************************************/
char is_empty(cop3530::List<char>* list) {
    return list->is_empty();
}

/******************************************
 *   is_full
 ******************************************/
char is_full(cop3530::List<char>* list) {
    return list->is_full();
}

/******************************************
 *   length
 ******************************************/
char length(cop3530::List<char>* list) {
    return list->length();
}

/******************************************
 *   compare
 ******************************************/
template <typename L>
bool compare(const L& d1, const L& d2) {
    if (d1 == d2) {
        return true;
    }
    return false;
}

/******************************************
 *   contains
 ******************************************/
char contains(cop3530::List<char>* list, char element) {
    return list->contains(element,*compare<char>);
}

/******************************************
 *   SSLL_iter
 ******************************************/
bool SSLL_iter() {
    cop3530::SSLL<char> * list = new cop3530::SSLL<char>();

    // fill list with values
    char value = 'a';
    for (size_t i=0; i<25; i++) {
        push_back(list,value++);
    }
    
    cop3530::SSLL<char>::iterator iter = list->begin();
    cop3530::SSLL<char>::iterator end = list->end();
    
    size_t i = 0;
    for ( ; iter != end ; ++iter ) {
        if (*iter != item_at(list,i)) {
            return false;
        } else {
            i++;
        }
    }
    
    i = 0;
    iter = list->begin();
    for ( ; iter != end ; ++iter ) {
        if (iter->data != item_at(list,i)) {
            return false;
        } else {
            i++;
        }
    }
    
    delete list;
    
    return true;
}

/******************************************
 *   PSLL_iter
 ******************************************/
bool PSLL_iter() {
    cop3530::PSLL<char> * list = new cop3530::PSLL<char>();
    
    // fill list with values
    char value = 'a';
    for (size_t i=0; i<25; i++) {
        push_back(list,value++);
    }
    
    cop3530::PSLL<char>::iterator iter = list->begin();
    cop3530::PSLL<char>::iterator end = list->end();
    
    size_t i = 0;
    for ( ; iter != end ; ++iter ) {
        if (*iter != item_at(list,i)) {
            return false;
        } else {
            i++;
        }
    }
    
    i = 0;
    iter = list->begin();
    for ( ; iter != end ; ++iter ) {
        if (iter->data != item_at(list,i)) {
            return false;
        } else {
            i++;
        }
    }
    
    delete list;
    
    return true;
}

/******************************************
 *   SDAL_iter
 ******************************************/
bool SDAL_iter() {
    cop3530::SDAL<char> * list = new cop3530::SDAL<char>();
    
    // fill list with values
    char value = 'a';
    for (size_t i=0; i<25; i++) {
        push_back(list,value++);
    }
    
    cop3530::SDAL<char>::iterator iter = list->begin();
    cop3530::SDAL<char>::iterator end = list->end();
    
    size_t i = 0;
    for ( ; iter != end ; ++iter ) {
        if (*iter != item_at(list,i)) {
            return false;
        } else {
            i++;
        }
    }

    delete list;
    
    return true;
}

/******************************************
 *   CDAL_iter
 ******************************************/
bool CDAL_iter() {
    cop3530::CDAL<char> * list = new cop3530::CDAL<char>();
    
    // fill list with values
    char value = 'a';
    for (size_t i=0; i<100; i++) {
        push_back(list,value++);
    }
    
    cop3530::CDAL<char>::iterator iter = list->begin();
    cop3530::CDAL<char>::iterator end = list->end();
    
    size_t i = 0;
    for ( ; iter != end ; ++iter ) {
        if (*iter != item_at(list,i)) {
            return false;
        } else {
            i++;
        }
    }
    
     i = 0;
     iter = list->begin();
     for ( ; iter != end ; ++iter ) {
         if (iter->array[i] != item_at(list,i)) {
             return false;
         } else {
             i++;
         }
     }
    
    delete list;
    
    return true;
}

/******************************************
 *   CBL_iter
 ******************************************/
bool CBL_iter() {
    cop3530::CBL<char> * list = new cop3530::CBL<char>();
    
    // fill list with values
    char value = 'a';
    for (size_t i=0; i<100; i++) {
        push_back(list,value++);
    }
    
    cop3530::CBL<char>::iterator iter = list->begin();
    cop3530::CBL<char>::iterator end = list->end();
    
    size_t i = 0;
    for ( ; iter != end ; ++iter ) {
        if (*iter != item_at(list,i)) {
            return false;
        } else {
            i++;
        }
    }
    
    delete list;
    
    return true;
}


TEST_CASE( "Add components to list", "[add]" ) {
    #ifdef TEST_SSLL
        cop3530::List<char> * list  = new cop3530::SSLL<char>();
    #elif TEST_PSSL
        cop3530::List<char> * list = new cop3530::PSLL<char>();
    #elif TEST_SDAL
        cop3530::List<char> * list = new cop3530::SDAL<char>(10);
    #elif TEST_CDAL
        cop3530::List<char> * list = new cop3530::CDAL<char>();
    #elif TEST_CBL
        cop3530::List<char> * list = new cop3530::CBL<char>(10);
    #endif
    
    REQUIRE( push_back(list,'c') == 'c' );
    REQUIRE( push_front(list,'b') == 'b' );
    REQUIRE( push_back(list,'d') == 'd' );
    REQUIRE( push_front(list,'a') == 'a' );
    REQUIRE( insert(list,'y',2) == 'y' );
    REQUIRE( insert(list,'x',0) == 'x' );
    REQUIRE( insert(list,'z',6) == 'z' );
    
    list->clear();   // deallocate list
    
    delete list;
}

TEST_CASE( "Subtract components from the list", "[subtract]" ) {
    #ifdef TEST_SSLL
        cop3530::List<char> * list  = new cop3530::SSLL<char>();
    #elif TEST_PSSL
        cop3530::List<char> * list = new cop3530::PSLL<char>();
    #elif TEST_SDAL
        cop3530::List<char> * list = new cop3530::SDAL<char>(10);
    #elif TEST_CDAL
        cop3530::List<char> * list = new cop3530::CDAL<char>();
    #elif TEST_CBL
        cop3530::List<char> * list = new cop3530::CBL<char>(10);
    #endif
    
    char value = 'a';
    for (size_t i=0; i<10; i++) {
        push_back(list,value);
        value++;
    }
    
    REQUIRE( replace(list,'x',0) == 'a' );
    REQUIRE( replace(list,'z',9) == 'j' );
    REQUIRE( replace(list,'y',4) == 'e' );
    REQUIRE( remove(list,0) == 'x' );
    REQUIRE( remove(list,8) == 'z' );
    REQUIRE( remove(list,3) == 'y' );
    REQUIRE( pop_front(list) == 'b' );
    REQUIRE( pop_back(list) == 'i' );
    
    list->clear();   // deallocate list
    
    delete list;
}

TEST_CASE( "View components in list", "[view]" ) {
    #ifdef TEST_SSLL
        cop3530::List<char> * list  = new cop3530::SSLL<char>();
    #elif TEST_PSSL
        cop3530::List<char> * list = new cop3530::PSLL<char>();
    #elif TEST_SDAL
        cop3530::List<char> * list = new cop3530::SDAL<char>(10);
    #elif TEST_CDAL
        cop3530::List<char> * list = new cop3530::CDAL<char>();
    #elif TEST_CBL
        cop3530::List<char> * list = new cop3530::CBL<char>(10);
    #endif
    
    char value = 'a';
    for (size_t i=0; i<10; i++) {
        push_back(list,value);
        value++;
    }
    
    REQUIRE( item_at(list,0) == 'a' );
    REQUIRE( item_at(list,9) == 'j' );
    REQUIRE( item_at(list,4) == 'e' );
    REQUIRE( peek_back(list) == 'j' );
    REQUIRE( peek_front(list) == 'a' );
    
    list->clear();   // deallocate list
    
    delete list;
}

TEST_CASE( "Check capacity of list", "[capacity]" ) {
    #ifdef TEST_SSLL
        cop3530::List<char> * list  = new cop3530::SSLL<char>();
    #elif TEST_PSSL
        cop3530::List<char> * list = new cop3530::PSLL<char>();
    #elif TEST_SDAL
        cop3530::List<char> * list = new cop3530::SDAL<char>(10);
    #elif TEST_CDAL
        cop3530::List<char> * list = new cop3530::CDAL<char>();
    #elif TEST_CBL
        cop3530::List<char> * list = new cop3530::CBL<char>(10);
    #endif
    
    char value = 'a';
    for (size_t i=0; i<100; i++) {
        push_front(list,value);
    }
    for (size_t i=0; i<100; i++) {
        push_back(list,value);
    }
    
    REQUIRE( is_empty(list) == 0 );
    REQUIRE( is_full(list) == 0 );

    REQUIRE( peek_front(list) == 'a' );
    REQUIRE( peek_back(list) == 'a' );
    REQUIRE( item_at(list,49) == 'a' );
    REQUIRE( item_at(list,50) == 'a' );
    REQUIRE( insert(list,'b',100) == 'b' );
    REQUIRE( insert(list,'c',0) == 'c' );
    REQUIRE( insert(list,'d',199) == 'd' );
    REQUIRE( remove(list,199) == 'd' );
    REQUIRE( remove(list,0) == 'c' );
    REQUIRE( remove(list,100) == 'b' );

    list->clear();   // deallocate list
    
    REQUIRE( is_empty(list) == 1 );
    REQUIRE( is_full(list) == 0 );
    REQUIRE( length(list) == 0 );
    
    delete list;
}

TEST_CASE( "Check contents of list", "[contents]" ) {
    #ifdef TEST_SSLL
        cop3530::List<char> * list  = new cop3530::SSLL<char>();
    #elif TEST_PSSL
        cop3530::List<char> * list = new cop3530::PSLL<char>();
    #elif TEST_SDAL
        cop3530::List<char> * list = new cop3530::SDAL<char>(10);
    #elif TEST_CDAL
        cop3530::List<char> * list = new cop3530::CDAL<char>();
    #elif TEST_CBL
        cop3530::List<char> * list = new cop3530::CBL<char>(10);
    #endif
    
    char value = 'a';
    for (size_t i=0; i<5; i++) {
        push_back(list,value);
        value++;
    }
    
    value = 'a';
    for (size_t i=0; i<5; i++) {
        REQUIRE( contains(list,value) == 1 );
        value++;
    }
    
    list->clear();   // deallocate list
    
    delete list;
}

TEST_CASE( "Test iterator functionality", "[iterators]" ) {
    #ifdef TEST_SSLL
        REQUIRE( SSLL_iter() == 1 );
    
    #elif TEST_PSSL
        REQUIRE( PSLL_iter() == 1 );
    
    #elif TEST_SDAL
        REQUIRE( SDAL_iter() == 1 );
    
    #elif TEST_CDAL
        REQUIRE( CDAL_iter() == 1 );
    
    #elif TEST_CBL
        REQUIRE( CBL_iter() == 1 );
    #endif

    
    
}
