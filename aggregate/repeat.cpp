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
// repeat()                    :       123 micro (10 runs, fastest: 107, slowest: 202)
// std::string(n, ch)          :         6 micro (10 runs, fastest: 6, slowest: 6) speedup: 18.4593
// repeat with oss             :      1164 micro (10 runs, fastest: 1100, slowest: 1192) speedup:
// 0.105656 repeat with const string ref:       318 micro (10 runs, fastest: 309, slowest: 356)
// speedup: 0.38608

// the winners are string_view (1st) and const string ref (2nd)

// using output string-stream is slower than the string_view version

std::string repeat( std::string_view pattern, size_t n )
{
    std::string o( std::size( pattern ) * n, '\0' );
    for ( ; n > 0; --n )
    {
        std::copy( std::execution::unseq,
                   std::cbegin( pattern ),
                   std::cend( pattern ),
                   std::next( std::begin( o ), std::size( pattern ) * ( n - 1 ) ) );
    }
    return o;
}

std::string repeat_oss( const std::string& pattern, size_t n )
{
    std::ostringstream oss;
    std::fill_n( std::execution::unseq, std::ostream_iterator< std::string >{ oss }, n, pattern );
    return oss.str();
}

std::string repeat_buf( const std::string& pattern, size_t n )
{
    std::string o( std::size( pattern ) * n, '\0' );
    for ( ; n > 0; --n )
    {
        std::copy( std::execution::unseq,
                   std::cbegin( pattern ),
                   std::cend( pattern ),
                   std::next( std::begin( o ), std::size( pattern ) * ( n - 1 ) ) );
    }
    return o;
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
        .measure( "repeat with oss",
                  [ sz ]() {
                      auto s = repeat_oss( "xxxx", sz );
                      assert( s.size() == 4 * sz );
                  } )
        .measure( "repeat with const string ref", [ sz ]() {
            auto s = repeat_buf( "xxxx", sz );
            assert( s.size() == 4 * sz );
        } );
}
