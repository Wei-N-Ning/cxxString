//
// Created by wein on 18/08/18.
//

// source

// how to set option modifier
// and what are all the modifiers
// http://www.cplusplus.com/reference/regex/basic_regex/flags/
// http://www.cplusplus.com/reference/regex/regex_constants/#syntax_option_type
// https://en.cppreference.com/w/cpp/regex/syntax_option_type

// how to construct regex object with modifier
// http://www.cplusplus.com/reference/regex/basic_regex/basic_regex/

// what is ECMAscript
// https://en.cppreference.com/w/cpp/regex/ecmascript

// how to access match result
// https://en.cppreference.com/w/cpp/regex/regex_match

#include <iostream>
#include <regex>
#include <string>

std::regex createRegex(const char* pattern, bool ignoreCase = false ) {
    using namespace std::regex_constants;
    syntax_option_type option(ECMAScript);
    if (ignoreCase) {
        option |= icase;
    }
    return std::regex(pattern, option);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        return 1;
    }
    std::regex re;
    if (argc == 2) {
        re = createRegex(argv[1]);
    } else if (argc == 3 && *argv[2] == 'i') {
        re = createRegex(argv[1], true);
    }
    std::string line;
    std::smatch m;
    while (std::getline(std::cin, line).good()) {
        if (std::regex_match(line, m, re)) {
            std::cout << m[0] << std::endl;
        }
    }
    return 0;
}