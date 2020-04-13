//
// Created by wein on 8/10/18.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <string>
#include <cassert>

TEST_CASE("out of range") {
    std::string s_sut;
    s_sut.clear();
    s_sut += "thereis ac ow 13 37";

    // throw std::out_of_range
    // s_sut.substr(1000, 2000);

    // truncate to the last character
    std::string a = s_sut.substr(4, 1000);
    assert(a == std::string{"eis ac ow 13 37"});

    // it is not possible to go out of range on the beginning side
    // ie. sut.substr(-100, 100);  IDE warning

    std::string b(s_sut.cbegin() + 6, s_sut.cend() - 10);
    assert(b == std::string("s a"));

    // end < start
    // throws std::length_error
    // std::string(s_sut.cbegin() + 6, s_sut.cend() - 14);


    s_sut.clear();
}