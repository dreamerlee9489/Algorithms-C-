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
std::shared_ptr<T> LinkedList<T>::Node<U>::disconnect()
{
    auto old = _data;
    _data = nullptr;
    _prev = _next = nullptr;
    return old;
}

template <typename T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &list)
{
    for (size_t i = 0; i < list._size; i++)
        insert(i, list.get(i));
    return *this;
}

template <typename T>
LinkedList<T> &LinkedList<T>::operator=(LinkedList<T> &&list) noexcept
{
    clear();
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
    _head->_prev = _head;
    this->_size = 0;
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &list)
{
    _head = new Node<T>(nullptr);
    _head->_prev = _head;
    this->_size = 0;
    *this = list;
}

template <typename T>
LinkedList<T>::LinkedList(LinkedList<T> &&list) noexcept
{
    _head = new Node<T>(nullptr);
    _head->_prev = _head;
    this->_size = 0;
    *this = std::move(list);
}

template <typename T>
LinkedList<T>::~LinkedList()
{
    clear();
    delete _head;
}

template <typename T>
int LinkedList<T>::index_of(std::shared_ptr<T> data)
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
    prev->_next = temp;
    if (next == nullptr)
        _head->_prev = temp;
    else
        next->_prev = temp;
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
        _head->_next = nullptr;
        _head->_prev = _head;
        this->_size = 0;
    }
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

    std::cout << "----------Test LinkedList(const LinkedList<T> &)----------\n";
    auto list1 = std::make_shared<LinkedList<Person>>();
    list1->add(std::make_shared<Person>(10, "test0"));
    list1->add(std::make_shared<Person>(11, "test1"));
    list1->add(std::make_shared<Person>(12, "test2"));
    auto list2 = std::make_shared<LinkedList<Person>>(*list1);
    for (size_t i = 0; i < list2->size(); ++i)
        std::cout << *list2->get(i);

    std::cout << "----------Test LinkedList(LinkedList<T> &&)----------\n";
    auto list3 = std::make_shared<LinkedList<Person>>(std::move(*list1));
    for (size_t i = 0; i < list3->size(); ++i)
        std::cout << *list3->get(i);
    std::getchar();
    return 0;
}

/*
2022年3月30日 15:32:00
输出:
----------Test add()----------
Add: 0x6f6750[20, Alice0]
Add: 0x6f67c0[21, Alice1]
Add: 0x6f6830[22, Alice2]
Add: 0x6f68a0[23, Alice3]
Add: 0x6f6910[24, Alice4]
Add: 0x6f6980[25, Alice5]
Add: 0x6f69f0[26, Alice6]
Add: 0x6f6a60[27, Alice7]
size=8
0x6f6750[20, Alice0]
0x6f67c0[21, Alice1]
0x6f6830[22, Alice2]
0x6f68a0[23, Alice3]
0x6f6910[24, Alice4]
0x6f6980[25, Alice5]
0x6f69f0[26, Alice6]
0x6f6a60[27, Alice7]
----------Test insert()----------
Insert: 0x6f6ad0[30, Bob0]
Insert: delete 0x6f6b40[35, Bob1]
index = 15 out of range for add: [0, 9].
size=9
0x6f6750[20, Alice0]
0x6f67c0[21, Alice1]
0x6f6830[22, Alice2]
0x6f68a0[23, Alice3]
0x6f6910[24, Alice4]
0x6f6ad0[30, Bob0]
0x6f6980[25, Alice5]
0x6f69f0[26, Alice6]
0x6f6a60[27, Alice7]
----------Test contains() & index_of()----------
delete 0x6f6c60[30, Bob0]
Bob0 at index=5
delete 0x6f6c60[30, Bob0]
----------Test set()----------
Set: delete 0x6f6ad0[30, Bob0]
0x6f6c60[25, Jack]
size=9
0x6f6750[20, Alice0]
0x6f67c0[21, Alice1]
0x6f6830[22, Alice2]
0x6f68a0[23, Alice3]
0x6f6910[24, Alice4]
0x6f6c60[25, Jack]
0x6f6980[25, Alice5]
0x6f69f0[26, Alice6]
0x6f6a60[27, Alice7]
----------Test remove()----------
Remove: 0x6f6c60[25, Jack]
delete 0x6f6c60[25, Jack]
Remove: index = -1 out of range: [0, 7].
size=8
0x6f6750[20, Alice0]
0x6f67c0[21, Alice1]
0x6f6830[22, Alice2]
0x6f68a0[23, Alice3]
0x6f6910[24, Alice4]
0x6f6980[25, Alice5]
0x6f69f0[26, Alice6]
0x6f6a60[27, Alice7]
----------Test clear()----------
delete 0x6f6a60[27, Alice7]
delete 0x6f69f0[26, Alice6]
delete 0x6f6980[25, Alice5]
delete 0x6f6910[24, Alice4]
delete 0x6f68a0[23, Alice3]
delete 0x6f6830[22, Alice2]
delete 0x6f67c0[21, Alice1]
delete 0x6f6750[20, Alice0]
size=0
----------Test LinkedList(const LinkedList<T> &)----------
0x6f6cc0[10, test0]
0x6f6b70[11, test1]
0x6f6be0[12, test2]
----------Test LinkedList(LinkedList<T> &&)----------
0x6f6cc0[10, test0]
0x6f6b70[11, test1]
0x6f6be0[12, test2]

delete 0x6f6be0[12, test2]
delete 0x6f6b70[11, test1]
delete 0x6f6cc0[10, test0]
*/