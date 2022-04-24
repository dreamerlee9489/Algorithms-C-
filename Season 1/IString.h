#ifndef ISTRING_H
#define ISTRING_H
#define STD_ std::
#include <string>

class IString
{
public:
    virtual STD_ string to_string() const = 0;
};

#endif /* ISTRING_H */
