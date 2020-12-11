//
// Created by wein on 14/04/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <vector>
#include <string>
#include <sstream>
#include <numeric>
#include "../vendor/auto_timer.h"

// modern C++ challenges P/52
std::string join( const std::vector< std::string > &xs, const std::string &delim )
{
    using namespace std;
    if ( xs.empty() )
    {
        return "";
    }
    ostringstream oss;
    for_each(
        xs.cbegin(), xs.cend() - 1, [ &oss, &delim ]( const auto &x ) { oss << x << delim; } );
    oss << xs.back();
    return oss.str();
}

TEST_CASE( "join strings with delimiter" )
{
    CHECK_EQ( "there.is.a.cow", join( { "there", "is", "a", "cow" }, "." ) );
    CHECK_EQ( "", join( {}, "." ) );
    CHECK_EQ( "AA", join( { "AA" }, ".." ) );
}

// FP in C++ P/137
// the chapter on laziness explains why str + str + str ... is inefficient:
// this process is inefficient. You are generating (and destroying) buffers
// you don't need. When you have a few strings to concatenate, it would be
// much more efficient to delay calculating the result until you know all
// the strings you need to concatenate. Then you can create a buffer that's
// large enough to store the final result and copy the data from the source
// strings just once.
// (str is std::string)

// this is where expression templates come in: they allow you to generate
// expression definitions instead of calculating the value of an expression.
// Rather than implement operator+() to return a concat string, you can make
// it return a definition of the expression it represents so that you can
// evaluate it later.

std::string operator|( const std::string &l, const std::string &r )
{
    std::string s( l.size() + r.size(), '\0' );
    std::copy( l.cbegin(), l.cend(), s.begin() );
    std::copy( r.cbegin(), r.cend(), s.begin() + l.size() );
    return s;
}

TEST_CASE( "overloaded concat operator" )
{
    std::string s( 6, 'a' );
    std::string t( 8, 'b' );
    auto st = s | t;
    CHECK_EQ( st, "aaaaaabbbbbbbb" );
}

TEST_CASE( "perf comparison between operator+ and overloaded concat operator" )
{
    std::string a( 1000, 'a' );
    {
        AutoTimer atm( "operator + (l, r)" );
        for ( auto &_ : std::vector< int >( 1000, 0 ) )
        {
            auto b = a + a;
        }
    }
    {
        AutoTimer atm( "operator += (self, other)" );
        std::string b;
        for ( auto &_ : std::vector< int >( 1000, 0 ) )
        {
            b += a;
        }
    }
    {
        AutoTimer atm( "operator | (l, r)" );
        for ( auto &_ : std::vector< int >( 1000, 0 ) )
        {
            auto b = a | a;
        }
    }
}