//
// Created by wein on 18/08/18.
//

// source
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2014/n4066.htm
// The problem is that the delimiter in the ostream_iterator constructor
// call is better described as a suffix than a delimiter.

#include <algorithm>
#include <vector>
#include <iterator>
#include <iostream>

int main() {
    std::vector<int> sut{1, 3, 3, 1};
    std::cout << "(";
    std::copy(sut.cbegin(), sut.cend(),
        std::ostream_iterator<int>(std::cout, ", "));
    std::cout << ")";
    return 0;
}