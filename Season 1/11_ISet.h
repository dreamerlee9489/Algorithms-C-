#ifndef ISET_H
#define ISET_H
#define STD_ std::
#include <memory>
/**
 * @brief 集合基类
 * @date 2022-04-17
 * @tparam K
 */
template <typename K>
class ISet
{
protected:
    using Comparator = int (*)(STD_ shared_ptr<K> a, STD_ shared_ptr<K> b);
    using TraverseFunc = bool (*)(STD_ shared_ptr<K> key, STD_ shared_ptr<bool> value);
    
protected:
    ISet() = default;
    virtual ~ISet() = default;
    virtual size_t size() = 0;
    virtual bool is_empty() = 0;
    virtual bool contains(STD_ shared_ptr<K> data) = 0;
    virtual void add(STD_ shared_ptr<K> data) = 0;
    virtual void remove(STD_ shared_ptr<K> data) = 0;
    virtual void clear() = 0;
};

#endif /* ISET_H */
