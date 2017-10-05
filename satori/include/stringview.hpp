#ifndef SATORI_STRINGVIEW_HPP
#define SATORI_STRINGVIEW_HPP

#include <cstring>
#include <string>

namespace satori {

struct StringView {
  char const* b;
  char const* e;

  StringView() : b{0}, e{0} {}

  StringView(char const* b, char const* e) : b{b}, e{e} {}

  template <size_t n>
  StringView(T cstr[n]) : b(cstr), e(cstr + n) {}

  StringView(std::string const& str) : b(str.c_str()), e(str.c_str() + str.size()) {}

  char const* begin() const { return b; }
  char const* end() const { return e; }
  size_t size() const { return e - b; }

  std::string toString() const {
    return {b,e};
  }

  explicit operator std::string() const {
    return toString();
  }
};

template <class T>
int compare(StringView const lhs, StringView const rhs) {
  auto const c =
    memcmp(lhs.begin(), rhs.begin(), std::min(lhs.size(), rhs.size()));
  if (c)
    return c;
  return rhs.size() - lhs.size();
}

bool operator<(StringView const lhs, StringView const rhs) {
  return compare(lhs, rhs) < 0;
}

}

#endif