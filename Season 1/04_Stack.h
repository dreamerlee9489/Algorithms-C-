#include "02_ArrayList.h"

template <typename T>
class Stack
{
private:
    ArrayList<T>* _list;

public:
    Stack();
    ~Stack();
    size_t size() { return _list->size(); }
    bool is_empty() { return _list->is_empty(); }
    std::shared_ptr<T> push(std::shared_ptr<T> data);
    std::shared_ptr<T> pop();
    std::shared_ptr<T> peek();
};

template <typename T>
Stack<T>::Stack()
{
    _list = new ArrayList<T>();
}

template <typename T>
Stack<T>::~Stack()
{
    delete _list;
}

template <typename T>
std::shared_ptr<T> Stack<T>::push(std::shared_ptr<T> data)
{
    return _list->add(data);
}

template <typename T>
std::shared_ptr<T> Stack<T>::pop()
{
    return _list->remove(_list->size() - 1);
}

template <typename T>
std::shared_ptr<T> Stack<T>::peek()
{
    return _list->get(_list->size());
}