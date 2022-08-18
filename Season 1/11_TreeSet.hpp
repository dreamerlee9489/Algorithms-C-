#ifndef TREE_SET_HPP
#define TREE_SET_HPP

#include "./10_RBTree.hpp"
#include "./11_ISet.hpp"

namespace app {
/**
 * @brief 红黑树集合
 * @date 2022-04-17
 * @tparam T
 */
    template<typename K>
    class TreeSet : public ISet<K> {
        using TraverseFunc = bool (*)(shared_ptr<K> data);
        RBTree<K> *_tree = nullptr;

    public:
        TreeSet(typename ISet<K>::Comparator comparator = nullptr) {
            _tree = new RBTree<K>(comparator);
        }

        ~TreeSet() { delete _tree; }

        size_t size() override { return _tree->size(); }

        bool is_empty() override { return _tree->is_empty(); }

        bool contains(shared_ptr<K> data) override { return _tree->contains(data); }

        void add(shared_ptr<K> data) override { _tree->add(data); }

        void remove(shared_ptr<K> data) override { _tree->remove(data); }

        void traverse(TraverseFunc func = nullptr) {
            _tree->traverse(RBTree<K>::TraverseOrder::In, func);
        }

        void clear() override { _tree->clear(); }
    };
} // namespace app

#endif /* TREE_SET_HPP */
