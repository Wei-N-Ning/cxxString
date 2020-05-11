//
// Created by weining on 12/5/20.
//

// modern c++ programming cookbook L2762
// an interesting thing about the token iterator is that it can return the unmatched
// parts of the string if the index of the subexpressions is -1, in which case it
// returns an std::match_results object that corresponds to the sequence of chars
// between the last match and the end of the sequence

using namespace std;
using namespace string_literals;
auto doc{R"TEXT(
-- don't do this: | Item
data Package =
    | Item
    -- | Follow Item
-- there is an Item
)TEXT"s};