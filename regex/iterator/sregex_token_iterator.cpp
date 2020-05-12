//
// Created by wein on 18/08/18.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

// source
// https://en.cppreference.com/w/cpp/regex/regex_token_iterator

// https://www.reddit.com/r/cpp/comments/5dxnwm/why_doesnt_stdstring_have_a_split_function/

//int main()
//{
//    std::string text = "Quick brown fox.";
//    std::regex ws_re("\\s+"); // whitespace
//    std::copy( std::sregex_token_iterator(text.begin(), text.end(), ws_re, -1),
//               std::sregex_token_iterator(),
//               std::ostream_iterator<std::string>(std::cout, "\n"));
//}

#include <algorithm>
#include <string>
#include <iostream>
#include <iterator>
#include <sstream>
#include <regex>

#include "absl/strings/match.h"

void process(std::istream &is, const std::string &delimiter_pattern = "\\s+") {
    std::regex delimiter(delimiter_pattern);
    std::string line;
    while(std::getline(is, line).good()) {
        if (line.size() < 2) {
            continue;
        }
        if (absl::StartsWith(line, "#")) {
            continue;
        }
        std::copy(
            std::sregex_token_iterator(
                line.cbegin(), line.cend(), delimiter, -1),
            std::sregex_token_iterator(),
            std::ostream_iterator<std::string>(std::cout, " ")
        );
    }
    std::cout << std::endl;
}

TEST_CASE ("using the default delimiter (whitespace characters)") {
    std::stringstream ss{R"DOC(
# comment:
[/]project(doom)
[/]scene(e1)
[/]shot(m1)

# comment:
[/]element(archvile)
[/]product(motion)

[/]version(101)
[/]resource(apm)

)DOC"};
    process(ss);
}

TEST_CASE ("using [/] as the delimiter") {
    std::stringstream ss{R"DOC(
# comment:
[/]project(doom)
[/]scene(e1)
[/]shot(m1)

# comment:
[/]element(archvile)
[/]product(motion)

[/]version(101)
[/]resource(apm)
)DOC"};
    process(ss, R"RE([\/])RE");
}