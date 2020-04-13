//
// Created by wein on 4/11/18.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

#include <algorithm>
#include <cassert>
#include <cstring>
#include <string>
#include <vector>

using std::string;
using std::vector;

TEST_CASE("to lower") {
  string actual;
  string sut{" ThereIsA cow@231\02"};
  std::transform(sut.begin(), sut.end(), std::back_inserter(actual), ::tolower);
  assert(0 == strcmp(" thereisa cow@231\02", actual.c_str()));
}

TEST_CASE("int to string") {
  auto n = std::to_string(90);
  assert(0 == strcmp("90", n.c_str()));
}
