#ifndef HASH_SET_H
#define HASH_SET_H
#include "./11_ISet.h"
#include "./15_HashMap.h"
/**
 * @brief 哈希集合
 * @date 2022-04-21
 * @tparam K 
 */
template <typename K>
class HashSet : public ISet<K>
{
    HashMap<K, bool> *map = nullptr;

public:
    HashSet(typename ISet<K>::Comparator comparator = nullptr) { map = new HashMap<K, bool>(comparator); }
    ~HashSet() { delete map; }
    size_t size() override { return map->size(); }
    bool is_empty() override { return map->is_empty(); }
    bool contains(STD_ shared_ptr<K> data) override { return map->contains_key(data); }
    void add(STD_ shared_ptr<K> data) override { map->add(data, STD_ make_shared<bool>(true)); }
    void remove(STD_ shared_ptr<K> data) override { map->remove(data); }
    void traverse(typename ISet<K>::TraverseFunc func = nullptr) { map->traverse(func); }
    void clear() override { map->clear(); }
};

#endif /* HASH_SET_H */
