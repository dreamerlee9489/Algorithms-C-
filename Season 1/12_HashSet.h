#ifndef HASH_SET_H
#define HASH_SET_H
#include "./11_ISet.h"
#include "./15_HashMap.h"
/**
 * @brief 哈希集合
 * @date 2022-04-21
 * @tparam K 键必须继承IHashable
 */
template <typename K>
class HashSet : public ISet<K>
{
    using Comparator = int (*)(std::shared_ptr<K> a, std::shared_ptr<K> b);
    using TraverseFunc = bool (*)(std::shared_ptr<K> key, std::shared_ptr<bool> value);
    HashMap<K, bool> *map = nullptr;

public:
    HashSet(Comparator comparator = nullptr) { map = new HashMap<K, bool>(comparator); }
    ~HashSet() { delete map; }
    size_t size() override { return map->size(); }
    bool is_empty() override { return map->is_empty(); }
    bool contains(std::shared_ptr<K> data) override { return map->contains_key(data); }
    void add(std::shared_ptr<K> data) override { map->add(data, std::make_shared<bool>(true)); }
    void remove(std::shared_ptr<K> data) override { map->remove(data); }
    void traverse(TraverseFunc func = nullptr) { map->traverse(func); }
    void clear() override { map->clear(); }
};

#endif /* HASH_SET_H */
