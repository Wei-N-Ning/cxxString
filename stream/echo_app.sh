#!/usr/bin/bash

sutbin=
buildApp() {
    cat >/tmp/_.cpp <<"EOF"
#include <iostream>
#include <iterator>
#include <algorithm>
int main() {
    using namespace std;
    auto isi = istreambuf_iterator<char>(cin.rdbuf());
    auto end = istreambuf_iterator<char>();
    copy(isi, end, ostream_iterator<char>(cout));
    return 0;
}
EOF
    c++ -std=c++14 /tmp/_.cpp -o /tmp/_
    sutbin=/tmp/_
}

runApp() {
    ${sutbin} <<"EOF"
there
is
a cow
EOF
}

buildApp
runApp
