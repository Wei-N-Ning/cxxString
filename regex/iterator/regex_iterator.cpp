//
// Created by wein on 19/08/18.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// source
// https://en.cppreference.com/w/cpp/regex/regex_iterator
// https://stackoverflow.com/questions/14664537/c11-regex-find-capture-group-identifier

#include <iostream>
#include <regex>
#include <string>
#include <sstream>

void process(std::istream &is, const std::string &pattern) {
    std::regex re{pattern};
    std::string line;
    std::regex_iterator<std::string::const_iterator> end;
    while (std::getline(is, line).good()) {
        // it is of type,
        // std::regex_iterator<std::string::const_iterator>
        auto it = std::sregex_iterator(line.cbegin(), line.cend(), re);
        while (it != end) {
            std::smatch m = *(it++);
            std::cout << ":" << m.str();
        }
        std::cout << std::endl;
    }
}

TEST_CASE ("search for whole worlds") {
    std::stringstream ss{R"DOC(
there is a cow
)DOC"};
    process(ss, R"RE(\w+)RE");
    process(ss, R"RE(\S+)RE");
}

TEST_CASE ("search for pattern with enclosing symbols; note `(` and `)` must be escaped") {
    std::stringstream ss{R"DOC(
/project(doom)/scene(e1)
)DOC"};
    process(ss, R"RE(\w+\(\w+\))RE");
    process(ss, R"RE(\(\w+\))RE");
}
