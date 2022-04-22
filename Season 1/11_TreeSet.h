#ifndef TREE_SET_H
#define TREE_SET_H
#include "./11_ISet.h"
#include "./10_RBtree.h"
/**
 * @brief 红黑树集合
 * @date 2022-04-17
 * @tparam T
 */
template <typename K>
class TreeSet : public ISet<K>
{
    using TraverseFunc = bool (*)(std::shared_ptr<K> data);
    RBTree<K> *tree = nullptr;

public:
    TreeSet(typename ISet<K>::Comparator comparator = nullptr) { tree = new RBTree<K>(comparator); }
    ~TreeSet() { delete tree; }
    size_t size() override { return tree->size(); }
    bool is_empty() override { return tree->is_empty(); }
    bool contains(std::shared_ptr<K> data) override { return tree->contains(data); }
    void add(std::shared_ptr<K> data) override { tree->add(data); }
    void remove(std::shared_ptr<K> data) override { tree->remove(data); }
    void traverse(TraverseFunc func = nullptr) { tree->traverse(RBTree<K>::TraverseOrder::In, func); }
    void clear() override { tree->clear(); }
};

#endif /* TREE_SET_H */
