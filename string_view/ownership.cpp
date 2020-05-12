//
// Created by weining on 12/5/20.
//

#include <string_view>
#include <string>

// inspired by: https://www.youtube.com/watch?v=xwP4YCP_0q0
// some operator is missing in C++17 (such as the sv + sv operator)
// ensure std::string owns the data; string_view to read or peak the data

int main() {
    using namespace std;
    using namespace string_literals;
    using namespace string_view_literals;

    auto sv1{"asd"sv};
    auto sv2{"bsd"sv};
    auto s{"asdbasd"s};
    string_view sview{s};
}
