//
// Created by wein on 4/11/18.
//

#include <algorithm>
#include <string>
#include <cassert>
#include <cstring>
#include <vector>

using std::string;
using std::vector;

void RunTinyTests();

void test_toLower() {
    string actual;
    string sut{" ThereIsA cow@231\02"};
    std::transform(sut.begin(), sut.end(), std::back_inserter(actual), ::tolower);
    assert(0 == strcmp(" thereisa cow@231\02", actual.c_str()));
}

void test_integer_to_string() {
    auto n = std::to_string(90);
    assert(0 == strcmp("90", n.c_str()));
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}
