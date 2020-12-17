//$(which true); dst=/var/tmp/sut; out=${dst}/$0.bin; mkdir -p ${dst}; c++ -std=c++14 -Wall -o
//"${out}" 1>&2 "$0" && "${out}" "$@"; exit $?
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <string>
#include <cstring>
#include <cassert>
#include <iostream>

#include <string_view>

using namespace std;

bool endswith( const string &text, const char *cstr )
{
    size_t found = text.rfind( cstr );
    if ( found == string::npos )
    {
        return false;
    }
    return text.size() - found == strlen( cstr );
}

TEST_CASE( "endswith" )
{
    // use c++17 string view and init value in the if-statement
    auto f = []( std::string_view haystack, std::string_view needle ) -> bool {
        if ( auto found = haystack.rfind( needle ); found != std::string_view::npos )
        {
            return haystack.size() - found == needle.size();
        }
        return false;
    };

    string text( "0x123 someFunc at tst/some_test.cc" );
    assert( endswith( text, ".cc" ) );
    assert( f( text, ".cc" ) );
    assert( !endswith( text, ".cpp" ) );
    assert( !f( text, ".cpp" ) );
}
