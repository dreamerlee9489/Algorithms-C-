#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "./03_IList.h"
// 泛型双向循环链表
template <typename T>
class LinkedList : public IList<T>
{
    template <typename U>
    friend inline std::ostream &operator<<(std::ostream &os, const LinkedList<U> &list);

private:
    template <typename U>
    struct Node
    {
        std::shared_ptr<T> _data = nullptr;
        Node<U> *_prev = nullptr, *_next = nullptr;
        inline Node<U> &operator=(const Node<U> &node);
        inline Node<U> &operator=(Node<U> &&node) noexcept;
        inline Node(std::shared_ptr<T> data, Node<U> *prev = nullptr, Node<U> *next = nullptr);
        ~Node() { _data = nullptr; }
        Node(const Node<U> &node) { *this = node; }
        Node(Node<U> &&node) noexcept { *this = std::move(node); }
        std::shared_ptr<T> disconnect();
    };
    Node<T> *get_node(int index) const;

public:
    Node<T> *_head = nullptr;
    inline LinkedList<T> &operator=(const LinkedList<T> &list);
    inline LinkedList<T> &operator=(LinkedList<T> &&list) noexcept;
    inline LinkedList();
    inline ~LinkedList();
    LinkedList(const LinkedList<T> &list) { *this = list; }
    LinkedList(LinkedList<T> &&list) noexcept { *this = std::move(list); }
    int index_of(std::shared_ptr<T> data) const override;
    std::shared_ptr<T> insert(int index, std::shared_ptr<T> data) override;
    std::shared_ptr<T> remove(int index) override;
    std::shared_ptr<T> get(int index) const override;
    std::shared_ptr<T> set(int index, std::shared_ptr<T> data) override;
    void clear() override;
};

template <typename T>
template <typename U>
LinkedList<T>::Node<U>::Node(std::shared_ptr<T> data, Node<U> *prev, Node<U> *next)
{
    _data = data;
    _prev = prev;
    _next = next;
}

template <typename T>
template <typename U>
LinkedList<T>::Node<U> &LinkedList<T>::Node<U>::operator=(const Node<U> &node)
{
    _data = node._data;
    _prev = node._prev;
    _next = node._next;
    return *this;
}

template <typename T>
template <typename U>
LinkedList<T>::Node<U> &LinkedList<T>::Node<U>::operator=(Node<U> &&node) noexcept
{
    _data = std::move((std::shared_ptr<T>)node._data);
    _prev = std::move((Node<U> *)node._prev);
    _next = std::move((Node<U> *)node._next);
    return *this;
}

template <typename T>
template <typename U>
std::shared_ptr<T> LinkedList<T>::Node<U>::disconnect()
{
    auto old = _data;
    _data = nullptr;
    _prev = _next = nullptr;
    return old;
}

template <typename U>
std::ostream &operator<<(std::ostream &os, const LinkedList<U> &list)
{
    for (size_t i = 0; i < list._size; ++i)
        if (list.get(i) != nullptr)
            os << *list.get(i) << "\n";
    return os;
}

template <typename T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &list)
{
    clear();
    _head = new Node<T>(nullptr);
    _head->_prev = _head->_next = _head;
    this->_size = 0;
    for (size_t i = 0; i < list._size; ++i)
        insert(i, list.get(i));
    return *this;
}

template <typename T>
LinkedList<T> &LinkedList<T>::operator=(LinkedList<T> &&list) noexcept
{
    clear();
    _head = new Node<T>(nullptr);
    _head->_prev = _head->_next = _head;
    this->_size = 0;
    if (list._size > 0)
    {
        this->_size = list._size;
        _head->_next = list._head->_next;
        _head->_prev = list._head->_prev;
        list._head->_next->_prev = _head;
        list._size = 0;
    }
    return *this;
}

template <typename T>
LinkedList<T>::LinkedList()
{
    _head = new Node<T>(nullptr);
    _head->_prev = _head->_next = _head;
    this->_size = 0;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
    clear();
    delete _head;
}

template <typename T>
int LinkedList<T>::index_of(std::shared_ptr<T> data) const
{
    Node<T> *p = _head;
    for (size_t i = 0; i < this->_size; ++i)
    {
        p = p->_next;
        if (*p->_data == *data)
            return i;
    }
    return -1;
}

template <typename T>
std::shared_ptr<T> LinkedList<T>::insert(int index, std::shared_ptr<T> data)
{
    this->check_range(index, true);
    Node<T> *prev = get_node(index - 1);
    Node<T> *next = prev->_next;
    Node<T> *temp = new Node<T>(data, prev, next);
    if (next != _head)
    {
        prev->_next = temp;
        next->_prev = temp;
    }
    else
    {
        prev->_next = temp;
        temp->_next = _head;
        _head->_prev = temp;
    }
    this->_size++;
    return data;
}

template <typename T>
std::shared_ptr<T> LinkedList<T>::remove(int index)
{
    this->check_range(index);
    Node<T> *old = _head->_next;
    for (size_t i = 0; i < index; ++i)
        old = old->_next;
    if (index == 0)
    {
        _head->_next = _head->_next->_next;
        _head->_next->_prev = _head;
    }
    else if (index == this->_size - 1)
    {
        _head->_prev = _head->_prev->_prev;
        _head->_prev->_next = _head;
    }
    else
    {
        old->_prev->_next = old->_next;
        old->_next->_prev = old->_prev;
    }
    this->_size--;
    return old->disconnect();
}

template <typename T>
std::shared_ptr<T> LinkedList<T>::get(int index) const
{
    this->check_range(index);
    Node<T> *p = _head->_next;
    for (size_t i = 0; i < index; ++i)
        p = p->_next;
    return p->_data;
}

template <typename T>
std::shared_ptr<T> LinkedList<T>::set(int index, std::shared_ptr<T> data)
{
    this->check_range(index);
    Node<T> *p = _head->_next;
    for (size_t i = 0; i < index; ++i)
        p = p->_next;
    p->_data = data;
    return p->_data;
}

template <typename T>
void LinkedList<T>::clear()
{
    if (this->_size > 0)
    {
        Node<T> *p = _head->_prev;
        while (p != _head)
        {
            p = p->_prev;
            delete p->_next;
        }
        _head->_next = _head;
        _head->_prev = _head;
        this->_size = 0;
    }
}

template <typename T>
LinkedList<T>::Node<T> *LinkedList<T>::get_node(int index) const
{
    if (index == -1)
        return _head;
    if (index == this->_size - 1)
        return _head->_prev;
    Node<T> *p = _head;
    for (size_t i = 0; i < index; ++i)
        p = p->_next;
    return p->_next;
}

#endif