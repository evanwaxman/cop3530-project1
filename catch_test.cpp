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

#define TEST_SSLL 1
#define TEST_PSSL 0
#define TEST_SDAL 0
#define TEST_CDAL 0

using namespace cop3530;

/******************************************
 *   push_back
 ******************************************/
char push_back(List<char>& list, char value) {
    list.push_back(value);
    return list.peek_back();
}

/******************************************
 *   push_front
 ******************************************/
char push_front(List<char>& list, char value) {
    list.push_front(value);
    return list.peek_front();
}

/******************************************
 *   subtract
 ******************************************/
void subtract(List<char>& list) {
    list.replace('e', 0);
    //list.print();
    
    list.replace('z', 19);
    //list.print();
    
    list.remove(0);
    //list.print();
    
    list.remove(5);
    //list.print();
    
    list.remove(10);
    //list.print();
    
    list.remove(16);
    //list.print();
    
    //std::cout << list.remove(1) << std::endl;
    //list.print();
    
    list.pop_back();
    //list.print();
    
    list.pop_front();
    //list.print();
    
    list.push_back('b');
    list.push_back('c');
    list.print();
}

/******************************************
 *   view
 ******************************************/
void view(List<char>& list) {
    std::cout << list.item_at(0) << std::endl;
    std::cout << list.item_at(3) << std::endl;
    std::cout << list.item_at(15) << std::endl;
    //std::cout << list.item_at(16) << std::endl;
    
    std::cout << list.peek_back() << std::endl;
    std::cout << list.peek_front() << std::endl;
}

/******************************************
 *   capacity
 ******************************************/
void capacity(List<char>& list) {
    list.clear();
    list.print();
    std::cout << list.is_empty() << std::endl;
    std::cout << list.is_full() << std::endl;
    
    for (size_t i=0; i<10; i++) {
        list.push_back('a'+i);
    }
    list.print();
    std::cout << list.is_empty() << std::endl;
    std::cout << list.is_full() << std::endl;
    
    //list.clear();
    list.print();
}

/******************************************
 *   contents
 ******************************************/
void contents(List<char>& list) {
    list.push_back('b');
    list.push_back('c');
    list.push_front('a');
    list.push_back('d');
    
    list.print();
    
    std::cout << list.contains('a') << std::endl;
    std::cout << list.contains('d') << std::endl;
    std::cout << list.contains('B') << std::endl;
    std::cout << list.contains('b') << std::endl;
    
    char* contents = list.contents();
    std::cout << list.contents() << std::endl;
    delete[] contents;
}

/******************************************
 *   run_tests
 ******************************************/
void run_tests() {
    //add();
    
    //subtract(list);
    
    //view(list);
    
    //capacity(list);
    
    //contents(list);
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
}

