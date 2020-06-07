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

// take 1 does not check the number of digits
std::optional<Date> parse_s_take1(const std::string &s) {
    using boost::spirit::qi::_1;
    using boost::spirit::qi::ushort_;
    using boost::spirit::qi::char_;
    using boost::phoenix::ref;

    Date res;
    const char *first = s.data();
    const char* const last = first + s.size();
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
    // c++ boost app dev P/75
    // the parse() function returns true on success.
    // if we want to make sure that the whole string was successfully parsed
    // we need to check for the parser's return value and equality of the
    // input iterators
    // semantic actions in Boost.Spirit are written inside [] and they
    // can be written using function pointers, function objects, boost::bind
    // std::bind or C++11 lambda functions
    return success ? std::optional<Date>{res} : std::optional<Date>{};
}

// check the number of digits via template parameters
std::optional<Date> parse_s(const std::string &s) {
    using boost::spirit::qi::uint_parser;
    using boost::spirit::qi::char_;
    using boost::spirit::qi::_1;
    using boost::phoenix::ref;

    // use unsigned short as output type, require Radix 10, and from 2
    // to 2 digits
    uint_parser<unsigned short, 10, 2, 2> u2_;
    uint_parser<unsigned short, 10, 4, 4> u4_;

    Date res;
    const char *first = s.data();
    const char* const end = first + s.size();
    bool success = boost::spirit::qi::parse(
        first, end,
        u4_[ref(res.year) = _1]
        >> char_('-')
        >> u2_[ref(res.month) = _1]
        >> char_('-')
        >> u2_[ref(res.day) = _1]
    );
    return success ? std::optional<Date>{res} : std::optional<Date>{};
}

TEST_CASE ("parse date string") {
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
