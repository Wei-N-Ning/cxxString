#!/usr/bin/env bashi

setUp() {
    set -e 
}

buildSUT() {
    cat > /tmp/_.cpp <<EOF
#include <boost/algorithm/string.hpp>
#include <vector>
#include <string>
#include <iostream>
int main() {
    std::vector<std::string> values;
    boost::split(values, "1:a/b/c::da2:", boost::is_any_of(":"));
    for (const auto &v : values) {
        std::cout << "(" << v << ")" << std::endl;
    }
    return 0;
}
EOF
    g++ -std=c++11 -o /tmp/_ /tmp/_.cpp
}

runSUT() {
    /tmp/_
}

setUp
buildSUT
runSUT

