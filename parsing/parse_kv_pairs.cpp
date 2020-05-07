//
// Created by weining on 7/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <string>
#include <sstream>
#include <utility>
#include <unordered_map>
#include <iterator>
#include <algorithm>
#include <numeric>

// c++ stl cookbook P/295

struct meme {
    std::string description{};
    std::size_t year{};
};

std::istream &operator>>(std::istream &is, meme &m) {
    // std::quoted
    // see: https://en.cppreference.com/w/cpp/io/manip/quoted
    // the quotation marks are automatically used as delimiters and dropped
    // afterward

    // MY NOTE:
    // it's both good and strange to see C++ STL goes this far to implement
    // the infrastructure for parser developers, without using applicative
    // parsing
    return is >> std::quoted(m.description) >> m.year;
}

std::istream &operator>>(std::istream &is, std::pair<std::string, meme> &p) {
    return is >> std::quoted(p.first) >> p.second;
}

TEST_CASE ("parse to structs") {
    std::string s{R"DOC(
"there is a cow" 2007
"there is a silence" 2016
)DOC"};
    std::stringstream ss{s};
    std::unordered_map<std::string, meme> db{};
    for (std::string line; std::getline(ss, line); ) {
        if (meme m; std::stringstream(line) >> m) {
            db[m.description] = m;
        }
    }
    CHECK_EQ(db["there is a cow"].year, 2007);
    CHECK_EQ(db["there is a silence"].year, 2016);
}

TEST_CASE ("parse to map") {
    // P/296
    // MY NOTE:
    // without applicative parsing, it's hard to parse
    // cow: ["there is a cow", 2007] (a json-like raw string)
    // it is hard to model "take a char, and it must be '[' character, otherwise
    // put it back"
    std::string s{R"DOC(
cow "there is a cow" 2007
silence "there is a silence" 2016
red "once up a time, there is a little girl named..." 2018
)DOC"};
    std::stringstream ss{s};
    std::unordered_map<std::string, meme> db{};
    using IsIter = std::istream_iterator<std::pair<std::string, meme>>;
    std::copy(IsIter{ss}, {}, std::inserter(db, std::end(db)));
    CHECK_EQ(db["cow"].year, 2007);
    CHECK_EQ(db["silence"].year, 2016);

    // find the longest meme
    using namespace std;
    auto len = accumulate(db.cbegin(), db.cend(), 0, [](auto len, const auto &p) {
        const auto &[_, m] = p;
        return m.description.size() > len ? m.description.size() : len;
    });
    CHECK_EQ(len, db["red"].description.size());
}
