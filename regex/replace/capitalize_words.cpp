//
// Created by weining on 12/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <regex>
#include <string>
#include <iostream>
#include <boost/regex.hpp>

template<typename T>
class TT;

TEST_CASE ("use word boundary symbol") {
    using namespace std;
    using namespace string_literals;

    auto doc{"there is a cow"s};
    regex re{R"RE(\b\w)RE"};
    sregex_iterator it{begin(doc), end(doc), re};
    sregex_iterator end{};
    for_each(it, end, [&doc](auto &m) {
        auto &ch = doc[m.position()];
        ch = toupper(ch);
    });
    cout << doc << endl;

}

// standard library's regex is not PCRE compliant hence not supporting the lookbehind mechanism
// use boost::regex in this case
TEST_CASE ("use fixed-size lookbehind group") {
    using namespace std;
    using namespace string_literals;

    auto doc{"there is a cow. here is a silence"s};
    boost::regex re{R"RE((?<=\.\s)(\w)|(^\w))RE"};
    boost::sregex_iterator it{begin(doc), end(doc), re};
    boost::sregex_iterator end{};
    for_each(it, end, [&doc](auto &m) {
        auto &ch = doc[m.position()];
        ch = toupper(ch);
    });
    cout << doc << endl;

}