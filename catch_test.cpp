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
#include "list.h"
#include "ssll.h"
#include "psll.h"
#include "sdal.h"
#include "cdal.h"

//#define TEST_SSLL 1
//#define TEST_PSSL 1
#define TEST_SDAL 1
//#define TEST_CDAL 1

using namespace cop3530;

/******************************************
 *   push_back
 ******************************************/
char push_back(List<char>& list, char element) {
    list.push_back(element);
    return list.peek_back();
}

/******************************************
 *   push_front
 ******************************************/
char push_front(List<char>& list, char element) {
    list.push_front(element);
    return list.peek_front();
}

/******************************************
 *   insert
 ******************************************/
char insert(List<char>& list, char element, size_t position) {
    list.insert(element, position);
    return list.item_at(position);
}

/******************************************
 *   replace
 ******************************************/
char replace(List<char>& list, char element, size_t position) {
    return list.replace(element, position);
}

/******************************************
 *   remove
 ******************************************/
char remove(List<char>& list, size_t position) {
    return list.remove(position);
    /*
    if (position == (list.length())) {
        position--;
    }
    return list.item_at(position);
    */
}

/******************************************
 *   pop_back
 ******************************************/
char pop_back(List<char>& list) {
    return list.pop_back();
}

/******************************************
 *   pop_front
 ******************************************/
char pop_front(List<char>& list) {
    return list.pop_front();
}

/******************************************
 *   item_at
 ******************************************/
char item_at(List<char>& list, size_t position) {
    return list.item_at(position);
}

/******************************************
 *   peek_back
 ******************************************/
char peek_back(List<char>& list) {
    return list.peek_back();
}

/******************************************
 *   peek_front
 ******************************************/
char peek_front(List<char>& list) {
    return list.peek_front();
}

/******************************************
 *   is_empty
 ******************************************/
char is_empty(List<char>& list) {
    return list.is_empty();
}

/******************************************
 *   is_full
 ******************************************/
char is_full(List<char>& list) {
    return list.is_full();
}

/******************************************
 *   contains
 ******************************************/
char contains(List<char>& list, char element) {
    return list.contains(element);
}


TEST_CASE( "Add components to list", "[add]" ) {
    #ifdef TEST_SSLL
        SSLL<char> list = SSLL<char>();
    #elif TEST_PSSL
        PSLL<char> list = PSLL<char>();
    #elif TEST_SDAL
        SDAL<char> list = SDAL<char>(10);
    #elif TEST_CDAL
        CDAL<char> list = CDAL<char>();
    #endif
    
    REQUIRE( push_back(list,'c') == 'c' );
    REQUIRE( push_front(list,'b') == 'b' );
    REQUIRE( push_back(list,'d') == 'd' );
    REQUIRE( push_front(list,'a') == 'a' );
    REQUIRE( insert(list,'y',2) == 'y' );
    REQUIRE( insert(list,'x',0) == 'x' );
    REQUIRE( insert(list,'z',6) == 'z' );
    
    list.clear();   // deallocate list
}

TEST_CASE( "Subtract components from the list", "[subtract]" ) {
    #ifdef TEST_SSLL
        SSLL<char> list = SSLL<char>();
    #elif TEST_PSSL
        PSLL<char> list = PSLL<char>();
    #elif TEST_SDAL
        SDAL<char> list = SDAL<char>(10);
    #elif TEST_CDAL
        CDAL<char> list = CDAL<char>();
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
    
    list.clear();   // deallocate list
}

TEST_CASE( "View components in list", "[view]" ) {
    #ifdef TEST_SSLL
        SSLL<char> list = SSLL<char>();
    #elif TEST_PSSL
        PSLL<char> list = PSLL<char>();
    #elif TEST_SDAL
        SDAL<char> list = SDAL<char>(10);
    #elif TEST_CDAL
        CDAL<char> list = CDAL<char>();
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
    
    list.clear();   // deallocate list
}

TEST_CASE( "Check capacity of list", "[capacity]" ) {
    #ifdef TEST_SSLL
        SSLL<char> list = SSLL<char>();
    #elif TEST_PSSL
        PSLL<char> list = PSLL<char>();
    #elif TEST_SDAL
        SDAL<char> list = SDAL<char>();
    #elif TEST_CDAL
        CDAL<char> list = CDAL<char>();
    #endif
    
    char value = 'a';
    for (size_t i=0; i<200; i++) {
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
    REQUIRE( remove(list,0) == 'c' );
    REQUIRE( remove(list,100) == 'b' );

    list.clear();   // deallocate list
    
    REQUIRE( is_empty(list) == 1 );
    REQUIRE( is_full(list) == 0 );
}

TEST_CASE( "Check contents of list", "[contents]" ) {
    #ifdef TEST_SSLL
        SSLL<char> list = SSLL<char>();
    #elif TEST_PSSL
        PSLL<char> list = PSLL<char>();
    #elif TEST_SDAL
        SDAL<char> list = SDAL<char>(10);
    #elif TEST_CDAL
        CDAL<char> list = CDAL<char>();
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
    
    list.clear();   // deallocate list
}
