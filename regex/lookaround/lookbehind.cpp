//
// Created by weining on 12/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <regex>
#include <string>
#include <sstream>
#include <unordered_map>

// modern c++ programming cookbook L2762

namespace {
    static std::regex re{R"RE(^(?!#)(\w+)\s*=\s*([\w\d]+[\w\d._,\-:]*)$)RE"};
}

TEST_CASE ("") {
    using namespace std;
    using namespace string_literals;

    auto doc{R"TEXT(
#remove '#' to uncomment the following lines
timeout=120
server = 127.0.0.1

# this is a comment
#retrycount = 3
)TEXT"s};

    stringstream ss(doc);
    string line;
    unordered_map<string, string> properties;
    while (getline(ss, line)) {
        if (smatch match; regex_search(line, match, ::re)) {
            // match[0] is the entire match portion
            properties[match[1]] = match[2];
        }
    }
    CHECK_EQ(2, properties.size());
    CHECK_EQ(properties["server"], "127.0.0.1"s);
}
