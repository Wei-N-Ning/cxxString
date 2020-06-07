//
// Created by wein on 8/9/18.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <string>
#include <sstream>
#include <cassert>
#include <boost/lexical_cast.hpp>

// boost c++ app dev P/59 introduces boost's lexical cast which is superior to both
// STL's istream >> and C's strtol()

TEST_CASE("base10 conversion") {
    assert(1337 == std::stoi("1337"));
}

TEST_CASE("base10 conversion failed") {
    // .48 is truncated; note stoi() returns the number of characters
    // successfully converted to the caller via an output parameter
    size_t numChars = 0;
    assert(13 == std::stoi("13.48", &numChars));
    assert(2 == numChars);

    // throw std::invalid_argument
    // assert(0 == std::stoi("a13.48"));
}

TEST_CASE("base16 conv") {
    assert(0x3e7 == std::stoi("0x3e7", nullptr, 16));
    assert(0x3e7 == std::stoi("0003e7", nullptr, 16));
    assert(0x3e7 == std::stoi("3e7", nullptr, 16));
}

// source: modern C++ challenges P/51
// see also from_numeric.cpp for the conversion from hexstring to vector
// NOTES:
// use ostringstream (not stringstream)
// how to utilize setf, std::hex, std::setw, std::setfill to manipulate the output stream
// I need static_cast otherwise the unsigned chars are interpreted as ascii chars,
// 0xBA != "BA"
std::string vec_to_hexstring(const std::vector<unsigned char> &xs, bool lower=true) {
    using namespace std;
    ostringstream ss;
    if (! lower) {
        ss.setf(ios_base::uppercase);
    }
    for_each(xs.cbegin(), xs.cend(),
        [&ss, lower](const auto &elem) {
            ss << hex << setw(2) << setfill('0') << static_cast<int>(elem);
    });
    auto s = ss.str();
    return s;
}

TEST_CASE ("8-bit ints to hexstring") {
    using namespace std;

    CHECK_EQ(std::string{"baadf00d"}, vec_to_hexstring({0xBA, 0xAD, 0xF0, 0x0D}));
    CHECK_EQ(std::string{"BAADF00D"}, vec_to_hexstring({0xBA, 0xAD, 0xF0, 0x0D}, false));
    CHECK_EQ(std::string{"010203040506"}, vec_to_hexstring({1, 2, 3, 4, 5, 6}));
}

TEST_CASE ("boost lexical cast") {
    using namespace boost;
    auto i1 = lexical_cast<int>("123");
    CHECK_EQ(i1, 123);
    // this throw bad lexical cast exception!
    // auto i2 = lexical_cast<int>("a123");
    // CHECK_EQ(i2, 0);
    auto d1 = lexical_cast<double>(".1213");
    CHECK_EQ(d1, 0.1213);

    // does not support hexstring out of box
    // auto x1 = lexical_cast<std::size_t>("0x13123");
}
