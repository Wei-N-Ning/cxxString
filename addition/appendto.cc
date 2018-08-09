#include <string>
#include <cassert>
#include <cstring>

using namespace std;

int main() {
    string s;
    s += "asd";
    char c = 13 / 12 + 'A';
    s += c;
    assert(0 == strcmp(s.c_str(), "asdB"));
    return 0;
}
