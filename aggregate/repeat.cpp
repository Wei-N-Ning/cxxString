//
// Created by weining on 30/12/20.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <string>
#include <algorithm>
#include <execution>
#include <cassert>
#include <sstream>

#include <autotimer.hh>

// inspired by haskell's repeat function
// the performance differs a lot in the debug build and in the release build,

// release build:
// compare repeat() with std::string(n, ch) constructor
//    repeat()          :       593 micro (10 runs, fastest: 521, slowest: 957)
//    std::string(n, ch):        25 micro (10 runs, fastest: 25, slowest: 26) speedup: 22.871
//    repeat with oss   :      3883 micro (10 runs, fastest: 2075, slowest: 5537) speedup: 0.152761

// using output string-stream is slower than the string_view version

std::string repeat( std::string_view pattern, size_t n )
{
    std::string o( pattern.size() * n, '\0' );
    for ( ; n > 0; --n )
    {
        std::copy( std::execution::unseq,
                   std::cbegin( pattern ),
                   std::cend( pattern ),
                   std::next( std::begin( o ), std::size( pattern ) * ( n - 1 ) ) );
    }
    return o;
}

std::string repeat_oss( const std::string &pattern, size_t n )
{
    std::ostringstream oss;
    std::fill_n( std::execution::unseq, std::ostream_iterator< std::string >{ oss }, n, pattern );
    return oss.str();
}

TEST_CASE( "repeat pattern n times" )
{
    auto s = repeat( "e1m1", 3 );
    CHECK_EQ( s.size(), 4 * 3 );
    CHECK_EQ( s, "e1m1e1m1e1m1" );

    auto largeS = repeat( "xxxx", 10000 );
    std::string expected( 4 * 10000, 'x' );
    CHECK_EQ( largeS, expected );
}

TEST_CASE( "compare repeat with string constructor" )
{
    constexpr size_t sz = 100000;
    AutoTimer::Builder()
        .withLabel( "compare repeat() with std::string(n, ch) constructor" )
        .withMultiplier( 10 )
        .measure( "repeat()",
                  [ sz ]() {
                      auto largeS = repeat( "xxxx", sz );
                      assert( largeS.size() == 4 * sz );
                  } )
        .measure( "std::string(n, ch)",
                  [ sz ]() {
                      std::string expected( 4 * sz, 'x' );
                      assert( expected.size() == 4 * sz );
                  } )
        .measure( "repeat with oss", [ sz ]() {
            auto s = repeat_oss( "xxxx", sz );
            assert( s.size() == 4 * sz );
        } );
}
