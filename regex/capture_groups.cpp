//
// Created by wein on 19/08/18.
//

// source
// https://stackoverflow.com/questions/29321249/regex-grouping-matches-with-c-11-regex-library

// important:
// https://en.cppreference.com/w/cpp/regex/regex_search
// regex_search will successfully match any subsequence of the given
// sequence;
// whereas std::regex_match will only return true if the regular
// expression matches the entire sequence.

#include <iostream>
#include <regex>
#include <string>

int main(int argc, char** argv) {
    if (argc < 2) {
        return 1;
    }
    std::regex re(argv[1]);
    std::string line;
    std::smatch m;
    while (std::getline(std::cin, line).good()) {
        size_t numMatchesPerLine = 0;
        while (std::regex_search(line, m, re)) {
            size_t numMatches = m.size();
            numMatchesPerLine++;
            for (size_t i = 1; i < numMatches; ++i) {
                std::cout << ":" <<  m[i].str();
            }
            line = m.suffix().str();
        }
        if (numMatchesPerLine > 0) {
            std::cout << " " << "matches: " << numMatchesPerLine \
                      << std::endl;
        }
    }
    return 0;
}