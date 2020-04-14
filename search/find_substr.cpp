#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <iostream>
#include <string>
#include <cassert>

using namespace std;

TEST_CASE ("find substr") {
    string text{"0x123 someFunc at tst/sometest.cc:123"};
    size_t found = text.find("at");
    assert(found != string::npos);
    cout << text.substr(found) << endl;
    cout << __FILE__ << endl;
}
