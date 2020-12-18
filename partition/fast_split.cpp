//
// Created by weining on 15/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <algorithm>
#include <string_view>
#include <vector>
#include <iostream>

// range-v3 and c++20 ranges api both offer a cleaner (but not necessarily faster) way of splitting
// string, i.e. tokenization.
// it is based on the range view and its split() algorithm;

// see cxxFP/data_structure/ranges
//

// c++ 17 in detail P/151
// NOTE: see P/171 on fast std::search() - I can use boyer_moore searcher,
// instead of std::find_first_of() to make it even faster

std::vector< std::string_view > splitSV( std::string_view strv, std::string_view delim )
{
    std::vector< std::string_view > oxs;
    auto first = strv.begin();
    auto begin = strv.begin();
    while ( first != strv.end() )
    {
        const auto second = std::search(
            first,
            std::cend( strv ),
            std::boyer_moore_horspool_searcher( std::cbegin( delim ), std::cend( delim ) ) );
        if ( first != second )
        {
            oxs.emplace_back(
                strv.substr( std::distance( begin, first ), std::distance( first, second ) ) );
        }
        if ( second == strv.end() )
        {
            break;
        }
        first = std::next( second );
    }
    return oxs;
}

TEST_CASE( "split to vector" )
{
    std::string s( 1000000, '\0' );
    std::generate( s.begin(), s.end(), [ idx = 0 ]() mutable {
        ++idx;
        if ( ( 300000 < idx && idx < 300010 ) || ( 600000 < idx && idx < 600010 ) )
        {
            return '.';
        }
        else
        {
            return 'x';
        }
    } );
    auto oxs = splitSV( s, "........." );
    CHECK_EQ( oxs.size(), 3 );

    for ( auto sv : oxs )
    {
        auto beginOffset = sv.data() - s.data();
        std::cout << '(' << beginOffset << ", " << beginOffset + sv.size() << ", " << sv.size()
                  << ")\n";
    }
}