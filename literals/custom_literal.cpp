//
// Created by weining on 8/5/20.
//

// modern c++ programming cookbook L/2075
// see also: cxxSysProg/date_and_time/abs_and_rela_time.cpp

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

struct Item {
    unsigned long long int a;
};

Item operator""_item(unsigned long long int n) {
    return Item{n};
}

TEST_CASE ("") {
    auto a{234_item};
    CHECK_EQ(a.a, 234);
}
