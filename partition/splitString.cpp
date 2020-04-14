//
// Created by wein on 6/8/18.
//

// Summary:
// this is a basic performance comparison between boost::split and c
// strstr();
// the later wins
// since boost split is not ported to C++ standard library, I may need
// to use getline:
// https://stackoverflow.com/questions/5167625/splitting-a-c-stdstring-using-tokens-e-g
// UPDATE:
// see find_split.cpp for a pure standard-library implementation using 
// iterators
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>

#include <cassert>
#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <memory>

void populateString(const std::string &element, const std::string &delimiter, size_t count, std::string &o_str) {
    while (count--) {
        o_str += delimiter + element;
    }
}

void populateCString(const char *element, const char *delimiter, size_t count, char *o_cstr) {
    auto le = std::strlen(element);
    auto ld = std::strlen(delimiter);
    std::memset(o_cstr, '\0', (le + ld) * count + ld);
    for (size_t i = 0; i < count; ++i) {
        std::memcpy(o_cstr + (le + ld) * i, element, le);
        std::memcpy(o_cstr + (le + ld) * i + le, delimiter, ld);
    }
}


TEST_CASE ("boost split") {
    using StrVec = std::vector<std::string>;
    auto text = std::make_shared<std::string>();
    auto values = std::make_shared<StrVec>();
    text->reserve(50000);
    values->reserve(50000);

    populateString("thereisacow", ":", 10000, *text);
    std::string &textRef = *text;
    StrVec &valuesRef = *values;

    auto start = clock();
    boost::split(valuesRef, textRef, boost::is_any_of(":"));
    auto us = clock() - start;
    printf("boost::split %f us (%f s)\n", (float) us, (float) (us / 1e6));

    assert(10001 == values->size());
}

TEST_CASE ("strstr()") {
    auto cstr = (char *) malloc(150000);
    int count = 0;
    populateCString("thereisacow", ":", 10000, cstr);

    auto startTime = clock();
    const char *start = cstr;
    const char *end = nullptr;
    const char *delimiter = ":";
    size_t sz = std::strlen(cstr);
    while (start && *start != '\0') {
        end = std::strstr(start, delimiter);
        if (end) {
            sz = end - start;
        }
        if (sz) {
            count++;
        }
        start = end + 1;
    }
    auto us = clock() - startTime;
    printf("strstr %f us (%f s)\n", (float) us, (float) (us / 1e6));
    free(cstr);

    assert(10000 == count);  // this method excludes 0-length element (such as ::)
}

// modern C++ challenges P/52
std::vector<std::string> split(const std::string &haystack, const std::string &needles) {
    using namespace std;

    vector<string> out;
    auto it = haystack.cbegin();
    auto end = haystack.cend();
    while (it != end) {
        auto found = find_if(it, end, [&needles](const auto &ch) {
            return any_of(needles.cbegin(), needles.cend(), [&ch](const auto &nd) { return nd == ch; });
        }); // use string::find_first_of, http://www.cplusplus.com/reference/string/string/find_first_of/
        if (it != found) {
            string s;
            s.reserve(haystack.size());
            copy(it, found, back_inserter(s));
            out.push_back(s);
        }
        it = found + 1;
    }
    return out;
}

TEST_CASE ("split with multiple delimiters") {
    using namespace std;

    vector<string> expected = {"this", "is", "a", "sample"};
    CHECK_EQ(expected, split("this,! is... a sample!!", ",.! "));
}

// source:
// https://www.boost.org/doc/libs/1_72_0/libs/regex/doc/html/boost_regex/ref/regex_token_iterator.html
// NOTE: regex-split is deprecated in favor for token iterator
TEST_CASE ("boost regex split") {
    using namespace std;

    auto f = [](const string &haystack) -> vector<string> {
        boost::regex re{"\\W+"};
        vector<string> out;
        for (auto it = boost::sregex_token_iterator{haystack.cbegin(), haystack.cend(), re, -1};
             it != boost::sregex_token_iterator{}; ++it) {
            out.push_back(it->str());
        }
        return out;
    };

    vector<string> expected = {"this", "is", "a", "sample"};
    CHECK_EQ(expected, f("this,! is... a sample!!"));
}