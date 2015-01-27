#include <unique_justseen.hpp>

#include "helpers.hpp"

#include <vector>
#include <string>
#include <iterator>

#include "catch.hpp"

using iter::unique_justseen;

using Vec = const std::vector<int>;

TEST_CASE("unique justseen: adjacent repeating values", "[unique_justseen]") {
    Vec ns = {1,1,1,2,2,3,4,4,5,6,7,8,8,8,8,9,9};
    auto ue = unique_justseen(ns);
    Vec v(std::begin(ue), std::end(ue));
    Vec vc = {1,2,3,4,5,6,7,8,9};
    REQUIRE( v == vc );
}

TEST_CASE("unique justseen: some repeating values", "[unique_justseen]") {
    Vec ns = {1,2,2,3,4,4,5,6,6};
    auto ue = unique_justseen(ns);
    Vec v(std::begin(ue), std::end(ue));
    Vec vc = {1,2,3,4,5,6};
    REQUIRE( v == vc );
}

TEST_CASE("unique justseen: doesn't omit non-adjacent duplicates",
        "[unique_justseen]") {
    Vec ns = {1,2,3,2,1,2,3,2,1};
    auto ue = unique_justseen(ns);
    Vec v(std::begin(ue), std::end(ue));
    REQUIRE( v == ns );
}

TEST_CASE("unique justseen: moves and binds correctly", "[unique_justseen]") {
    itertest::BasicIterable<int> bi{1, 2};
    unique_justseen(bi);
    REQUIRE_FALSE( bi.was_moved_from() );

    unique_justseen(std::move(bi));
    REQUIRE( bi.was_moved_from() );
}