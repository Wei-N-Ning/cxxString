//
// Created by weining on 7/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <iomanip>
#include <sstream>
#include <locale>

// c++ stl cookbook P/285

TEST_CASE ("left/right alignment (ljust/rjust in python)") {
    using namespace std;
    ostringstream oss;

    string expected{R"TEXT(
doom____________
____________doom
____________doom
)TEXT"};
    oss << endl;
    oss << setfill('_');
    oss << left << setw(16) << "doom" << endl;
    oss << right << setw(16) << "doom" << endl;

    // P/285 internal look identical to right
    oss << internal << setw(16) << "doom" << endl;
    CHECK_EQ(expected, oss.str());
}

TEST_CASE ("numeric bases and boolean") {
    using namespace std;

    ostringstream oss;
    oss << hex << showbase;

    string expected{"0x123abc 0123456 0X123ABC 123 true false"};

    oss << 0x123abc;
    oss << oct;
    oss << " " << 0123456;
    oss << " " << hex << uppercase << 0x123abc;
    oss << " " << dec << 123;

    oss << boolalpha << " " << true << " " << false;
    CHECK_EQ(expected, oss.str());
}

TEST_CASE ("floating point") {
    using namespace std;
    ostringstream oss;
    string expected{"12.3 12.0 12.3000000 12.0000000"};
    oss << showpoint << setprecision(1) << fixed << 12.3 << " " << 12.0;
    oss << showpoint << setprecision(7) << " " << fixed << 12.3 << " " << 12.0;
    CHECK_EQ(expected, oss.str());
}