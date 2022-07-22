#ifndef LINKED_HASH_SET_HPP
#define LINKED_HASH_SET_HPP
#include "./11_ISet.hpp"
#include "./16_LinkedHashMap.hpp"

namespace app
{
    /**
     * @brief 按元素添加顺序遍历的哈希集合
     * @date 2022-04-21
     * @tparam K
     */
    template <typename K>
    class LinkedHashSet : public ISet<K>
    {
        LinkedHashMap<K, bool> *map = nullptr;

    public:
        LinkedHashSet(typename ISet<K>::Comparator comparator = nullptr) { map = new LinkedHashMap<K, bool>(comparator); }
        ~LinkedHashSet() { delete map; }
        size_t size() override { return map->size(); }
        bool is_empty() override { return map->is_empty(); }
        bool contains(shared_ptr<K> data) override { return map->contains_key(data); }
        void add(shared_ptr<K> data) override { map->add(data, make_shared<bool>(true)); }
        void remove(shared_ptr<K> data) override { map->remove(data); }
        void traverse(typename ISet<K>::TraverseFunc func = nullptr) { map->traverse(func); }
        void clear() override { map->clear(); }
    };
} // namespace app

#endif /* LINKED_HASH_SET_HPP */
