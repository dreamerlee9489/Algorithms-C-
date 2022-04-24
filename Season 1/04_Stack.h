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
    friend STD_ ostream &operator<<(STD_ ostream &os, const Stack<T> &stack) { return os << *stack._list; }
    ArrayList<T> *_list = nullptr;

public:
    Stack<T> &operator=(const Stack<T> &stack);
    Stack<T> &operator=(Stack<T> &&stack) noexcept;
    Stack() { _list = new ArrayList<T>(); }
    Stack(const Stack<T> &stack) { *this = stack; }
    Stack(Stack<T> &&stack) noexcept { *this = STD_ move(stack); }
    ~Stack() { delete _list; }
    size_t size() const { return _list->size(); }
    bool is_empty() const { return _list->is_empty(); }
    void push(STD_ shared_ptr<T> data) { _list->add(data); }
    STD_ shared_ptr<T> pop() { return _list->remove(_list->size() - 1); }
    STD_ shared_ptr<T> top() const { return _list->get(_list->size() - 1); }
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
    *_list = STD_ move(*stack._list);
    return *this;
}

#endif /* STACK_H */
