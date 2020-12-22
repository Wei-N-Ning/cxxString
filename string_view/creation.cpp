//
// Created by weining on 17/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <string_view>
#include <algorithm>

// C++ 17 in depth P/133
//

// C++ 17 in depth P/152
// always remember to use string_view::size() when you build a string from
// string_view. The size() method properly marks the end of string_view

TEST_CASE( "create string view from const char *" )
{
    /**
     *
     * 4) Constructs a view of the null-terminated character string pointed to by s,
     * not including the terminating null character. The length of the view is determined
     * as if by Traits::length(s).
     *
     * The behavior is undefined if [s, s+Traits::length(s)) is not a valid range.
     *
     * After construction, data() is equal to s, and size() is equal to Traits::length(s).
     * */
    std::string_view s{ "iddqd" };
    auto n = std::count( s.begin(), s.end(), 'd' );
    CHECK_EQ( n, 3 );
}

// c++ 17 in detail P/148
//

TEST_CASE( "string view with constexpr" )
{
    using namespace std::literals;

    constexpr auto strv = "there is a cow"sv;
    constexpr auto part = strv.substr( 6, 2 );
    static_assert( part == "is"sv );

    // there is no runtime asm code generated!
}

// c++ 17 the complete guide P/178
// there are two major applications of string-view
// - you might have allocated or mapped data with character sequences or strings and
//   want to use this data without allocating more mem; typical examples are:
//    - memory mapped files
//    - strings in large texts
// - you want to improve perf for functions/operations that receive strings just
//   to directly process them read-only, not needing a trailing null terminator