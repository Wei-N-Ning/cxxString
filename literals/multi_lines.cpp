//
// Created by wein on 19/08/18.
//

// source:
// raw string literals
// https://en.cppreference.com/w/cpp/language/string_literal
// https://stackoverflow.com/questions/1135841/c-multiline-string-literal
// good explanation on the delimiter symbols;

// used here:
// https://stackoverflow.com/questions/29321249/regex-grouping-matches-with-c-11-regex-library

// see embedded text file exploit
// ./embedded_text_file

#include <cassert>
#include <cstring>
#include <iostream>

void test_text() {
    const char* cstr = R"IDDQD(--
there is
a cow
//
// Created
--)IDDQD";
    std::cout << cstr;
}

int main() {
    test_text();
    return 0;
}