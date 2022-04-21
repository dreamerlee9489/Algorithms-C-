#ifndef ISET_H
#define ISET_H
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
    ISet() = default;
    virtual ~ISet() = default;
    virtual size_t size() = 0;
    virtual bool is_empty() = 0;
    virtual bool contains(std::shared_ptr<K> data) = 0;
    virtual void add(std::shared_ptr<K> data) = 0;
    virtual void remove(std::shared_ptr<K> data) = 0;
    virtual void clear() = 0;
};

#endif /* ISET_H */
