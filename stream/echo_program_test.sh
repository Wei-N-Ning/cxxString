#!/usr/bin/env bash

set -e
CC=cc
CXX=c++
TEMPDIR=/tmp/sut

tearDown() {
    rm -rf ${TEMPDIR}
}

setUp() {
    tearDown
    mkdir -p ${TEMPDIR}
}

sutbin=${TEMPDIR}/sut.bin
sutapp=${1:?missing program name!}
generateSUT() {
    dd if=/dev/urandom of=${sutbin} bs=5000000 count=1 >/dev/null 2>&1
}

roundTrip() {
    local expected=$( perl -MDigest::MD5=md5_hex -le 'print md5_hex(<> or die)' ${sutbin} )
    local outfile=${TEMPDIR}/out.bin
    ${sutapp} ${sutbin} ${outfile}
    local actual=$( perl -MDigest::MD5=md5_hex -le 'print md5_hex(<> or die)' ${outfile} )
    if [[ "${expected}" != "${actual}" ]]
    then
        echo "round trip failed!"
        exit 1
    fi
}

setUp
generateSUT
roundTrip
tearDown

