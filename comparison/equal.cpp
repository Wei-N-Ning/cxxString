//
// Created by weining on 8/6/20.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"
#include <boost/algorithm/string/predicate.hpp>
#include <string>

// c++ boost app dev P/201
//

TEST_CASE( "case insensitive equal (iequal)" )
{
    std::string s1{ "iddqd" }, s2{ "IDDQD" };
    CHECK( boost::iequals( s1, s2 ) );

    auto o = s1.size() == s2.size()
             && std::equal( s1.cbegin(), s1.cend(), s2.cbegin(), boost::is_iequal() );
    CHECK( o );
}
