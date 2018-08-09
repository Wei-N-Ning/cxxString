//
// Created by wein on 6/8/18.
//

#include <boost/algorithm/string.hpp>

#include <cassert>
#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <memory>

void RunTinyTests();

void populateString(const std::string& element, const std::string& delimiter, size_t count, std::string& o_str) {
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


void test_boostSplit() {
    using StrVec = std::vector<std::string>;
    using PStrVec = std::shared_ptr<StrVec>;
    using PStr = std::shared_ptr<std::string>;
    auto text = std::make_shared<std::string>();
    auto values = std::make_shared<StrVec>();
    text->reserve(50000);
    values->reserve(50000);

    populateString("thereisacow", ":", 10000, *text);
    std::string& textRef = *text;
    StrVec& valuesRef = *values;

    auto start = clock();
    boost::split(valuesRef, textRef, boost::is_any_of(":"));
    auto us = clock() - start;
    printf("boost::split %f us (%f s)\n", (float)us, (float)(us / 1e6));

    assert(10001 == values->size());
}

void test_strstr() {
    auto cstr = (char *)malloc(150000);
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
    printf("strstr %f us (%f s)\n", (float)us, (float)(us / 1e6));
    free(cstr);

    assert(10000 == count);  // this method excludes 0-length element (such as ::)
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}
