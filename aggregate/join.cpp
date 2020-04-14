//
// Created by wein on 14/04/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <vector>
#include <string>
#include <sstream>
#include <numeric>

// modern C++ challenges P/52
std::string join(const std::vector<std::string> &xs, const std::string &delim) {
    using namespace std;
    if (xs.empty()) {
        return "";
    }
    ostringstream oss;
    for_each(xs.cbegin(), xs.cend() - 1, [&oss, &delim](const auto &x) { oss << x << delim; });
    oss << xs.back();
    return oss.str();
}

TEST_CASE ("join strings with delimiter") {
    CHECK_EQ("there.is.a.cow", join({"there", "is", "a", "cow"}, "."));
    CHECK_EQ("", join({}, "."));
    CHECK_EQ("AA", join({"AA"}, ".."));
}
