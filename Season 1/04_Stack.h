#ifndef STACK_H
#define STACK_H
#include "02_ArrayList.h"

template <typename T>
class Stack
{
private:
    ArrayList<T> *_list;

public:
    Stack() { _list = new ArrayList<T>(); }
    ~Stack() { delete _list; }
    size_t size() { return _list->size(); }
    bool is_empty() { return _list->is_empty(); }
    std::shared_ptr<T> push(std::shared_ptr<T> data) { return _list->add(data); }
    std::shared_ptr<T> pop() { return _list->remove(_list->size() - 1); }
    std::shared_ptr<T> peek() { return _list->get(_list->size() - 1); }
    void clear() { _list->clear(); }
};

#endif
