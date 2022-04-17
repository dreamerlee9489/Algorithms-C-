#ifndef TREE_SET_H
#define TREE_SET_H
#include "./11_ISet.h"
#include "./10_RBtree.h"
// 集合
template <typename T>
class Set : public ISet<T>
{
    RBTree<T> *tree;

public:
    Set() { tree = new RBTree<T>(); }
    ~Set() { delete tree; }
    size_t size() override { return tree->size(); }
    bool is_empty() override { return tree->is_empty(); }
    bool contains(std::shared_ptr<T> data) override { return tree->contains(data); }
    void add(std::shared_ptr<T> data) override { tree->add(data); }
    void remove(std::shared_ptr<T> data) override { tree->remove(data); }
    void traverse(typename ISet<T>::traverse_func func = nullptr) override { tree->traverse(RBTree<T>::TraverseOrder::In, func); }
    void clear() override { tree->clear(); }
};

#endif /* TREE_SET_H */
