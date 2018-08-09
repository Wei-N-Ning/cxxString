#include <iostream>
#include <string>
#include <cstring>

using namespace std;


void modify(string& sut) {
    int delta = sut[0] > 'a' ? -32 : 32;
    for (auto& c : sut) {
        c += delta;
    }
}

void modify_(string& sut) {
    for (int i = sut.size(); i--; ){
        sut[i] = 'A';
    }
}

int main() {
    string s{"thereisacow"};
    modify(s);
    cout << s << endl;
    modify(s);
    cout << s << endl;
    modify_(s);
    cout << s << endl;
    return 0;
}
