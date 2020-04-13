
// exceptional Chapter 2, P25
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <iomanip>
#include <sstream>

#include <cstdio>
#include <cstring>
#include <cassert>

TEST_CASE("sprintf caveat") {
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

TEST_CASE("string-stream") {
    std::stringstream ss;
    ss << std::setw(4) << 1000000;
    assert(std::string("1000000") == ss.str());
    ss.str("");
    ss << std::setw(4) << 1;
    assert(std::string("   1") == ss.str());

}

TEST_CASE("from int to string") {
    std::string s = std::to_string(1337);
    assert(s == std::string("1337"));
}
