//
// Created by wein on 14/04/20.
//

/*
 * NOTE: variable length lookbehind is ***NOT*** supported by boost
 * see: https://www.boost.org/doc/libs/1_72_0/libs/regex/doc/html/boost_regex/syntax/perl_syntax.html#boost_regex.syntax.perl_syntax.lookbehind
 * Lookbehind
(?<=pattern) consumes zero characters, only if pattern could be matched against the characters preceding the current position (pattern must be of fixed length).
(?<!pattern) consumes zero characters, only if pattern could not be matched against the characters preceding the current position (pattern must be of fixed length).
 * */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <string>
#include <iterator>

TEST_CASE ("variable length positive lookbehind") {
    using namespace std;

    string text{R"DOC(
 -- there is a cow, NamedTuple
 | Struct with NamedTuple with a, b, c -- construct payload

 | Some $ compute (arg, opt) -- Note: use NamedTuple

)DOC"};
    // boost::regex re{"(?<!--.+)NamedTuple"};
    istringstream iss{text};
    for_each(istream_iterator<string>{iss}, istream_iterator<string>{},
        [&](const auto &line) {
            auto o = false; // boost::regex_search(line, re);
            // cout << line << "  " << o << endl;
    });
}
