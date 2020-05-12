//
// Created by weining on 12/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// modern c++ programming cookbook L2793
// so nice to see the standard library use pcre style placement symbols

#include <string>
#include <regex>
#include <iostream>

TEST_CASE ("3-some") {
    using namespace std;
    using namespace string_literals;

    auto doc{"abc aa bca ca bbbb"s};
    regex re{R"RE(\b[abc]{3}\b)RE"};

    // returns a new string
    auto new_doc = regex_replace(doc, re, "---"s);
    CHECK_EQ(new_doc, "--- aa --- ca bbbb");
}

TEST_CASE ("use capture group") {
    using namespace std;
    using namespace string_literals;

    auto doc{"e1m1,   doom1"s};
    regex re{R"RE((\w+),\s*(\w+))RE"};
    auto new_doc = regex_replace(doc, re, "$2 $1"s);
    CHECK_EQ(new_doc, "doom1 e1m1");
}

TEST_CASE ("use perl like $& $` $' symbols") {
    using namespace std;
    using namespace string_literals;

    auto doc{"data CapitalGain = CapitalGain CapitalType Int"s};
    //                         ^^^^^^^^^^ match this one, $&
    regex re{R"RE(CapitalGain(?=\s\=))RE"};
    auto entire_match = regex_replace(doc, re, "New$&");
    auto before_first_match = regex_replace(doc, re, "[$`]");
    auto after_last_match = regex_replace(doc, re, "<$'>");
    cout << entire_match << endl;
    cout << before_first_match << endl;
    cout << after_last_match << endl;
}

// L2820
//
TEST_CASE ("replace first only") {
    using namespace std;
    using namespace string_literals;

    auto doc{"abc aa bca ca bbbb"s};
    regex re{R"RE(\b[abc]{3}\b)RE"};

    // returns a new string
    auto new_doc = regex_replace(doc, re, "---"s, regex_constants::format_first_only);
    CHECK_EQ(new_doc, "--- aa bca ca bbbb");
}
