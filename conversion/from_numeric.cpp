
// exceptional Chapter 2, P25
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <iomanip>
#include <algorithm>
#include <string>
#include <iterator>

#include <cstdio>
#include <cstring>
#include <cassert>
#include <boost/lexical_cast.hpp>

// source: boost c++ app dev P/62
// I can also use boost::lexical_cast<string> to save the boilerplate code
// HOWEVER, clang-tidy suggests std::to_string()!

TEST_CASE ("sprintf caveat") {
    char smallBuf[5] = {0, 0, 0, 0, 0};

    // given a char array of length 5
    // conversion is successful only for:
    // 1, 10, 100, 1000,
    // ///////// remember a legit C-string needs to be null-
    // terminating /////////
    int value = 1000;
    assert(4 == std::sprintf(smallBuf, "%d", value));
    assert(0 == std::strcmp("1000", smallBuf));

    // P25
    // (increase the number of digits) we will start scribbling past
    // the end of smallBuf, which might be into the bytes of value
    // itself if the compiler choose a memory layout that put value
    // immediate;y after smallBuf in memory
}

TEST_CASE ("string-stream") {
    std::stringstream ss;
    ss << std::setw(4) << 1000000;
    assert(std::string("1000000") == ss.str());
    ss.str("");
    ss << std::setw(4) << 1;
    assert(std::string("   1") == ss.str());

}

TEST_CASE ("from int to string") {
    std::string s = std::to_string(1337);
    assert(s == std::string("1337"));
}

// source: modern c++ challenge P/51
// see also tointeger.cpp for the conversion from vector to hexstring
// NOTES:
// use std::transform() (FP-map) to produce the intermediate unsigned chars
// reverse and pad 0 to make the total length of the intermediate vector
// a even number - simplify the last iteration
// the last iteration uses reverse iter - see comments
std::vector<unsigned char> hexstring_to_vec(const std::string &s) {
    using namespace std;

    vector<unsigned char> temp(s.size());
    transform(s.cbegin(), s.cend(), temp.rbegin(),
              [](const auto &ch) -> unsigned char {
                  if (ch >= '0' && ch <= '9') return ch - '0';
                  if (ch >= 'A' && ch <= 'F') return ch - 'A' + 10;  // 8,9,a,b...
                  if (ch >= 'a' && ch <= 'f') return ch - 'a' + 10;
                  throw invalid_argument("Invalid hexstring");
              });
    if (s.size() % 2 == 1) {
        temp.push_back(0);
    }
    vector<unsigned char> result(temp.size() / 2);
    auto src_it = temp.rbegin();
    for (auto &elem : result) {
        elem = 16 * *src_it + *(++src_it);  // end here -> 0xd, 0xa, 0xb, 0x0 <-- start here
        ++src_it;
    }
    return result;
};

TEST_CASE ("hexstring to 8-bit ints") {
    using namespace std;
    CHECK_EQ(vector<unsigned char>{0x0B, 0xAD}, hexstring_to_vec("BAD"));
    CHECK_EQ(vector<unsigned char>{0xBA, 0xAD}, hexstring_to_vec("BAAD"));
    CHECK_EQ(vector<unsigned char>{0x0B, 0xAD, 0xF0, 0x0D}, hexstring_to_vec("BADF00D"));
    CHECK_EQ(vector<unsigned char>{1, 2, 3, 4, 5, 6}, hexstring_to_vec("010203040506"));
}

TEST_CASE ("boost::lexical_cast<string>") {
    using namespace boost;
    using namespace std::string_literals;
    // prefer std::to_string() to boost::lexical_cast<>
    auto s = lexical_cast<std::string>(0x12321);
    CHECK_EQ("74529"s, s);
    auto s2 = std::to_string(0x12321);
    auto s3 = std::to_string(12321);
    CHECK_EQ("74529"s, s2);
    CHECK_EQ("12321"s, s3);
}
