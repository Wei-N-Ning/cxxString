#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <iostream>
#include <string>
#include <cassert>
#include <algorithm>

using namespace std;

TEST_CASE( "find substr" )
{
    string text{ "0x123 someFunc at tst/sometest.cc:123" };
    size_t found = text.find( "at" );
    assert( found != string::npos );
    cout << text.substr( found ) << endl;
    cout << __FILE__ << endl;
}

// c++ 17 in detail P/170
// c++17 adds more search algorithms

TEST_CASE( "boyer moore searcher" )
{
    string s{ "there is a cow" };
    string needle{ "cow" };
    const auto it = std::search(
        std::begin( s ),
        std::end( s ),
        std::boyer_moore_horspool_searcher( std::begin( needle ), std::end( needle ) ) );
    CHECK_NE( it, s.end() );
}