//
// Created by wein on 14/04/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <string>
#include <boost/regex.hpp>

// source: modern C++ challenges P/52
// see also boost devops notes in README
// boost regex uses PCRE; it supports lookbehind
// whereas regex in standard library (C++11) does not
std::string capitalize(const std::string &s) {
    using namespace std;

    string result{s};
    boost::regex re{"(?<=\\b)\\w"};
    boost::sregex_iterator stop{};
    for (auto it = boost::sregex_iterator(s.begin(), s.end(), re); it != stop; ++it) {
        result[it->position()] = toupper(it->str()[0]);
    }
    return result;
}

TEST_CASE ("capitalizing sentence") {
    using namespace std;
    CHECK_EQ(string{"The C++ Challenger"}, capitalize("the c++ challenger"));
    CHECK_EQ(string{" There   Is A  1 /  Cowis. B"}, capitalize(" there   Is a  1 /  cowis. b"));
}
