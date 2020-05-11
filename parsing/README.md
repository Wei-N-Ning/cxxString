# Parsing stuffs in C++

parsing stuffs requires a framework and haskell's parsec & attoparsec have set the 
standard;

see a port of parsec in c++: <https://github.com/crockeo/parsical>

## Parse a comma separated list

the easiest tasks possible, see parse_csl.cpp

## Parse an object

see parse_struct.cpp, and how to recover from parsing-failure

## Parse key-value pairs

see parse_kv_pairs.cpp

see also ../regex/lookbehind, parsing a loosely structured text file that
contains `#property=value` statements
