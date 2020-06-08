//
// Created by weining on 7/6/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest/doctest.h"
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_bind.hpp>
#include <string>
#include <optional>

// c++ boost app dev P/74
// NOTE there are a few typos in the pdf version of this book.
// see the following working example for my corrections
// NOTE:
// worth reading into this framework!
// it has a similar touch and feel to Haskell's parsec
// this the second example for branching
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

// c++ boost app dev P/77
enum class ZoneOffsetType {
    OffsetNotSet,
    OffsetZ,
    OffsetUtcPlus,
    OffsetUtsMinus,
};

struct DateTime {
    unsigned short year;
    unsigned short month;
    unsigned short day;
    unsigned short hours;
    unsigned short minutes;
    unsigned short seconds;
    ZoneOffsetType zot;
    unsigned int zo_in_minutes;

    static void set_zone_offset(
        DateTime &dt,
        char sign,  // _1
        unsigned short hours,  // _2
        unsigned short minutes  // _3
    ) {
        if (sign == '+') {
            dt.zot = ZoneOffsetType::OffsetUtcPlus;
        }
    }

    static void set_zone_offset_type(
        DateTime &dt,
        ZoneOffsetType zot
    ) {
        dt.zot = zot;
    }
};

// c++ boost app dev P/80
// "rules" erases the type and allows you to write parsers in source files and export
// them in headers
// to optimize, do not use type-erasure
std::optional<DateTime> parse_dt(const std::string &s) {
    using boost::spirit::qi::_1;
    using boost::spirit::qi::_2;
    using boost::spirit::qi::_3;
    using boost::spirit::qi::uint_parser;
    using boost::spirit::qi::char_;
    using boost::phoenix::bind;
    using boost::phoenix::ref;

    DateTime dt{};

    uint_parser<unsigned short, 10, 2, 2> u2_;
    uint_parser<unsigned short, 10, 4, 4> u4_;
    boost::spirit::qi::rule<const char*, void()> timezone_parser =
        -(
            char_('Z')[bind(&DateTime::set_zone_offset_type, ref(dt), ZoneOffsetType::OffsetZ)]
            |
            ((char_('+') | char_('-')) >> u2_ >> ':' >> u2_)[bind(&DateTime::set_zone_offset, ref(dt), _1, _2, _3)]
        );

    boost::spirit::qi::rule<const char*, void()> date_parser =
        u4_[ref(dt.year) = _1] >> char_('-')
        >> u2_[ref(dt.month) = _1] >> char_('-')
        >> u2_[ref(dt.day) = _1];

    boost::spirit::qi::rule<const char*, void()> time_parser =
        u2_[ref(dt.hours) = _1] >> char_(':')
        >> u2_[ref(dt.minutes) = _1] >> char_(':')
        >> u2_[ref(dt.seconds) = _1];

    const char* first = s.data();
    const char* end = first + s.size();

    bool success = boost::spirit::qi::parse(
        first, end,
        (
                (
                    date_parser >> char_('T') >> time_parser
                    | date_parser
                    | time_parser
                )
                >> timezone_parser
        )
    );
    return success ? std::optional<DateTime>{dt} : std::optional<DateTime>{};
}

TEST_CASE ("parse date-time string with timezone info") {
    if (auto o = parse_dt("2020-02-12T12:12:12Z"); o.has_value()) {
        auto v = o.value();
        CHECK_EQ(v.year, 2020);
        CHECK_EQ(v.hours, 12);
        CHECK_EQ(v.zot, ZoneOffsetType::OffsetZ);
    } else {
        CHECK(false);
    }

    if (auto o = parse_dt("2020-02-12T13:23:45+09:30"); o.has_value()) {
        auto v = o.value();
        CHECK_EQ(v.year, 2020);
        CHECK_EQ(v.zot, ZoneOffsetType::OffsetUtcPlus);
    } else {
        CHECK(false);
    }
}
