//
// Created by weining on 12/5/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <string>
#include <bitset>
#include <iostream>

// inspired by: cppcon 2018: std::basic_string for more than just text
// https://www.youtube.com/watch?v=SDJImePyftY
// advantages:
// - has a vector-like auto-growing storage mechanism
// - get to use the string API (particularly, concatenation algorithm)
// - can stick in a complex structure
// - can take advantage of small-string optimization (such as .size() call)

void toggle_bits(std::basic_string<bool> &bit_states) {
    for (auto &b : bit_states) {
        b = !b;
    }
}

template<typename T>
void print_bits(T t) {
    for (auto &b : t) {
        std::cout << b;
    }
    std::cout << std::endl;
}

bool operator""_b(unsigned long long int n) {
    return n == 1;
}

TEST_CASE ("use string as bitset") {
    using namespace std;

    basic_string<bool> bsets{1_b, 1_b, 0_b, 1_b, 0_b, 1_b, 1_b, 0_b};
    print_bits(bsets);
    toggle_bits(bsets);
    print_bits(bsets);
}

enum class bit_direction : unsigned char {
    input,
    output,
};

struct alignas(16) bit {
    bool state{0_b};  // 1
    bit_direction direction{bit_direction::input};  // 1
    char code[14]{"UNKNOWN"};  // rest of
};

TEST_CASE ("stick in a structure in string") {
    // stick a struct in the string
    static_assert(sizeof(bit) == 16);

    using namespace std;
    basic_string<bit> bsets{
        bit{1_b, bit_direction::output, "TECH"},
        bit{0_b, bit_direction::input, "DEV"},
        bit{0_b, bit_direction::output, "DEBUG"},
        bit{0_b, bit_direction::input, "RELEASE"},
    };

    // concat like string
    // can be handy when there is a C-API expecting some array of structs
    // and the data is concatenated on the fly using this "string"
    bsets.push_back(bit{});

    for (auto &b : bsets) {
        if (b.direction == bit_direction::output) b.state = !b.state;
    }
    CHECK_FALSE(bsets[0].state);
}

// the down side is std:bitset has fixed size
TEST_CASE ("std::bitset") {
    using namespace std;

    bitset<16> bset{0b0000000101010101};
    CHECK_EQ(bset.flip(), bitset<16>{0b1111111010101010});
}
