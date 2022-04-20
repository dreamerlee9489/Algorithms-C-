#ifndef IHASHABLE_H
#define IHASHABLE_H
#include <memory>

class IHashable
{
public:
    virtual int hash_code() const = 0;
    virtual bool equals(void *data) const = 0;
};

#endif /* IHASHABLE_H */
