//
// Created by wein on 15/04/20.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <sstream>
#include <iostream>
#include <boost/tokenizer.hpp>

TEST_CASE ("") {
    using namespace std;
    string text{R"DOC(
[doctest] test cases:      1 |      1 passed |      0 failed |      0 skipped
[doctest] assertions:      0 |      0 passed |      0 failed |
[doctest] Status: SUCCESS!
)DOC"};
    istringstream inss{text};

    // how to iterate over lines
    // source: https://stackoverflow.com/questions/2291802/is-there-a-c-iterator-that-can-iterate-over-a-file-line-by-line
    using istream_tokenizer = boost::tokenizer<boost::char_separator<char>, std::istreambuf_iterator<char>>;
    using separator = boost::char_separator<char>;
    auto it = istream_tokenizer{istreambuf_iterator<char>{inss},
                                istreambuf_iterator<char>{},
                                separator{"\n", "", boost::keep_empty_tokens}};
    for_each(it.begin(), it.end(), [](const auto &line) { cout << ">>" << line << endl; });
}
