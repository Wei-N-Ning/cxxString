#include <string>
#include <cstring>
#include <cassert>

using std::string;

int main() {
    const char* cstr = "asd\000asdsad\000asdasdasdasd\000asd";
    string s(cstr);
    assert(strlen(cstr) == s.size());
    return 0;
}

