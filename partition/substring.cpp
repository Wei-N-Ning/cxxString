//
// Created by wein on 8/10/18.
//

#include <string>
#include <cassert>

void RunTinyTests();

static std::string s_sut;

void setUp() {
    s_sut.clear();
    s_sut += "thereis ac ow 13 37";
}

void tearDown() {
    s_sut.clear();
}

void test_out_of_range() {
    // throw std::out_of_range
    // s_sut.substr(1000, 2000);

    // truncate to the last character
    std::string a = s_sut.substr(4, 1000);
    assert(a == std::string{"eis ac ow 13 37"});

    // it is not possible to go out of range on the beginning side
    // ie. sut.substr(-100, 100);  IDE warning

    std::string b(s_sut.cbegin() + 6, s_sut.cend() - 10);
    assert(b == std::string("s a"));

    // end < start
    // throws std::length_error
    // std::string(s_sut.cbegin() + 6, s_sut.cend() - 14);
}

void test_use_iterators() {
    ;
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}