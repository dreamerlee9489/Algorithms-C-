#ifndef ISTRING_H
#define ISTRING_H
#include <string>

namespace app
{
    class IString
    {
    public:
        virtual std::string to_string() const = 0;
    };
} // namespace app

#endif /* ISTRING_H */
