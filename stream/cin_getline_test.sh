#!/usr/bin/env bash

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
    ${sutbin} <<"EOF"
there
there "is"
there is ${a} cow
there is a cow 0x3e7
EOF
}

setUp
runSUT
tearDown
