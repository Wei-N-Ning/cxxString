//
// Created by weining on 11/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <string>
#include <vector>
#include <regex>

TEST_CASE ("search") {
    using namespace std;
    regex re{"[A-Z]{3}-[A-Z]{2} [0-9]{3,4}"};
    CHECK(regex_search("NWC-AA 1112   NWC-AA 1112     NWC-AA 1112", re));
}

TEST_CASE ("match") {
    using namespace std;
}