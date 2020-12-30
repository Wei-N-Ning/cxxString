//
// Created by weining on 30/12/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// mentioned in c++ 20 the programmer's intro P/57
// see:
// https://en.cppreference.com/w/cpp/utility/format/format
// formatter (i.e. the standard format)
// https://en.cppreference.com/w/cpp/utility/format/formatter#Standard_format_specification
// this is based on python's format spec

// NOTE: at the time of writing, gcc (10) does not provide this functionality
// (the version token of 10 is 201707L)
//  Text formatting 	P0645R10 		__cpp_lib_format >= 201907L

TEST_CASE( "compare stringstream and cxx format function" )
{
    ;
}