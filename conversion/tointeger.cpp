//
// Created by wein on 8/9/18.
//

#include <string>
#include <cassert>

void RunTinyTests();

void test_base10_successful() {
    assert(1337 == std::stoi("1337"));
}

void test_base10_unsuccessful() {
    // .48 is truncated; note stoi() returns the number of characters
    // successfully converted to the caller via an output parameter
    size_t numChars = 0;
    assert(13 == std::stoi("13.48", &numChars));
    assert(2 == numChars);

    // throw std::invalid_argument
    // assert(0 == std::stoi("a13.48"));
}

void test_base16_successful() {
    assert(0x3e7 == std::stoi("0x3e7", nullptr, 16));
    assert(0x3e7 == std::stoi("0003e7", nullptr, 16));
    assert(0x3e7 == std::stoi("3e7", nullptr, 16));
}


int main() {
    RunTinyTests();
    return 0;
}
