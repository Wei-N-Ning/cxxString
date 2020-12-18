//
// Created by weining on 18/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"
#include <string_view>
#include <charconv>

// c++ 17 in detail P/155
// converting from characters to numbers
// https://en.cppreference.com/w/cpp/utility/from_chars

TEST_CASE( "from_chars integer" )
{
    using namespace std::literals;
    auto sv = "111"sv;
    int x{ 0 };
    if ( auto [ p, ec ] = std::from_chars( sv.begin(), sv.end(), x ); ec == std::errc() )
    {
        CHECK_EQ( x, 111 );
    }
    else
    {
        CHECK( false );
    }
}

TEST_CASE( "from_chars float and double" )
{
    // NOTE:
    // gcc as of version 10.1 does not support float/double version of from_chars!
    // it only supports integer

    //    using namespace std::literals;
    //    const std::string sv{"111.111"};
    //    double x{ 0 };
    //    auto format = std::chars_format::general;
    //    std::from_chars( sv.data(), sv.data() + sv.size(), x, std::chars_format::general );
}