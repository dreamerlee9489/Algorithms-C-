#ifndef LINKED_HASH_SET_HPP
#define LINKED_HASH_SET_HPP

#include "./11_ISet.hpp"
#include "./16_LinkedHashMap.hpp"

namespace app {
    /**
     * @brief 按元素添加顺序遍历的哈希集合
     * @date 2022-04-21
     * @tparam K
     */
    template<typename K>
    class LinkedHashSet : public ISet<K> {
        LinkedHashMap<K, bool> *_map = nullptr;

    public:
        LinkedHashSet(typename ISet<K>::Comparator comparator = nullptr) {
            _map = new LinkedHashMap<K, bool>(comparator);
        }

        ~LinkedHashSet() { delete _map; }

        size_t size() override { return _map->size(); }

        bool is_empty() override { return _map->is_empty(); }

        bool contains(shared_ptr<K> data) override { return _map->contains_key(data); }

        void add(shared_ptr<K> data) override { _map->add(data, make_shared<bool>(true)); }

        void remove(shared_ptr<K> data) override { _map->remove(data); }

        void traverse(typename ISet<K>::TraverseFunc func = nullptr) { _map->traverse(func); }

        void clear() override { _map->clear(); }
    };
} // namespace app

#endif /* LINKED_HASH_SET_HPP */
