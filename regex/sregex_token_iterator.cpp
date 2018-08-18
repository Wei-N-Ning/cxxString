//
// Created by wein on 18/08/18.
//

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
#include <regex>

int main(int argc, char** argv) {

    // default delimiter
    std::string delimiter_pattern("\\s+");
    if (argc == 2) {
        delimiter_pattern = argv[1];
    }
    std::regex delimiter(delimiter_pattern);

    std::string line;
    while(std::getline(std::cin, line).good()) {
        if (line.size() < 2) {
            continue;
        }
        if (line.find('#') == 0) {
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

    return 0;
}
