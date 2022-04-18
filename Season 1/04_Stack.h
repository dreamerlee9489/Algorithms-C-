#ifndef STACK_H
#define STACK_H
#include "./02_ArrayList.h"
/**
 * @brief 栈
 * @date 2022-04-05
 * @tparam T
 */
template <typename T>
class Stack
{
    friend std::ostream &operator<<(std::ostream &os, const Stack<T> &stack) { return os << *stack._list; }
    ArrayList<T> *_list = nullptr;

public:
    Stack<T> &operator=(const Stack<T> &stack);
    Stack<T> &operator=(Stack<T> &&stack) noexcept;
    Stack() { _list = new ArrayList<T>(); }
    Stack(const Stack<T> &stack) { *this = stack; }
    Stack(Stack<T> &&stack) noexcept { *this = std::move(stack); }
    ~Stack() { delete _list; }
    size_t size() const { return _list->size(); }
    bool is_empty() const { return _list->is_empty(); }
    void push(std::shared_ptr<T> data) { _list->add(data); }
    std::shared_ptr<T> pop() { return _list->remove(_list->size() - 1); }
    std::shared_ptr<T> top() const { return _list->get(_list->size() - 1); }
    void clear() { _list->clear(); }
};

template <typename T>
inline Stack<T> &Stack<T>::operator=(const Stack<T> &stack)
{
    clear();
    delete _list;
    _list = new ArrayList<T>();
    *_list = *stack._list;
    return *this;
}

template <typename T>
inline Stack<T> &Stack<T>::operator=(Stack<T> &&stack) noexcept
{
    clear();
    delete _list;
    _list = new ArrayList<T>();
    *_list = std::move(*stack._list);
    return *this;
}

#endif /* STACK_H */
