#ifndef IHASHABLE_H
#define IHASHABLE_H
#include <memory>

class IHashable
{
public:
    virtual int hash_code() = 0;
    virtual bool equals(void *data) = 0;
};

#endif /* IHASHABLE_H */
