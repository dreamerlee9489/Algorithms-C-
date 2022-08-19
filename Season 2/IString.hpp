#ifndef ISTRING_HPP
#define ISTRING_HPP

#include <string>

namespace app {
class IString {
public:
  virtual std::string to_string() const = 0;
};
} // namespace app

#endif /* ISTRING_HPP */
