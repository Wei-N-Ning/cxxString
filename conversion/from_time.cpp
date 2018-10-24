
#include <iostream>
#include <string>
#include <chrono>

void RunTinyTests();

void test_from_nanoseconds_to_uint64() {
    uint64_t now = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count(); 
    std::string s = std::to_string(now);
    std::cout << now << " -> " << s << std::endl;
}

int main() {
    RunTinyTests();

    return 0;
}
