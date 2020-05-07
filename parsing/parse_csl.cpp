//
// Created by weining on 6/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

// c++ stl cookbook P/280
// taking advantage of getline(), std::ws
// see also skipws
// When the skipws format flag is set, as many whitespace characters as necessary are
// read and discarded from the stream until a non-whitespace character is found
// before. This applies to every formatted input operation performed with
// operator>> on the stream.
// http://www.cplusplus.com/reference/ios/skipws/
TEST_CASE ("istream whitespace trimming technique") {
    char a, b, c;

    std::istringstream iss ("  123");
    iss >> std::skipws >> a >> b >> c;
    std::cout << a << b << c << '\n';

    iss.seekg(0);
    iss >> std::noskipws >> a >> b >> c;
    std::cout << a << b << c << '\n';
}

TEST_CASE ("parse csl text") {
    std::stringstream ss{R"TEXT(
there,is,a,cow,there,is,a,silence
# this is a comment
e1m1,e1,m1,e2,e2m2,e3m1,m,e1
)TEXT"};
    // P/290, "ws"
    // std::ws from iomanip can be used on input streams to skip any whitespace
    // at the head of the stream
    for (std::string line; getline(ss >> std::ws, line);) {
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
