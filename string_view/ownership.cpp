//
// Created by weining on 12/5/20.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <string_view>
#include <string>
#include <iostream>

// inspired by: https://www.youtube.com/watch?v=xwP4YCP_0q0
// some operator is missing in C++17 (such as the sv + sv operator)
// ensure std::string owns the data; string_view to read or peak the data

TEST_CASE( "ownership demo" )
{
    using namespace std;
    using namespace string_literals;
    using namespace string_view_literals;

    string original{ "there is a cow"s };
    // original owns the data; sv "immutably borrows" the data
    string_view sv{ original.data() };
    // for function types, use string_view instead of const string &;
    // use pass-by-value idiom; the example here shows that arg
    // points to the same underlying data as the original's
    auto f = []( string_view arg ) { cout << ( void * )arg.data() << endl; };
    // however! using string_view_literal results in the creation
    // of an invisible string

    // create a new string, owned by s - detached from the original
    string s{ sv };

    cout << ( void * )original.data() << ", " << ( void * )sv.data() << ", " << ( void * )s.data()
         << endl;
    f( original );

    // good practices:
    // these search functions should use cheaply borrowed string_view
    size_t first{ sv.find_first_of( "is"sv ) };
    size_t last{ sv.find_first_of( "cow"sv ) };

    // good practices:
    // can also create cheap string_view via substr()
    string_view subsv{ sv.substr( first, last - first ) };

    // this is NOT cheap; this authors a new string
    string subs{ s.substr( first, last - first ) };

    // modify the new string, not affecting nothing
    subs[ 0 ] = 'X';

    // modify the original string, which affects the string_view
    original[ original.find_first_of( "is" ) ] = 'X';
    cout << subsv << endl;
}
