#ifndef IMAP_H
#define IMAP_H
#define STD_ std::
#include <memory>
#include <queue>
#include <iostream>
#include "./IString.h"
/**
 * @brief 映射基类
 * @date 2022-04-19 
 * @tparam K 
 * @tparam V 
 */
template <typename K, typename V>
class IMap
{
protected:
    using TraverseFunc = bool (*)(STD_ shared_ptr<K> key, STD_ shared_ptr<V> value);
    using Comparator = int (*)(STD_ shared_ptr<K> a, STD_ shared_ptr<K> b);
    
public:
    IMap() = default;
    virtual ~IMap() = default;
    virtual size_t size() const = 0;
    virtual bool is_empty() const = 0;
    virtual bool contains_key(STD_ shared_ptr<K> key) const = 0;
    virtual bool contains_value(STD_ shared_ptr<V> value) const = 0;
    virtual STD_ shared_ptr<V> get_value(STD_ shared_ptr<K> key) const = 0;
    virtual STD_ shared_ptr<V> add(STD_ shared_ptr<K> key, STD_ shared_ptr<V> value) = 0;
    virtual STD_ shared_ptr<V> remove(STD_ shared_ptr<K> key) = 0;
    virtual void clear() = 0;
};

#endif /* IMAP_H */
