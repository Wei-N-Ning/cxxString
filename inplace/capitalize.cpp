//
// Created by wein on 14/04/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <string>

// source: modern C++ challenges P/52
std::string capitalize(const std::string &s) {
    using namespace std;

    return "";
}

TEST_CASE ("capitalizing sentence") {
    using namespace std;

    CHECK_EQ(string{"The C++ Challenger"}, capitalize("the c++ challenger"));
//    CHECK_EQ(string{" There   Is A  1 /  Cowis. B"}, capitalize(" there   Is a  1 /  cowis. b"));
}
