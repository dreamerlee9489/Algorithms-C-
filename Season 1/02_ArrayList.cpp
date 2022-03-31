#include "./02_ArrayList.h"
#include "./Person.h"

template <typename T>
ArrayList<T> &ArrayList<T>::operator=(const ArrayList<T> &list)
{
    for (size_t i = 0; i < list._size; i++)
        insert(i, list.get(i));
    return *this;
}

template <typename T>
ArrayList<T> &ArrayList<T>::operator=(ArrayList<T> &&list) noexcept
{
    clear();
    this->_size = list._size;
    _array = list._array;
    _capacity = list._capacity;
    list._size = 0;
    return *this;
}

template <typename T>
ArrayList<T>::ArrayList()
{
    this->_size = 0;
    _capacity = DEFAULT_CAPACITY;
    _array = new std::shared_ptr<T>[_capacity];
}

template <typename T>
ArrayList<T>::ArrayList(const ArrayList<T> &list)
{
    this->_size = 0;
    _capacity = DEFAULT_CAPACITY;
    _array = new std::shared_ptr<T>[_capacity];
    *this = list;
}

template <typename T>
ArrayList<T>::ArrayList(ArrayList<T> &&list) noexcept
{
    this->_size = list._size;
    _capacity = list._capacity;
    *this = std::move(list);
}

template <typename T>
ArrayList<T>::~ArrayList()
{
    if(this->_size > 0)
        clear();
    _capacity = 0;
}

template <typename T>
int ArrayList<T>::index_of(std::shared_ptr<T> element)
{
    for (size_t i = 0; i < this->_size; ++i)
        if (*_array[i] == *element)
            return i;
    return -1;
}

template <typename T>
std::shared_ptr<T> ArrayList<T>::insert(int index, std::shared_ptr<T> element)
{
    this->check_range(index, true);
    if (this->_size >= _capacity)
        expand_capacity();
    for (size_t i = this->_size; i > index; --i)
        _array[i] = _array[i - 1];
    _array[index] = element;
    this->_size++;
    return element;
}

template <typename T>
std::shared_ptr<T> ArrayList<T>::remove(int index)
{
    this->check_range(index);
    auto old = _array[index];
    for (size_t i = index + 1; i < this->_size; ++i)
        _array[i - 1] = _array[i];
    _array[this->_size--] = nullptr;
    return old;
}

template <typename T>
std::shared_ptr<T> ArrayList<T>::get(int index)
{
    this->check_range(index);
    return _array[index];
}

template <typename T>
std::shared_ptr<T> ArrayList<T>::get(int index) const
{
    this->check_range(index);
    return _array[index];
}

template <typename T>
std::shared_ptr<T> ArrayList<T>::set(int index, std::shared_ptr<T> element)
{
    this->check_range(index);
    _array[index] = element;
    return element;
}

template <typename T>
void ArrayList<T>::clear()
{
    delete[] _array;
    this->_size = 0;
}

template <typename T>
void ArrayList<T>::expand_capacity()
{
    _capacity <<= 1;
    auto temp = new std::shared_ptr<T>[_capacity];
    for (size_t i = 0; i < this->_size; ++i)
        temp[i] = _array[i];
    delete[] _array;
    _array = temp;
}

int main()
{
    auto list = std::make_shared<ArrayList<Person>>();
    std::cout << "----------Test add()----------\n";
    std::cout << "Add: " << *list->add(std::make_shared<Person>(20, "Alice0"));
    std::cout << "Add: " << *list->add(std::make_shared<Person>(21, "Alice1"));
    std::cout << "Add: " << *list->add(std::make_shared<Person>(22, "Alice2"));
    std::cout << "Add: " << *list->add(std::make_shared<Person>(23, "Alice3"));
    std::cout << "Add: " << *list->add(std::make_shared<Person>(24, "Alice4"));
    std::cout << "Add: " << *list->add(std::make_shared<Person>(25, "Alice5"));
    std::cout << "Add: " << *list->add(std::make_shared<Person>(26, "Alice6"));
    std::cout << "Add: " << *list->add(std::make_shared<Person>(27, "Alice7"));
    std::cout << "size=" << list->size() << ", capacity=" << list->capacity() << std::endl;
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
    std::cout << "size=" << list->size() << ", capacity=" << list->capacity() << std::endl;
    for (size_t i = 0; i < list->size(); ++i)
        std::cout << *list->get(i);

    std::cout << "----------Test contains() & index_of()----------\n";
    if (list->contains(std::make_shared<Person>(30, "Bob0")))
        std::cout << "Bob0 at index=" << list->index_of(std::make_shared<Person>(30, "Bob0")) << std::endl;

    std::cout << "----------Test set()----------\n";
    std::cout << "Set: " << *list->set(5, std::make_shared<Person>(25, "Jack"));
    std::cout << "size=" << list->size() << ", capacity=" << list->capacity() << std::endl;
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
    std::cout << "size=" << list->size() << ", capacity=" << list->capacity() << std::endl;
    for (size_t i = 0; i < list->size(); ++i)
        std::cout << *list->get(i);

    std::cout << "----------Test clear()----------\n";
    list->clear();
    std::cout << "size=" << list->size() << ", capacity=" << list->capacity() << std::endl;

    std::cout << "----------Test ArrayList(const ArrayList<T> &)----------\n";
    auto list1 = std::make_shared<ArrayList<Person>>();
    list1->add(std::make_shared<Person>(10, "test0"));
    list1->add(std::make_shared<Person>(11, "test1"));
    list1->add(std::make_shared<Person>(12, "test2"));
    auto list2 = std::make_shared<ArrayList<Person>>(*list1);
    for (size_t i = 0; i < list2->size(); ++i)
        std::cout << *list2->get(i);

    std::cout << "----------Test ArrayList(ArrayList<T> &&)----------\n";
    auto list3 = std::make_shared<ArrayList<Person>>(std::move(*list1));
    for (size_t i = 0; i < list3->size(); ++i)
        std::cout << *list3->get(i);
    std::getchar();
    return 0;
}

