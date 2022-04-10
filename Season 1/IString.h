#ifndef ISTRING_H
#define ISTRING_H
#include <string>

class IString
{
public:
    virtual std::string to_string() const = 0;
};

#endif /* ISTRING_H */
