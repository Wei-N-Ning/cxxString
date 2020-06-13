//
// Created by weining on 13/6/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

TEST_CASE( "python style string.split('...')" )
{
    std::string sut{
        "/home/weining/work/dev/cxx/github.com/powergun/cxxString/partition/boost_split.sh" };
    std::string needle{"cxxString/"};
    if ( auto pos = sut.find(needle); pos != std::string::npos)
    {
        auto s{sut.substr(pos + needle.size(), std::string::npos)};
        CHECK_EQ( s, "partition/boost_split.sh" );
    }
}
