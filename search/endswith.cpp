//$(which true); dst=/var/tmp/sut; out=${dst}/$0.bin; mkdir -p ${dst}; c++ -std=c++14 -Wall -o "${out}" 1>&2 "$0" && "${out}" "$@"; exit $?

#include <string>
#include <cstring>
#include <cassert>
#include <iostream>

using namespace std;

bool endswith(const string& text, const char* cstr) {
    size_t found = text.rfind(cstr);
    if (found == string::npos) {
        return false;
    }
    return text.size() - found == strlen(cstr);
}

int main() {
    string text("0x123 someFunc at tst/sometest.cc");
    assert(endswith(text, ".cc"));
    assert(! endswith(text, ".cpp"));
    
    cout << "+ DONE" << endl;
    return 0;
}
