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
// std::search() works with non-character element type (such as DNA type)
// see P/175
// to satisfy the searcher, a custom type (not character-based) needs to support std::hash interface
// and also define operator==

// c++ 17 the complete guide P/274
// boyer moore and boyer-moore-horspool searchers require RandIt instead of
// ForwardIt, unlike the naive search algorithm

TEST_CASE( "boyer moore horspool searcher" )
{
    string s{ "there is a cow" };
    string needle{ "cow" };
    const auto it = std::search(
        std::begin( s ),
        std::end( s ),
        std::boyer_moore_horspool_searcher( std::begin( needle ), std::end( needle ) ) );
    CHECK_NE( it, s.end() );
}

TEST_CASE( "boyer moore to search for all the occurrences" )
{
    // create searcher
    // for (pos = search(); pos != end; pos = search_further()) {
    //    utilise pos
    // }

    // or c++ 17 the complete guide P/275
    // for (auto [b, e] = searcher(begin, end); b != end; tie(b, e) = searcher(e, end)) {
    //    utilise b, e
    // }
}

TEST_CASE( "boyer moore or horspool" )
{
    // boyer moore: fast, go-to option
    // boyer moore horspool: trade time for space, use less mem but slower
}

struct Item
{
    int x{ 0 };

    bool operator==( const Item& other ) const
    {
        return x == other.x;
    }
};

namespace std
{
template <>
struct hash< Item >
{
    // don't forget the const qualifier!!! otherwise it will throw a confusing template assertion
    // error
    size_t operator()( const Item& item ) const
    {
        return std::hash< int >()( item.x );
    }
};
}  // namespace std

TEST_CASE( "use boyer moore searcher with custom type " )
{
    // firstly, test that std::hash<> works with the custom type
    CHECK_EQ( std::hash< int >()( 10 ), std::hash< Item >()( Item{ 10 } ) );

    // generate the haystack and the needle
    std::vector< Item > haystack( 1000 );
    std::generate_n( haystack.begin(), 1000, [ idx = 1000 ]() mutable { return Item{ --idx }; } );
    std::vector< Item > needle{ Item{ 10 }, Item{ 9 }, Item{ 8 }, Item{ 7 }, Item{ 6 } };

    auto it = std::search( haystack.cbegin(),
                           haystack.cend(),
                           std::boyer_moore_horspool_searcher( needle.cbegin(), needle.cend() ) );
    CHECK_GT( std::distance( haystack.cbegin(), it ), 100 );
}

TEST_CASE( "haystack and needle can be of different types" )
{
    // c++ 17 the complete guide P/276
    // as shown in the book, the haystack is a vector whereas the needle is a std::deque
}

struct Bean
{
    int x{ 0 };
};

TEST_CASE( "use boyer moore searcher with custom type with lambda predicates" )
{
    // c++ 17 the complete guide P/277
    // I can define the hash and equality function as lambda predicates

    // P/278
    // however, note that using a predicate might create a significant overhead
    // to using searchers;
    // only use them if you have a huge number of elements and search for a
    // subsequence of significant size (1000 needle out of 1,000,000 haystack)

    // generate the haystack and the needle
    std::vector< Bean > haystack( 1000 );
    std::generate_n( haystack.begin(), 1000, [ idx = 1000 ]() mutable { return Bean{ --idx }; } );
    std::vector< Bean > needle{ Bean{ 10 }, Bean{ 9 }, Bean{ 8 }, Bean{ 7 }, Bean{ 6 } };

    std::boyer_moore_horspool_searcher searcher{
        needle.cbegin(),
        needle.cend(),
        // the hash function
        []( const Bean& bean ) { return std::hash< int >{}( bean.x ); },
        // the Eq function
        []( const Bean& a, const Bean& b ) { return a.x == b.x; } };

    auto it = std::search( haystack.cbegin(), haystack.cend(), searcher );
    CHECK_GT( std::distance( haystack.cbegin(), it ), 100 );
}