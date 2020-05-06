#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <string>
#include <cstring>
#include <string_view>
#include <iostream>
#include <sstream>
#include <algorithm>

// c++ stl cookbook P/268

TEST_CASE ("create from cstring") {
    using std::string;
    const char *cstr = "asd\000asdsad\000asdasdasdasd\000asd";
    string s(cstr);
        CHECK_EQ(strlen(cstr), s.size());
}

// the string literal is a game changer for productivity
// see: https://en.cppreference.com/w/cpp/string/basic_string/operator%22%22s
TEST_CASE ("create from brace-init and string literals") {
    using std::string;
    using namespace std::string_literals;
    string brace_init{"a"};
    auto b("a"s);
    CHECK_EQ(brace_init, b);
    CHECK(std::is_same_v<decltype(brace_init), decltype(b)>);
}

TEST_CASE ("create string-view and string-view literals") {
    using namespace std;
    using namespace std::string_literals;
    using namespace std::string_view_literals;

    string_view c{"c"};
    auto d("c"sv);
    CHECK_EQ(c, d);
    CHECK(std::is_same_v<decltype(c), decltype(d)>);
}

// c++ stl cookbook P/269
// we have to get the string out of string-view first, in order for concatenation
// use ostringstream for efficient concat however
TEST_CASE ("concatenate string using string-view") {
    using namespace std;
    using namespace std::string_view_literals;

    auto prefix("idd"sv);
    auto suffix("qd"sv);
    cout << string{prefix} + string{suffix} << endl;
}