
#include <string>
#include <cstring>
#include <cassert>

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
    return 0;
}
