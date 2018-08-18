//
// Created by wein on 18/08/18.
//

#include <iostream>
#include <string>

int main() {
    std::string line;
    while (std::getline(std::cin, line).good()) {
        std::cout << ":" << line << std::endl;
    }
    return 0;
}