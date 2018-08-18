#!/usr/bin/env bash

# source

# istream iterator:
# https://en.cppreference.com/w/cpp/iterator/istream_iterator

# observe the behavior:
# - istream_iterator reads one std::string at a time;
# - ignore whilespace characters, including space, tab and newline
#   (see whitespace characters:
#    https://en.wikipedia.org/wiki/Whitespace_character)
# - identify EOF
# - echo -e will enable interpretation of backslash escapes (therefore
#   special symbols such as \t is interpreted correctly)

CC=${CC-cc}
CXX=${CXX-c++}
DBG=${DBG-lldb}

set -e

TEMPDIR=/tmp/sut

tearDown() {
    rm -rf ${TEMPDIR} /tmp/_ /tmp/_.* /tmp/__*
}

setUp() {
    tearDown
    mkdir -p ${TEMPDIR}
}

sutbin=
buildSUT() {
    cat > ${TEMPDIR}/_.cpp << "EOF"
#include <regex>
#include <iostream>
#include <iterator>

using namespace std;

int main() {
    istream_iterator<string> iter(cin), end;
    while (iter != end) {
        cout << ":" << *(iter++);
    }
    return 0;
}
EOF
    ${CXX} -std=c++14 -o ${TEMPDIR}/_ ${TEMPDIR}/_.cpp
    sutbin=${TEMPDIR}/_
}

runSUT() {
    echo -e "
doom 1993\tdos
doom 2    1994\ndos
" | ${sutbin}
}

setUp
buildSUT
runSUT
tearDown
