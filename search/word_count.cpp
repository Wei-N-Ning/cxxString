//
// Created by weining on 7/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"
#include <boost/preprocessor/stringize.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>

// c++ stl cookbook P/283
// effective use of std::distance and istream_iterator
// wc is 2x faster than this version

TEST_CASE ("") {
    using namespace std;
    string text_file{BOOST_PP_STRINGIZE(TEXT_FILE)};
    ifstream ifs{text_file};
    auto c = distance(istream_iterator<string>{ifs}, {});
    // for reference,
    // wc resources/text
    // 121 1657 9880 resources/text
    //     ^^^^
    cout << c << endl;
}
