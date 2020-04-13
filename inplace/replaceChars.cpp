//
// Created by wein on 8/10/18.
//

// source
// http://www.cs.cmu.edu/~gregjor/project/eckelbook/volume2/Chap04.htm
// see also (snippets)
// http://www.yolinux.com/TUTORIALS/LinuxTutorialC++StringClass.html


// source:
// see stackoverflow about std::replace() in STL <algorithms>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <algorithm>
#include <string>

#include <cassert>
#include <cstring>

TEST_CASE("replace all chars") {
    using namespace std;

    string haystack{"iddqd/idkfa idnoclip_idfa"};
    string needle{"i"};
    string new_needle{"E"};
    replace(haystack.begin(), haystack.end(), 'i', 'E');
    string expected{"Eddqd/Edkfa EdnoclEp_Edfa"};
    
    assert(expected == haystack); 
    assert(0 == strcmp(expected.c_str(), haystack.c_str()));
}

