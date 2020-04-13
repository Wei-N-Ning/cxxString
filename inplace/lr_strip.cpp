#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <sstream>
#include <vector>
#include <cassert>

// source
// http://www.martinbroadhurst.com/how-to-trim-a-stdstring.html
// see also:
// http://www.cplusplus.com/reference/string/string/erase/

TEST_CASE("left strip") {
    auto f = [](std::string& o_str) {
        o_str.erase(0, o_str.find_first_not_of("\t\n\v\f\r "));
    };
    
    // note that the second row is ' iddqd ' (trailing space)
    std::string sut = R"IDDQD(
 iddqd 
ther
 2 1
)IDDQD";
    std::stringstream ss(sut);
    std::string line;
    std::vector<std::string> results;
    while (std::getline(ss, line).good()) {
        f(line);
        results.emplace_back(std::move(line));
    }
   
    std::vector<std::string> expected{"", "iddqd ", "ther", "2 1"};
    assert(expected == results);
}

TEST_CASE("right strip") {
    auto f = [](std::string& o_str) {
        o_str.erase(o_str.find_last_not_of("\t\n\v\f\r ") + 1);
    };
    
    // each non-empty line has some kind of whitespace characters
    std::string sut = R"IDDQD(
 iddqd  
ther      
 2 1   
)IDDQD";

    std::stringstream ss(sut);
    std::string line;
    std::vector<std::string> results;
    while (std::getline(ss, line).good()) {
        f(line);
        results.emplace_back(std::move(line));
    }
    
    std::vector<std::string> expected{"", " iddqd", "ther", " 2 1"};
    assert(expected == results);
}

TEST_CASE("strip") {
    auto f = [](std::string& o_str) {
        o_str.erase(0, o_str.find_first_not_of("\t\n\v\f\r "));
        o_str.erase(o_str.find_last_not_of("\t\n\v\f\r ") + 1);
    };

    std::string sut = R"IDDQD(
 idd qd         
   ther   
 2 1  
)IDDQD";

    std::stringstream ss(sut);
    std::string line;
    std::vector<std::string> results;
    while (std::getline(ss, line).good()) {
        f(line);
        results.emplace_back(std::move(line));
    }
    
    std::vector<std::string> expected{"", "idd qd", "ther", "2 1"};
    assert(expected == results);
}
