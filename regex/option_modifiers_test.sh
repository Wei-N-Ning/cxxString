#!/usr/bin/env bash

# inspired by
# perlFoo/strings/regex/optionModifiers.pl

sutbin=${1:?missing program}

# case sensitive
${sutbin} 'i[d]+.*' <<"EOF"
iddqd
IDDqd
idkfa
EOF

# case insensitive
${sutbin} 'i[d]+.*' 'i' <<"EOF"
iddqd--
IDDqd--
idkfa--
EOF
