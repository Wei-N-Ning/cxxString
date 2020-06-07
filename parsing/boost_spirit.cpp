//
// Created by weining on 7/6/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <string>
#include <optional>

// c++ boost app dev P/74
// NOTE there are a few typos in the pdf version of this book.
// see the following working example for my corrections
// NOTE:
// worth reading into this framework!
// it has a similar touch and feel to Haskell's parsec
// TODO: impl a ini parser in both qi and parsec, compare performance

struct Date {
    unsigned short year{0};
    unsigned short month{0};
    unsigned short day{0};
};

std::optional<Date> parse_s(const std::string &s) {
    using boost::spirit::qi::_1;
    using boost::spirit::qi::ushort_;
    using boost::spirit::qi::char_;
    using boost::phoenix::ref;

    Date res;
    const char *first = s.data();
    const char *last = first + s.size();
    bool success = boost::spirit::qi::parse(
        first, last,
        ushort_[ref(res.year) = _1] >> char_('-')
       >> ushort_[ref(res.month) = _1] >> char_('-')
       >> ushort_[ref(res.day) = _1]
    );
    /*
     * parse $ many digit
     *      <*> char '-'
     *      <*> twice digit
     *      <*> char '-'
     *      <*> twice digit
     * */
    return success ? std::optional<Date>{res} : std::optional<Date>{};
}

TEST_CASE ("") {
    using namespace std::string_literals;
    auto o1 = parse_s("1993-06-12"s);
    CHECK(o1.has_value());
    CHECK_EQ(o1->year, 1993);
    CHECK_EQ(o1.value().month, 6);

    if (auto o = parse_s("1-a-;"s); o.has_value()) {
        CHECK(false);
    }
    if (auto o = parse_s("2020-05-18"s); o.has_value()) {
        CHECK_EQ(o->year, 2020);
    } else {
        CHECK(false);
    }
}
