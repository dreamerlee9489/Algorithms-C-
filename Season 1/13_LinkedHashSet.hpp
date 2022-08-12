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
        LinkedHashMap<K, bool> *mMap = nullptr;

    public:
        LinkedHashSet(typename ISet<K>::Comparator comparator = nullptr) {
            mMap = new LinkedHashMap<K, bool>(comparator);
        }

        ~LinkedHashSet() { delete mMap; }

        size_t size() override { return mMap->size(); }

        bool is_empty() override { return mMap->is_empty(); }

        bool contains(shared_ptr<K> data) override { return mMap->containspKey(data); }

        void add(shared_ptr<K> data) override { mMap->add(data, make_shared<bool>(true)); }

        void remove(shared_ptr<K> data) override { mMap->remove(data); }

        void traverse(typename ISet<K>::TraverseFunc func = nullptr) { mMap->traverse(func); }

        void clear() override { mMap->clear(); }
    };
} // namespace app

#endif /* LINKED_HASH_SET_HPP */
