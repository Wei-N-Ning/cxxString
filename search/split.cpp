
// NOTE: this is to split at the FIRST occasion of <cstr>
// to make it behaves the same as the Python version I 
// need to change the return type to vector

#include <string>
#include <utility>
#include <cassert>
#include <cstring>

using namespace std;

pair<string, string> split(const std::string& text, const char* cstr) {
    size_t found = text.find(cstr);
    if (found == string::npos) {
        return {"", ""};
    }
    return {
        text.substr(0, found),
        text.substr(found + strlen(cstr))
    };
}

int main() {
    pair<string, string> result;
    
    // split in the middle
    result = split("idkfaiddqdidnoclip", "iddqd");
    assert(result.first == string("idkfa"));
    assert(result.second == string("idnoclip"));

    // split at the beginning
    result = split("idkfaiddqdidnoclip", "id");
    assert(result.first.empty());
    assert(result.second == string("kfaiddqdidnoclip"));
    
    // split at the end
    result = split("idkfaiddqdidnoclip", "noclip");
    assert(result.first == string("idkfaiddqdid"));
    assert(result.second.empty());
    
    // fail to split
    result = split("idkfaiddqdidnoclip", "idfa");
    assert(result.first.empty());
    assert(result.second.empty());

    return 0;
}

