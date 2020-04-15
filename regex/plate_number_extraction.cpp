//
// Created by wein on 15/04/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <string>
#include <vector>
#include <regex>

bool is_plate(const std::string &s) {
    using namespace std;

    regex re{"[A-Z]{3}-[A-Z]{2} [0-9]{3,4}"};
    return sregex_iterator(s.cbegin(), s.cend(), re) != sregex_iterator{};
}

std::vector<std::string> find_all_plates(const std::string &s) {
    using namespace std;

    vector<string> o;
    regex re{"[A-Z]{3}-[A-Z]{2} [0-9]{3,4}"};
    for (auto it = sregex_iterator(s.cbegin(), s.cend(), re); it != sregex_iterator{}; ++it) {
        o.emplace_back(it->str());
    }
    return o;
}

TEST_CASE ("validate plate number") {
    CHECK(! is_plate("IDDQD 111"));
    CHECK(is_plate("NWC-AA 111"));
    CHECK(is_plate("NWC-AA 1112"));

    CHECK_EQ(find_all_plates("NWC-AA 1112   NWC-AA 1112     NWC-AA 1112").size(), 3);
}
