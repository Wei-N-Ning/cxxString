
#include <iostream>
#include <string>
#include <chrono>

int main() {
    uint64_t now = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count(); 
    std::string s = std::to_string(now);
    std::cout << now << " -> " << s << std::endl;
    
    return 0;
}
