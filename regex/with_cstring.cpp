//
// Created by weining on 11/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <string>
#include <vector>
#include <algorithm>
#include <regex>
#include <iostream>

TEST_CASE ("search") {
    using namespace std;
    regex re{"[A-Z]{3}-[A-Z]{2} [0-9]{3,4}"};
    CHECK(regex_search("NWC-AA 1112   NWC-AA 1112     NWC-AA 1112", re));
}

TEST_CASE ("match") {
    using namespace std;
    CHECK(regex_match("NWC-AA 1112   NWC-AA 1112     NWC-AA 1112", regex{R"RE([\w\-\s]+)RE"}));
}

template<typename T>
class TT;

TEST_CASE ("regex iterator") {
    using namespace std;
    const char s[]{"there is a cow"};
    regex re{R"RE(\w+)RE"};
    cregex_iterator it{begin(s), end(s), re};
    cregex_iterator end{};
    for_each(it, end, [](const auto &m) {
        cout << m.str() << endl;
    });
}
