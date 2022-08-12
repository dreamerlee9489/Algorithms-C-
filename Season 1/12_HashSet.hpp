#ifndef HASH_SET_HPP
#define HASH_SET_HPP

#include "./11_ISet.hpp"
#include "./15_HashMap.hpp"

namespace app {
    /**
     * @brief 哈希集合
     * @date 2022-04-21
     * @tparam K
     */
    template<typename K>
    class HashSet : public ISet<K> {
        HashMap<K, bool> *mMap = nullptr;

    public:
        HashSet(typename ISet<K>::Comparator comparator = nullptr) { mMap = new HashMap<K, bool>(comparator); }

        ~HashSet() { delete mMap; }

        size_t size() override { return mMap->size(); }

        bool is_empty() override { return mMap->is_empty(); }

        bool contains(shared_ptr<K> data) override { return mMap->containspKey(data); }

        void add(shared_ptr<K> data) override { mMap->add(data, make_shared<bool>(true)); }

        void remove(shared_ptr<K> data) override { mMap->remove(data); }

        void traverse(typename ISet<K>::TraverseFunc func = nullptr) { mMap->traverse(func); }

        void clear() override { mMap->clear(); }
    };
} // namespace app

#endif /* HASH_SET_HPP */
