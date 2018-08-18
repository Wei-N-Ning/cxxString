#!/usr/bin/env bash

# source

# istream iterator:
# https://en.cppreference.com/w/cpp/iterator/istream_iterator

# In addition, std::istreambuf_iterator is more efficient,
# since it avoids the overhead of constructing and destructing the
# sentry object once per character.

# std::istreambuf_iterator is a single-pass input iterator that reads
# successive characters from the std::basic_streambuf object for which
# it was constructed.

# The default-constructed std::istreambuf_iterator is known as the
# end-of-stream iterator. When a valid std::istreambuf_iterator reaches
# the end of the underlying stream, it becomes equal to the
# end-of-stream iterator. Dereferencing or incrementing it further
# invokes undefined behavior.

# observe the behavior:
# - special characters are not skipped and are printed to the output
#   stream
# - recall Perl's "include newline" //s


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
    istreambuf_iterator<char> iter(cin.rdbuf()), end;
    while (iter != end) {
        cout << *(iter++);
    }
    return 0;
}
EOF
    ${CXX} -std=c++14 -o ${TEMPDIR}/_ ${TEMPDIR}/_.cpp
    sutbin=${TEMPDIR}/_
}

runSUT() {
    echo -e "-\n-
there is a cow 0x3e7
+\t+" | ${sutbin}
}

setUp
buildSUT
runSUT
tearDown

