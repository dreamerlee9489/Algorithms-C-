#include "03_LinkedList.h"
#include "Person.h"

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
LinkedList<T>::Node<U>::~Node()
{
    _data = nullptr;
    _prev = _next = nullptr;
}

template <typename T>
template <typename U>
std::shared_ptr<T> LinkedList<T>::Node<U>::disconnect()
{
    _prev = _next = nullptr;
    return _data;
}

template <typename T>
LinkedList<T>::LinkedList()
{
    head = last = new Node<T>(nullptr);
    this->_size = 0;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
    Node<T> *p = last;
    while (p != head)
    {
        p = p->_prev;
        delete p->_next;
    }
    delete head;
    this->_size = 0;
    head = last = nullptr;
}

template <typename T>
int LinkedList<T>::index_of(std::shared_ptr<T> element)
{
    Node<T> *p = head;
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
    Node<T> *temp = new Node<T>(element, get_node(index - 1), get_node(index));
    if (this->_size == 0)
    {
        head = temp;
        last = temp;
    }
    else if (index == 0)
    {
        temp->_next = head;
        head->_prev = temp;
        head = temp;
    }
    else if (index == this->_size)
    {
        temp->_prev = last;
        last->_next = temp;
        last = temp;
    }
    else
    {
        Node<T> *p = head;
        for (size_t i = 1; i < index; ++i)
            p = p->_next;
        temp->_next = p->_next;
        p->_next->_prev = temp;
        temp->_prev = p;
        p->_next = temp;
    }
    this->_size++;
    return element;
}

template <typename T>
std::shared_ptr<T> LinkedList<T>::remove(int index)
{
    this->check_range(index);
    Node<T> *p = head;
    if (index == 0)
    {
        head->_next->_prev = nullptr;
        head = head->_next;
    }
    else if (index == this->_size - 1)
    {
        p = last;
        last->_prev->_next = nullptr;
        last = last->_prev;
    }
    else
    {
        for (size_t i = 0; i < index; ++i)
            p = p->_next;
        p->_prev->_next = p->_next;
        p->_next->_prev = p->_prev;
    }
    this->_size--;
    return p->disconnect();
}

template <typename T>
std::shared_ptr<T> LinkedList<T>::get(int index)
{
    this->check_range(index);
    Node<T> *p = head;
    for (size_t i = 0; i < index; ++i)
        p = p->_next;
    return p->_data;
}

template <typename T>
std::shared_ptr<T> LinkedList<T>::set(int index, std::shared_ptr<T> element)
{
    this->check_range(index);
    Node<T> *p = head;
    for (size_t i = 0; i < index; ++i)
        p = p->_next;
    p->_data = element;
    return p->_data;
}

template <typename T>
void LinkedList<T>::clear()
{
    Node<T> *p = last;
    while (p != head)
    {
        p = p->_prev;
        delete p->_next;
    }
    delete head;
    this->_size = 0;
    head = last = nullptr;
}

template <typename T>
LinkedList<T>::Node<T> *LinkedList<T>::get_node(int index)
{
    Node<T> *p = head;
    if(index == -1)
        return head;
    if(index == this->_size)
        return last;
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

/*
2022年3月28日 20:59:21
输出:
----------Test add()----------
Add: 0xfa16f0[20, Alice0]
Add: 0xfa1760[21, Alice1]
Add: 0xfa17d0[22, Alice2]
Add: 0xfa1840[23, Alice3]
Add: 0xfa18b0[24, Alice4]
Add: 0xfa1920[25, Alice5]
Add: 0xfa1990[26, Alice6]
Add: 0xfa1a00[27, Alice7]
size=8
0xfa16f0[20, Alice0]
0xfa1760[21, Alice1]
0xfa17d0[22, Alice2]
0xfa1840[23, Alice3]
0xfa18b0[24, Alice4]
0xfa1920[25, Alice5]
0xfa1990[26, Alice6]
0xfa1a00[27, Alice7]
----------Test insert()----------
Insert: 0xfa1a70[30, Bob0]
Insert: delete 0xfa1ae0[35, Bob1]
index = 15 out of range for add: [0, 9].
size=9
0xfa16f0[20, Alice0]
0xfa1760[21, Alice1]
0xfa17d0[22, Alice2]
0xfa1840[23, Alice3]
0xfa18b0[24, Alice4]
0xfa1a70[30, Bob0]
0xfa1920[25, Alice5]
0xfa1990[26, Alice6]
0xfa1a00[27, Alice7]
----------Test contains() & index_of()----------
delete 0xfa1c00[30, Bob0]
Bob0 at index=5
delete 0xfa1c00[30, Bob0]
----------Test set()----------
Set: delete 0xfa1a70[30, Bob0]
0xfa1c00[25, Jack]
size=9
0xfa16f0[20, Alice0]
0xfa1760[21, Alice1]
0xfa17d0[22, Alice2]
0xfa1840[23, Alice3]
0xfa18b0[24, Alice4]
0xfa1c00[25, Jack]
0xfa1920[25, Alice5]
0xfa1990[26, Alice6]
0xfa1a00[27, Alice7]
----------Test remove()----------
Remove: 0xfa1c00[25, Jack]
Remove: index = -1 out of range: [0, 7].
size=8
0xfa16f0[20, Alice0]
0xfa1760[21, Alice1]
0xfa17d0[22, Alice2]
0xfa1840[23, Alice3]
0xfa18b0[24, Alice4]
0xfa1920[25, Alice5]
0xfa1990[26, Alice6]
0xfa1a00[27, Alice7]
----------Test clear()----------
delete 0xfa1a00[27, Alice7]
delete 0xfa1990[26, Alice6]
delete 0xfa1920[25, Alice5]
delete 0xfa18b0[24, Alice4]
delete 0xfa1840[23, Alice3]
delete 0xfa17d0[22, Alice2]
delete 0xfa1760[21, Alice1]
delete 0xfa16f0[20, Alice0]
size=0
*/