//
// Created by wein on 19/08/18.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// source
// https://stackoverflow.com/questions/29321249/regex-grouping-matches-with-c-11-regex-library

// important:
// https://en.cppreference.com/w/cpp/regex/regex_search
// regex_search will successfully match any subsequence of the given
// sequence;
// whereas std::regex_match will only return true if the regular
// expression matches the entire sequence.

#include <iostream>
#include <regex>
#include <sstream>
#include <string>

void process(std::istream &is, const std::string &pattern) {
    std::regex re{pattern};
    std::string line;
    std::smatch m;
    // to extract <name>(<value>) pairs in the text
    // note regex_search yields the first matching sub sequence  therefore I
    // need to repeatedly process match.suffix().str() to process the rest
    // of the text
    while (std::getline(is, line).good()) {
        size_t numMatchesPerLine = 0;
        while (std::regex_search(line, m, re)) {
            size_t numMatches = m.size();
            numMatchesPerLine++;
            for (size_t i = 1; i < numMatches; ++i) {
                std::cout << ":" <<  m[i].str();
            }
            line = m.suffix().str();
        }
        if (numMatchesPerLine > 0) {
            std::cout << " " << "matches: " << numMatchesPerLine \
                      << std::endl;
        }
    }
}

TEST_CASE ("") {
    std::string pattern{R"RE((\w+)\((\w+)\))RE"};
    std::string text{R"DOC(
# comment:
[/]project(doom)
[/]scene(e1)
[/]shot(m1)

# comment:
[/]element(archvile)
[/]product(motion)

[/]version(101)
[/]resource(apm)

)DOC"};
    std::stringstream ss(text);
    process(ss, pattern);
}
