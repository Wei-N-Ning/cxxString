//
// Created by weining on 6/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <sstream>

// inspired by RLE (run-length-encoding) example in c++ stl cookbook
// P/278 also explains how to interact with std::cin and >>
TEST_CASE ("completely converted") {
    int a;
    char b;
    double c;

    std::stringstream ss{"1 c 3.0"};
    ss >> a >> b >> c;
    CHECK_EQ(a, 1);
    CHECK_EQ(b, 'c');
    CHECK_EQ(c, 3.0);
}

TEST_CASE ("partially converted") {
    int a;
    char b;
    double c{0.0};

    std::stringstream ss{"1 asd 3.0"};

    // P/278, I can use the evaluated result of this expression to determine
    // whether the entire operation (3 consecutive read) is successful
    // NOTE: the evaluated result is still a mut ref to the stream P/280
    if (ss >> a >> b >> c) {
        CHECK(false);
    }
    CHECK_EQ(a, 1);
    CHECK_EQ(b, 'a'); // conversion stops here due to failure
    CHECK_EQ(c, 0.0);
}

TEST_CASE ("non trivial conversion") {
    using namespace std::string_literals;
    int a;
    std::string b;
    double c{0.0};

    std::stringstream ss{"1 tt 3.0"};
    if (ss >> a >> b >> c) {
        ;
    } else {
        CHECK(false);
    }
    CHECK_EQ(a, 1);
    CHECK_EQ(b, "tt"s);
    CHECK_EQ(c, 3.0);
}

// showing how to recover from a read-failure
TEST_CASE ("fail over") {
    // P/278 if the parsing did not succeed for any reason, the cin stream is
    // now in a fail state and will not give us other input until we clear
    // the fail state again.
    // in order to be able to parse a new input, we call cin.clear()
    // to drop all input we received until now.
    // the dropping is done with cin.ignore, where we specify that we are dropping
    // the maximum number of chars until we finally see a newline

    std::stringstream ss{R"TXT(
1 sss 3.0  <-- fail, clear and ignore (drop until \n)
1. sr 3.0  <-- fail, clear and ignore
asd        <-- samo
1 c 3.0  <-- should succeed here
)TXT"};
    int a; char b; double c;
    while (!ss.eof()) {
        if (ss >> a >> b >> c) {
            break;
        } else {
            ss.clear();
            ss.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    CHECK_EQ(a, 1);
    CHECK_EQ(b, 'c');
    CHECK_EQ(c, 3.0);
}