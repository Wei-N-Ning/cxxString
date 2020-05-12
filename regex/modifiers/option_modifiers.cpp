//
// Created by wein on 18/08/18.
//

// source

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// inspired by: perlFoo/strings/regex/optionModifiers.pl

// how to set option modifier
// and what are all the modifiers
// http://www.cplusplus.com/reference/regex/basic_regex/flags/
// http://www.cplusplus.com/reference/regex/regex_constants/#syntax_option_type
// https://en.cppreference.com/w/cpp/regex/syntax_option_type

// how to construct regex object with modifier
// http://www.cplusplus.com/reference/regex/basic_regex/basic_regex/

// what is ECMAscript
// https://en.cppreference.com/w/cpp/regex/ecmascript

// how to access match result
// https://en.cppreference.com/w/cpp/regex/regex_match

#include <iostream>
#include <regex>
#include <string>
#include <sstream>

std::regex createRegex(const std::string &pattern, bool ignoreCase = false ) {
    using namespace std::regex_constants;
    syntax_option_type option(ECMAScript);
    if (ignoreCase) {
        option |= icase;
    }
    return std::regex(pattern, option);
}

void process(std::istream &is, const std::string &pattern, bool ignoreCase = false) {
    std::regex re{createRegex(pattern, ignoreCase)};
    std::string line;
    std::smatch m;
    while (std::getline(is, line).good()) {
        if (std::regex_match(line, m, re)) {
            std::cout << m[0] << std::endl;
        }
    }
}

TEST_CASE ("case sensitive") {
    std::stringstream ss{R"DOC(
iddqd
IDDqd
idkfa
)DOC"};
    process(ss, R"RE(i[d]+.*)RE");
}

TEST_CASE ("case insensitive") {
    std::stringstream ss{R"DOC(
iddqd--
IDDqd--
idkfa--
)DOC"};
    process(ss, R"RE(i[d]+.*)RE", true);
}