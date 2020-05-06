//
// Created by weining on 6/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <string>
#include <string_view>
#include <algorithm>
#include <sstream>

// c++ stl cookbook P/271

// this is my hack
TEST_CASE ("find-copy") {
    using namespace std;
    using namespace std::string_literals;
    string speech{"   there is a coww  "};
    auto pred = [](const auto &ch) { return ! isspace(ch); };
    auto begin = std::find_if(speech.cbegin(), speech.cend(), pred);
    auto end = std::find_if(speech.crbegin(), speech.crend(), pred).base();
    auto sz = distance(begin, end);
    std::copy(begin, end, speech.begin());
    speech.resize(sz);
    CHECK_EQ("there is a coww"s, speech);
}

// this is the book's recipe
// std::string offers find_first/last_not_of(char-array) methods and substr()
// method.
TEST_CASE ("find first, copy") {
    using namespace std;
    using namespace std::string_literals;
    string speech{"   there is a coww  "};
    const char whitespace[] = {" \t\n"};
    const size_t first(speech.find_first_not_of(whitespace));
    const size_t last(speech.find_last_not_of(whitespace));
    string s(speech.substr(first, (last - first + 1)));
    CHECK_EQ("there is a coww"s, s);
}

// P/275
// cpp reference on string view:
// https://en.cppreference.com/w/cpp/string/basic_string_view
TEST_CASE ("use string view to hide the whitespace") {
    using namespace std;
    using namespace std::string_literals;
    using namespace std::string_view_literals;
    auto v("   there is a coww  "sv);
    const auto begin(v.find_first_not_of(" \t\n"));
    v.remove_prefix(min(begin, v.size()));
    const auto end(v.find_last_not_of(" \t\n"));
    v.remove_suffix(v.size() - end - 1);
    ostringstream oss;
    oss << v;
    CHECK_EQ("there is a coww"s, oss.str());
}
