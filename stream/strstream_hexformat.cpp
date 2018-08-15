
#include <sstream>
#include <string>
#include <cassert>

using namespace std;

void print_int_in_hex_then_dec() {
    stringstream ss;
    ss << hex << 999 << dec << 999;
    assert(string("3e7999") == ss.str());
}

int main() {
    print_int_in_hex_then_dec();
    return 0;
}

