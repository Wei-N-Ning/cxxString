//
// Created by wein on 15/03/20.
// source: https://en.cppreference.com/w/cpp/locale/ctype
// also mentioned in category theory for programmer P/24
// comparing c++ isdigit with std::ctype::do_is
// L"..." and L'x' is wide string literal, see:
// https://en.cppreference.com/w/cpp/language/string_literal

#include "predicates.hh"
#include <iostream>
#include <locale>
#include <sstream>

void RunTinyTests();

struct csv_whitespace : std::ctype<wchar_t> {
  bool do_is(mask m, char_type c) const override {
    if ((m & space) && c == L' ') {
      return false; // space will NOT be classified as whitespace
    }
    if ((m & space) && c == L',') {
      return true; // comma will be classified as whitespace
    }
    return ctype::do_is(m, c); // leave the rest to the parent class
  }
};

void test_parse_csv() {
  std::wstring in = L"Column 1,Column 2,Column 3\n123,456,789";
  std::wstring token;

  std::wcout << "default locale:\n";
  std::wistringstream s1(in);
  while (s1 >> token) {
    std::wcout << "  " << token << '\n';
  }

  std::wcout << "locale with modified ctype:\n";
  std::wistringstream s2(in);
  auto *my_ws = new csv_whitespace; //csv_whitespace
  s2.imbue(std::locale(s2.getloc(), my_ws));
  while (s2 >> token) {
    std::wcout << "  " << token << '\n';
  }
}

int main() {
  RunTinyTests();
  return 0;
}
