#ifndef ICOMPARABLE_H
#define ICOMPARABLE_H

class IComparable
{
public:
    virtual int compare_to(void* data) const = 0;
};

#endif /* ICOMPARABLE_H */
