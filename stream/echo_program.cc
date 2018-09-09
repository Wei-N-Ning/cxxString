#include <iostream>
#include <fstream>

// source
// more exceptional c++ Item 1 P3

// take home lessons:
// how to use iostream, fstream
// prefer encapsulation (and recall compile time polymorphism, which 
// merely requires the passed object to have a suitable interface, 
// such as rdbuf() - recall Go's interface system)

// std::cin is std::basic_istream<char, std::char_traits<char>>
// std::cout is std::basic_ostream<char, std::char_traits<char>>
//
template<typename CharType, typename CharTraits>
void process(
    const std::basic_istream<CharType, CharTraits>& i_in, 
    std::basic_ostream<CharType, CharTraits>& o_out) {
    o_out << i_in.rdbuf();
}

// read:
// stackoverflow has a post on why ifstream, ofstream constructor
// are protected - "why constructor of std::ofstream is protected"
// Note the way it identifies the incoming stream - from pipe or arg
int main(int argc, char** argv) {
    using namespace std;
    fstream in, out;
    if (argc > 2) {
        out.open(argv[2], ios::out | ios::binary);
    }
    if (argc > 1) {
        in.open(argv[1], ios::in | ios::binary);
    }
    process(in.is_open() ? in : cin, out.is_open() ? out : cout);
    return 0;
}
