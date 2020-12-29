//
// Created by weining on 29/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"
#include <string>
#include <vector>
#include <sstream>
#include <locale>
#include <algorithm>
#include <memory>
#include <iostream>

// example comes from c++ 20 the programmer's intro P/10
// note it is a deliberately complex example to test the compiler's
// capacity; but it is useful anyway.

// see:
// https://en.cppreference.com/w/cpp/locale/collate
// Class std::collate encapsulates locale-specific collation
// (comparison) and hashing of strings

// create a shallow subclass of std::basic_string;
// recall that std::string is a type alias to std::basic_string<char>
template < typename C >
struct Text : std::basic_string< C >
{
    using super = std::basic_string< C >;

    // def __init__(self):
    //     super().__init__()
    constexpr Text() noexcept : super{}
    {
    }

    // the big five
    Text( const Text& ) = default;
    Text( Text&& ) noexcept = default;
    Text& operator=( const Text& ) = default;
    Text& operator=( Text&& ) noexcept = default;

    // __bool__()
    constexpr explicit operator bool() const noexcept
    {
        return not this->empty();
    }
};

template < typename C >
auto readlines( std::basic_istream< C >& in ) -> std::vector< Text< C > >
{
    std::vector< Text< C > > xs;
    Text< C > line;
    while ( std::getline( in, line ) )
    {
        xs.emplace_back( std::move( line ) );
    }
    return xs;
}

TEST_CASE( "read lines and sort lines by locale" )
{
    std::stringstream ss{ R"(x
😄😪😽😚😅
🏋🌏🕛
there is a cow
there is a silence
)" };

    using Collate = std::collate< char >;
    std::locale loc{ "" };
    const Collate& collate{ std::use_facet< Collate >( loc ) };
    std::vector lines = readlines( ss );
    std::ranges::sort( lines );
    // std::ranges::for_each( lines, []( const auto& line ) { std::cout << line << '\n'; } );

    CHECK_EQ( lines[ 0 ], "there is a cow" );
    CHECK_EQ( lines[ 1 ], "there is a silence" );
}