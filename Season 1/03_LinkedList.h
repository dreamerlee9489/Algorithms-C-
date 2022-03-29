#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "./03_IList.h"
// 泛型双向链表
template <typename T>
class LinkedList : public IList<T>
{
private:
    template <typename U>
    struct Node
    {
        std::shared_ptr<T> _data = nullptr;
        Node<U> *_prev = nullptr, *_next = nullptr;
        Node(std::shared_ptr<T> data, Node<U>* prev = nullptr, Node<U>* next = nullptr);
        ~Node();
        std::shared_ptr<T> disconnect();
    };
    Node<T> *get_node(int index);

public:
    Node<T> *head = nullptr, *last = nullptr;
    LinkedList();
    ~LinkedList();
    int index_of(std::shared_ptr<T> element) override;
    std::shared_ptr<T> insert(int index, std::shared_ptr<T> element) override;
    std::shared_ptr<T> remove(int index) override;
    std::shared_ptr<T> get(int index) override;
    std::shared_ptr<T> set(int index, std::shared_ptr<T> element) override;
    void clear() override;
};

#endif