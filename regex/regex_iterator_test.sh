#!/usr/bin/env bash

# source:
# https://stackoverflow.com/questions/14664537/c11-regex-find-capture-group-identifier

sutbin=${1:?missing program}

# search for whole words (no whitespace characters)
echo 'there is a cow' | ${sutbin} '\w+'
echo 'there is a cow' | ${sutbin} '\S+'

# search for pattern with enclosing symbols
# note ( and ) must be escaped
echo '/project(doom)/scene(e1)' | ${sutbin} '\w+\(\w+\)'
echo '/project(doom)/scene(e1)' | ${sutbin} '\(\w+\)'

