#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <boost/format.hpp>
#include <string>
#include <iostream>

// good old printf
// it can be useful in a multi-threading situation, for quickly
// dumping some text to stdout
// format:
// https://stackoverflow.com/questions/3209909/how-to-printf-unsigned-long-in-c
//
// for unsigned long/long type
// %llu, %lu,

// c++ boost app dev P/211
struct Item
{
    std::size_t id{};
    std::string name{};
    int value{};

    [[nodiscard]] std::string to_str( const std::string &f_ ) const
    {
        boost::format f( f_ );
        unsigned char flags = boost::io::all_error_bits;
        flags ^= boost::io::too_many_args_bit;
        f.exceptions( flags );
        return ( f % id % name % value ).str();
    }
};

TEST_CASE( "use printf format tokens" )
{
    Item i{ 123, "woodhead", 3 };
    std::cout << i.to_str( "id: %llu, there is, a cow named %s, with value %i" ) << std::endl;
}
