//
// Created by wein on 19/08/18.
//

// source
// https://en.cppreference.com/w/cpp/regex/regex_iterator
// https://stackoverflow.com/questions/14664537/c11-regex-find-capture-group-identifier

#include <iostream>
#include <regex>
#include <string>

int main(int argc, char** argv) {
    if (argc < 2) {
        return 1;
    }
    std::regex re(argv[1]);
    std::string line;
    std::regex_iterator<std::string::const_iterator> end;
    while (std::getline(std::cin, line).good()) {
        // it is of type,
        // std::regex_iterator<std::string::const_iterator>
        auto it = std::sregex_iterator(line.cbegin(), line.cend(), re);
        while (it != end) {
            std::smatch m = *(it++);
            std::cout << ":" << m.str();
        }
        std::cout << std::endl;
    }
    return 0;
}