
#include <iostream>
#include <string>
#include <cassert>

using namespace std;

int main() {
    string text{"0x123 someFunc at tst/sometest.cc:123"};
    size_t found = text.find("at");
    assert(found != string::npos);
    cout << text.substr(found) << endl;
    cout << __FILE__ << endl;
    return 0;
}
