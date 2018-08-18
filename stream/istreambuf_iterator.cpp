//
// Created by wein on 18/08/18.
//

#include <regex>
#include <iostream>
#include <iterator>

using namespace std;

int main() {
    istreambuf_iterator<char> iter(cin.rdbuf()), end;
    while (iter != end) {
        cout << *(iter++);
    }
    return 0;
}