#!/usr/bin/env bash

# to extract <name>(<value>) pairs in the text
# note regex_search yields the first matching sub sequence  therefore I
# need to repeatedly process match.suffix().str() to process the rest
# of the text

sutbin=${1:?missing program}

echo '/project(doom)/scene(e1)' | ${sutbin} '(\w+)\((\w+)\)'
${sutbin} 'TypeTester\<(.*)\>' <<"EOF"
_.cpp: In function ‘int main()’:
_.cpp:4:21: error: aggregate ‘TypeTester<StringView> tt’ has
incomplete type and cannot be defined
     TypeTester<StringView> tt;
                     ^
EOF
