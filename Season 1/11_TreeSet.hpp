#ifndef TREE_SET_HPP
#define TREE_SET_HPP

#include "./11_ISet.hpp"
#include "./10_RBtree.hpp"

namespace app {
    /**
     * @brief 红黑树集合
     * @date 2022-04-17
     * @tparam T
     */
    template<typename K>
    class TreeSet : public ISet<K> {
        using TraverseFunc = bool (*)(shared_ptr<K> data);
        RBTree<K> *mTree = nullptr;

    public:
        TreeSet(typename ISet<K>::Comparator comparator = nullptr) { mTree = new RBTree<K>(comparator); }

        ~TreeSet() { delete mTree; }

        size_t size() override { return mTree->size(); }

        bool is_empty() override { return mTree->is_empty(); }

        bool contains(shared_ptr<K> data) override { return mTree->contains(data); }

        void add(shared_ptr<K> data) override { mTree->add(data); }

        void remove(shared_ptr<K> data) override { mTree->remove(data); }

        void traverse(TraverseFunc func = nullptr) { mTree->traverse(RBTree<K>::TraverseOrder::In, func); }

        void clear() override { mTree->clear(); }
    };
} // namespace app

#endif /* TREE_SET_HPP */