/*
2022年3月30日 16:12:20
输出:
----------Test add()----------
Add: 0x25d2120[20, Alice0]
Add: 0x25d21a0[21, Alice1]
Add: 0x25d2220[22, Alice2]
Add: 0x25d22a0[23, Alice3]
Add: 0x25d2320[24, Alice4]
Add: 0x25d23a0[25, Alice5]
Add: 0x25d2420[26, Alice6]
Add: 0x25d24a0[27, Alice7]
size=8, capacity=8
0x25d2120[20, Alice0]
0x25d21a0[21, Alice1]
0x25d2220[22, Alice2]
0x25d22a0[23, Alice3]
0x25d2320[24, Alice4]
0x25d23a0[25, Alice5]
0x25d2420[26, Alice6]
0x25d24a0[27, Alice7]
----------Test insert()----------
Insert: 0x25d2520[30, Bob0]
Insert: delete 0x25d26f0[35, Bob1]
index = 15 out of range for add: [0, 9].
size=9, capacity=16
0x25d2120[20, Alice0]
0x25d21a0[21, Alice1]
0x25d2220[22, Alice2]
0x25d22a0[23, Alice3]
0x25d2320[24, Alice4]
0x25d2520[30, Bob0]
0x25d23a0[25, Alice5]
0x25d2420[26, Alice6]
0x25d24a0[27, Alice7]
----------Test contains() & index_of()----------
delete 0x25d2ca0[30, Bob0]
Bob0 at index=5
delete 0x25d2d20[30, Bob0]
----------Test set()----------
Set: delete 0x25d2520[30, Bob0]
0x25d2da0[25, Jack]
size=9, capacity=16
0x25d2120[20, Alice0]
0x25d21a0[21, Alice1]
0x25d2220[22, Alice2]
0x25d22a0[23, Alice3]
0x25d2320[24, Alice4]
0x25d2da0[25, Jack]
0x25d23a0[25, Alice5]
0x25d2420[26, Alice6]
0x25d24a0[27, Alice7]
----------Test remove()----------
Remove: 0x25d2da0[25, Jack]
delete 0x25d2da0[25, Jack]
Remove: index = -1 out of range: [0, 7].
size=8, capacity=16
0x25d2120[20, Alice0]
0x25d21a0[21, Alice1]
0x25d2220[22, Alice2]
0x25d22a0[23, Alice3]
0x25d2320[24, Alice4]
0x25d23a0[25, Alice5]
0x25d2420[26, Alice6]
0x25d24a0[27, Alice7]
----------Test clear()----------
delete 0x25d24a0[27, Alice7]
delete 0x25d2420[26, Alice6]
delete 0x25d23a0[25, Alice5]
delete 0x25d2320[24, Alice4]
delete 0x25d22a0[23, Alice3]
delete 0x25d2220[22, Alice2]
delete 0x25d21a0[21, Alice1]
delete 0x25d2120[20, Alice0]
size=0, capacity=16
----------Test ArrayList(const ArrayList<T> &)----------
0x1c8080[10, test0]
0x1c7e00[11, test1]
0x1c8280[12, test2]
----------Test ArrayList(ArrayList<T> &&)----------
0x1c8080[10, test0]
0x1c7e00[11, test1]
0x1c8280[12, test2]

delete 0x1c8280[12, test2]
delete 0x1c7e00[11, test1]
delete 0x1c8080[10, test0]
*/