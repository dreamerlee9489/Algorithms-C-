#ifndef IMAP_H
#define IMAP_H
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
    using Comparator = int (*)(std::shared_ptr<K> a, std::shared_ptr<K> b);
    IMap() = default;
    virtual ~IMap() = default;
    virtual size_t size() const = 0;
    virtual bool is_empty() const = 0;
    virtual bool contains_key(std::shared_ptr<K> key) const = 0;
    virtual bool contains_value(std::shared_ptr<V> value) const = 0;
    virtual std::shared_ptr<V> get_value(std::shared_ptr<K> key) const = 0;
    virtual std::shared_ptr<V> add(std::shared_ptr<K> key, std::shared_ptr<V> value) = 0;
    virtual std::shared_ptr<V> remove(std::shared_ptr<K> key) = 0;
    virtual void clear() = 0;
};

#endif /* IMAP_H */
