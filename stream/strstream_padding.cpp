
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cassert>

using namespace std;

void left_adjustified() {
    stringstream ss;
    ss << left << setfill(' ') << setw(7) << "12345";
    assert(string("12345  ") == ss.str());
}

void right_adjustified() {
    stringstream ss;
    ss << right << setfill('.') << setw(8) << "4123";
    assert(string("....4123") == ss.str());
}

// the default behavior of io manipulator affects the immediate output
void partially_adjustified() {
    stringstream ss;
    ss << right << setfill(' ') << setw(3) << 98;
    ss << " # " << "text";
    assert(string(" 98 # text") == ss.str());
}

int main() {
    left_adjustified();
    right_adjustified();
    partially_adjustified();
    return 0;
}
