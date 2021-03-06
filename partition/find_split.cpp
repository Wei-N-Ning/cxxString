//
// Created by wein on 20/08/18.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <algorithm>
#include <iterator>
#include <iostream>
#include <string>
#include <vector>
#include <cassert>

// see also: cExamples/tests/string/strstr.c 

template<typename T>
std::vector<T> find_split(const T& haystack, const T& needle) {
    std::vector<T> elements;
    if (haystack.empty() || needle.empty()) {
        return elements;
    }
    std::size_t curr = 0, next = 0, last = haystack.size() - 1;
    while (curr < last) {
        next = haystack.find(needle, curr);
        if (next == T::npos) {
            elements.emplace_back(haystack.substr(curr, last - curr + 1));
            break;
        } else if (curr != next) {
            elements.emplace_back(haystack.substr(curr, next - curr));
        }
        curr = next + needle.size();
    }
    return elements;
}

template<typename T>
inline void prt(const std::vector<T>& elems) {
    std::copy(elems.begin(), elems.end(),
        std::ostream_iterator<T>(std::cout, ", "));
    std::cout << std::endl;
}

inline void _assert(const std::vector<std::string>& elems,
                    const std::vector<std::string>& expected) {
    if (elems.size() == expected.size() &&
        std::equal(elems.begin(), elems.end(), expected.begin())) {
        ;
    } else {
        std::cout << "expected:" << std::endl;
        prt(expected);
        std::cout << "actual:" << std::endl;
        prt(elems);
        assert(false);
    }
}

TEST_CASE("needle is one char") {
    std::vector<std::string> elems;

    elems = find_split(
        std::string("/doom/doom2"),
        std::string("/"));
    _assert({"doom", "doom2"}, elems);

    elems = find_split(
        std::string("=doom=doom2=dune2"),
        std::string("="));
    _assert(elems, {"doom", "doom2", "dune2"});

    elems = find_split(
        std::string("==doom==doom2===dune2=="),
        std::string("="));
    _assert(elems, {"doom", "doom2", "dune2"});
}

TEST_CASE("needle has multiple chars") {
    std::vector<std::string> elems;

    elems = find_split(
        std::string("//doom///doom2"),
        std::string("//"));
    _assert({"doom", "/doom2"}, elems);

    elems = find_split(
        std::string("==doom==doom2==dune2"),
        std::string("=="));
    _assert(elems, {"doom", "doom2", "dune2"});

    elems = find_split(
        std::string("==doom==doom2===dune2=="),
        std::string("=="));
    _assert(elems, {"doom", "doom2", "=dune2"});
}

TEST_CASE("needle not found") {
    std::vector<std::string> elems;
    elems = find_split(
        std::string("//doom///doom2"),
        std::string("--"));

    // this behavior is similar to Python's
    _assert({"//doom///doom2"}, elems);

    elems = find_split(
        std::string("//doom///doom2"),
        std::string());
    assert(elems.empty());
}
