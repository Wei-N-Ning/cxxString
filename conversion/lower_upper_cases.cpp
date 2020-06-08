//
// Created by weining on 8/6/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"
#include <string>
#include <boost/algorithm/string/case_conv.hpp>

TEST_CASE ("to lowercase") {
    std::string s1{"idkfa"}, s2{"idnoclip"};
    CHECK_EQ(boost::to_upper_copy(s1), "IDKFA");
    boost::to_upper(s2);
    CHECK_EQ(s2, "IDNOCLIP");
}
