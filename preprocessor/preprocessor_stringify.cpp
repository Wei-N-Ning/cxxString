//
// Created by weining on 16/5/20.
//

// I have run into this many times:
// how can I expand a macro inside a quoted cstring? (and turn it into a
// std::string or even std::filesystem::path ?)

// boost provides a preprocessor macro stringify but I don't want to pull
// in such a heavy weight library just to expand a handful of characters

// see:
// https://stackoverflow.com/questions/20631922/expand-macro-inside-string-literal
// https://stackoverflow.com/questions/12958925/expand-macros-inside-quoted-string

// do:
#define STRINGIFY2(X) #X
#define STRINGIFY(X) STRINGIFY2(X)

// official guide from GCC:
// https://gcc.gnu.org/onlinedocs/gcc-4.8.5/cpp/Stringification.html
