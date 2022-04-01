#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "./03_IList.h"
// 泛型双向循环链表(智能指针版)
template <typename T>
class LinkedList : public IList<T>
{
private:
    template <typename U>
    struct Node
    {
        std::shared_ptr<T> _data = nullptr;
        Node<U> *_prev = nullptr, *_next = nullptr;
        Node<U> &operator=(const Node<U> &node);
        Node<U> &operator=(Node<U> &&node) noexcept;
        Node(std::shared_ptr<T> data, Node<U> *prev = nullptr, Node<U> *next = nullptr);
        Node(const Node<U> &node) { *this = node; }
        Node(Node<U> &&node) noexcept { *this = std::move(node); }
        ~Node() { _data = nullptr; }
        std::shared_ptr<T> disconnect();
    };
    Node<T> *get_node(int index);

public:
    Node<T> *_head = nullptr;
    LinkedList<T> &operator=(const LinkedList<T> &list);
    LinkedList<T> &operator=(LinkedList<T> &&list) noexcept;
    LinkedList();
    ~LinkedList();
    LinkedList(const LinkedList<T> &list);
    LinkedList(LinkedList<T> &&list) noexcept;
    int index_of(std::shared_ptr<T> data) override;
    std::shared_ptr<T> insert(int index, std::shared_ptr<T> data) override;
    std::shared_ptr<T> remove(int index) override;
    std::shared_ptr<T> get(int index) override;
    std::shared_ptr<T> get(int index) const override;
    std::shared_ptr<T> set(int index, std::shared_ptr<T> data) override;
    void clear() override;
};

#endif