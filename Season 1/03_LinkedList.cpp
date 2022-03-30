#include "./03_LinkedList.h"
#include "./Person.h"

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
LinkedList<T>::Node<U>::~Node()
{
    _data = nullptr;
    _prev = _next = nullptr;
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

template <typename T>
LinkedList<T>::LinkedList()
{
    _head = new Node<T>(nullptr);
    this->_size = 0;
}

template <typename T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList &list)
{
    return *this;
}

template <typename T>
LinkedList<T> &LinkedList<T>::operator=(LinkedList &&list) noexcept
{
    return *this;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
    if (this->_size > 0)
        clear();
    delete _head;
}

template <typename T>
int LinkedList<T>::index_of(std::shared_ptr<T> element)
{
    Node<T> *p = _head;
    for (size_t i = 0; i < this->_size; ++i)
    {
        p = p->_next;
        if (*p->_data == *element)
            return i;
    }
    return -1;
}

template <typename T>
std::shared_ptr<T> LinkedList<T>::insert(int index, std::shared_ptr<T> element)
{
    this->check_range(index, true);
    Node<T> *prev = get_node(index - 1);
    Node<T> *next = prev->_next;
    Node<T> *temp = new Node<T>(element, prev, next);
    prev->_next = temp;
    if (next == nullptr)
        _head->_prev = temp;
    else
        next->_prev = temp;
    this->_size++;
    return element;
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
        _head->_prev->_next = nullptr;
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
std::shared_ptr<T> LinkedList<T>::get(int index)
{
    this->check_range(index);
    Node<T> *p = _head->_next;
    for (size_t i = 0; i < index; ++i)
        p = p->_next;
    return p->_data;
}

template <typename T>
std::shared_ptr<T> LinkedList<T>::set(int index, std::shared_ptr<T> element)
{
    this->check_range(index);
    Node<T> *p = _head->_next;
    for (size_t i = 0; i < index; ++i)
        p = p->_next;
    p->_data = element;
    return p->_data;
}

template <typename T>
void LinkedList<T>::clear()
{
    Node<T> *p = _head->_prev;
    while (p != _head)
    {
        p = p->_prev;
        delete p->_next;
    }
    this->_size = 0;
}

template <typename T>
LinkedList<T>::Node<T> *LinkedList<T>::get_node(int index)
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

int main()
{
    auto list = std::make_shared<LinkedList<Person>>();
    std::cout << "----------Test add()----------\n";
    std::cout << "Add: " << *list->add(std::make_shared<Person>(20, "Alice0"));
    std::cout << "Add: " << *list->add(std::make_shared<Person>(21, "Alice1"));
    std::cout << "Add: " << *list->add(std::make_shared<Person>(22, "Alice2"));
    std::cout << "Add: " << *list->add(std::make_shared<Person>(23, "Alice3"));
    std::cout << "Add: " << *list->add(std::make_shared<Person>(24, "Alice4"));
    std::cout << "Add: " << *list->add(std::make_shared<Person>(25, "Alice5"));
    std::cout << "Add: " << *list->add(std::make_shared<Person>(26, "Alice6"));
    std::cout << "Add: " << *list->add(std::make_shared<Person>(27, "Alice7"));
    std::cout << "size=" << list->size() << std::endl;
    for (size_t i = 0; i < list->size(); ++i)
        std::cout << *list->get(i);

    std::cout << "----------Test insert()----------\n";
    try
    {
        std::cout << "Insert: " << *list->insert(5, std::make_shared<Person>(30, "Bob0"));
        std::cout << "Insert: " << *list->insert(15, std::make_shared<Person>(35, "Bob1"));
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    std::cout << "size=" << list->size() << std::endl;
    for (size_t i = 0; i < list->size(); ++i)
        std::cout << *list->get(i);

    std::cout << "----------Test contains() & index_of()----------\n";
    if (list->contains(std::make_shared<Person>(30, "Bob0")))
        std::cout << "Bob0 at index=" << list->index_of(std::make_shared<Person>(30, "Bob0")) << std::endl;

    std::cout << "----------Test set()----------\n";
    std::cout << "Set: " << *list->set(5, std::make_shared<Person>(25, "Jack"));
    std::cout << "size=" << list->size() << std::endl;
    for (size_t i = 0; i < list->size(); ++i)
        std::cout << *list->get(i);

    std::cout << "----------Test remove()----------\n";
    try
    {
        std::cout << "Remove: " << *list->remove(5);
        std::cout << "Remove: " << *list->remove(-1);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    std::cout << "size=" << list->size() << std::endl;
    for (size_t i = 0; i < list->size(); ++i)
        std::cout << *list->get(i);

    std::cout << "----------Test clear()----------\n";
    list->clear();
    std::cout << "size=" << list->size() << std::endl;
    std::getchar();
    return 0;
}