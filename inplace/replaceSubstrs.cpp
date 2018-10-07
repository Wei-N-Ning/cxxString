//
// source
// stackoverflow replace all occurrences of substring

// read cpp reference about string.replace -> it obviously invalidates
// all the iterators if new needle has a different length to needle
//
// RELATED:
// see also strstr.c in cexamples project
// see also replace single character
//

#include <string>
#include <cassert>

void RunTinyTests();

void replaceAll(const std::string& i_needle,  
                const std::string& i_newNeedle,
                std::string& o_haystack) {
    using namespace std;
    
    for (size_t pos = 0;   
         pos != string::npos;
         pos = o_haystack.find(i_needle, pos)) {
        o_haystack.replace(pos, i_needle.size(), i_newNeedle);
        pos += i_newNeedle.size();
    }


}

void test_replace_substr_all_places() {
    using namespace std;

    string haystack{"iddqd_idfa,idkfa/idnoclip"};
    string needle{"id"};
    string newNeedle{"E.A."};
    
    replaceAll(needle, newNeedle, haystack);
    string expected{"E.A.dqd_E.A.fa,E.A.kfa/E.A.noclip"};
    assert(expected == haystack);
}

int main() {
    RunTinyTests();
    return 0;
}
