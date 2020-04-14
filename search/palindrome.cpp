//
// Created by wein on 15/04/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"

#include <string>

// modern C++ challenges P/61
std::string palindromic_substr(const std::string &s) {
    using namespace std;

    string ss;

    // this is the brutal force method, the resulting performance is O(N^3)
    // however, I can reuse the previous computation, as observation shows
    // that the longer palindrome string is built upon a shorter one, as
    // it grows each end by one element
    // use a 2D array (or 1D with idx trick) to store the previous results
    auto ispalindromic = [&s](int start, int end) {
        for (auto i = 0; i < (end - start + 1) / 2; ++i) {
            if (s[start + i] != s[end - i]) {
                return false;
            }
        }
        return true;
    };
    for (auto i = 0; i < s.size(); ++i) {
        for (auto j = s.size() - 1; j > i; --j) {
            if (ispalindromic(i, j)) {
                auto ss_ = s.substr(i, j - i + 1);
                if (ss_.size() > ss.size()) {
                    ss = ss_;
                }
            }
        }
    }
    return ss;
}

TEST_CASE ("find palindromic substr") {
    using namespace std;

    CHECK_EQ(string{"case||esac"}, palindromic_substr("e1m1case||esaciddqd"));
    //                                                 dqddicase||esac
}
