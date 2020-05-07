//
// Created by weining on 7/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

// c++ stl cookbook P/292
// in order to be able to read such as city from a serial input stream,
// we need to overload the stream function operator>>

struct city {
    std::string name{};
    std::size_t population{};
    double latitude{};
    double longitude{};

    friend std::ostream &operator<<(std::ostream &os, const city &c) {
        os << c.name << " " << c.population << std::setprecision(1) << std::fixed;
        os << " " << c.latitude << " " << c.longitude;
        return os;
    }
};

std::istream &operator>>(std::istream &is, city &c) {
    is >> std::ws;
    is >> c.name >> c.population >> c.latitude >> c.longitude;
    return is;
}

TEST_CASE ("parse single unit") {
    std::string s{"e1m1 10 1.0 2.0"};
    std::stringstream ss{s};
    city c;
    ss >> c;

    std::ostringstream oss{};
    oss << c;
    CHECK_EQ(s, oss.str());
}

TEST_CASE ("parse with comment") {
    std::string s{"e1m1 10 1.0 2.0"};
    std::stringstream ss{"#comment# " + s};
    city c;
    {
        std::string comment;
        ss >> std::ws >> comment;
    }
    ss >> c;
    std::ostringstream oss{};
    oss << c;
    CHECK_EQ(s, oss.str());
}

// support comment and parsing failure
TEST_CASE ("parse multiple unit") {
    std::string doc{R"DOC(
# comment
e1m1 10 1.0 2.0

e1m1 10 1.0 2.0
# comment

e1m1 10 1.0 2.0
e1m1 10 1.0
e1m1 10 1.0 2.0

)DOC"};
    std::stringstream is{doc};
    std::vector<city> v;
    for (std::string line; getline(is, line); ){
        if (line.find_first_of('#') == 0) continue;
        // this is the (accidentally implemented) failure-recovering mechanism
        // the istream is re-constructed for each new line therefore the previous
        // error state has no impact on the subsequent parsing
        // in contrary, using a istream_iterator does not benefit from this,
        // and will terminate the parsing in the case of a single failure
        if (city c; std::stringstream(line) >> c){
            v.emplace_back(std::move(c));
        }
    }
    CHECK_EQ(4, v.size());
}

// note this does not have the capability to handle comment
// it also can not recover from parsing failure
TEST_CASE ("parse multiple unit using istream_iterator<>") {
    std::string doc{R"DOC(
e1m1 10 1.0 2.0

e1m1 10 1.0 2.0

e1m1 10 1.0 2.0

e1m1 10 1.0 2.0

)DOC"};
    std::stringstream is{doc};
    std::vector<city> v;
    std::copy(std::istream_iterator<city>{is}, {}, std::back_inserter(v));
    CHECK_EQ(4, v.size());
}
