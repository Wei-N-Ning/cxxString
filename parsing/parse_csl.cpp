//
// Created by weining on 6/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <string>
#include <vector>
#include <sstream>

// c++ stl cookbook P/280
// taking advantage of getline()

TEST_CASE ("parse csl text") {
    std::stringstream ss{R"TEXT(
there,is,a,cow,there,is,a,silence
# this is a comment
e1m1,e1,m1,e2,e2m2,e3m1,m,e1
)TEXT"};
    for (std::string line; getline(ss, line);) {
        if (line.find_first_of('#') == 0 || line.size() <= 1) {
            continue;
        }
        std::vector<std::string> words;
        std::stringstream line_ss{line};
        for (std::string word; getline(line_ss, word, ',');) {
            words.emplace_back(std::move(word));
        }
        CHECK_EQ(8, words.size());
    }
}
