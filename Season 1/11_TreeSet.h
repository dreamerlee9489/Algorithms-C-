/**
 * @file 11_TreeSet.h
 * @author dreamerlee9489@outlook.com
 * @brief 基于红黑树的集合
 * @version 0.1
 * @date 2022-04-17
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef SET_H
#define SET_H
#include "./11_ISet.h"
#include "./10_RBtree.h"

template <typename T>
class TreeSet : public ISet<T>
{
    RBTree<T> *tree = nullptr;

public:
    TreeSet(typename ISet<T>::Comparator comparator = nullptr) { tree = new RBTree<T>(comparator); }
    ~TreeSet() { delete tree; }
    size_t size() override { return tree->size(); }
    bool is_empty() override { return tree->is_empty(); }
    bool contains(std::shared_ptr<T> data) override { return tree->contains(data); }
    void add(std::shared_ptr<T> data) override { tree->add(data); }
    void remove(std::shared_ptr<T> data) override { tree->remove(data); }
    void traverse(typename ISet<T>::TraverseFunc func = nullptr) override { tree->traverse(RBTree<T>::TraverseOrder::In, func); }
    void clear() override { tree->clear(); }
};

#endif /* SET_H */
