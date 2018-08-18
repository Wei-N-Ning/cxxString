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
# - note that when using heredoc, \t, \n is not interpreted

set -e

TEMPDIR=/tmp/sut

tearDown() {
    rm -rf ${TEMPDIR} /tmp/_ /tmp/_.* /tmp/__*
}

setUp() {
    tearDown
    mkdir -p ${TEMPDIR}
}

sutbin=${1:?missing program}

runSUT() {
    # use stdin
    echo -e "
doom 1993\tdos
doom 2    1994\ndos
" | ${sutbin}
    echo ""

    # use a file
    cat >${TEMPDIR}/text <<EOF
doom 1993 dos
doom 2    1994
dos
EOF
    ${sutbin} ${TEMPDIR}/text
    echo ""
}

setUp
runSUT
tearDown
