//
// Created by weining on 18/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"
#include <string_view>
#include <charconv>
#include <optional>
#include <cmath>
#include <vector>
#include <iostream>

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

template < typename T >
std::ostream& operator<<( std::ostream& os, const std::optional< T >& optX )
{
    if ( optX.has_value() )
    {
        os << *optX;
    }
    else
    {
        os << "None";
    }
    return os;
}

TEST_CASE( "from_chars for float and double workaround" )
{
    auto f = []( std::string_view sv ) -> std::optional< double > {
        if ( auto decimalPoint = sv.find( '.' ); decimalPoint == std::string_view::npos )
        {
            int x{ 0 };
            if ( auto [ _, ec ] = std::from_chars( sv.data(), sv.data() + sv.size(), x );
                 ec != std::errc{} )
            {
                return std::nullopt;
            }
            else
            {
                return static_cast< double >( x );
            }
        }
        else
        {
            int x{ 0 }, d{ 0 };
            if ( std::from_chars( sv.data(), sv.data() + decimalPoint, x ).ec == std::errc{} )
            {
                if (auto [p, ec] = std::from_chars( sv.data() + decimalPoint + 1, sv.data() + sv.size(), d ); ec == std::errc{}) {
                    int sign{ x > 0 ? 1 : -1 };
                    // 3.1415926a
                    //          ^ p
                    return x + sign * d / std::pow( 10, p - sv.data() - decimalPoint - 1 );
                }
            }
            return std::nullopt;
        }
    };
    using namespace std::literals;
    std::vector xs{ // simple cases
                    "1"sv,
                    "1.0"sv,
                    "31.415926"sv,
                    // exceptional
                    "1a"sv,  // converted up to 1
                    "3.1415926a"sv,  // converted up to ...926
                    "a1"sv,  // None
                    // negative
                    "-1.0"sv,
                    "-31.415926"sv };
    for ( auto x : xs )
    {
        std::cout << std::showpoint << std::setprecision(12) << f( x ) << '\n';
    }
}