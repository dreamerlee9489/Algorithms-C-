#include "02_ArrayList.h"
#include "Person.h"

template <typename T>
ArrayList<T>::ArrayList()
{
    this->_size = 0;
    _capacity = DEFAULT_CAPACITY;
    array = new std::shared_ptr<T>[_capacity];
}

template <typename T>
ArrayList<T>::~ArrayList()
{
    this->_size = 0;
    _capacity = 0;
    delete[] array;
    array = nullptr;
}

template <typename T>
int ArrayList<T>::index_of(std::shared_ptr<T> element)
{
    for (size_t i = 0; i < this->_size; ++i)
        if (*array[i] == *element)
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
        array[i] = array[i - 1];
    array[index] = element;
    this->_size++;
    return element;
}

template <typename T>
std::shared_ptr<T> ArrayList<T>::remove(int index)
{
    this->check_range(index);
    auto old = array[index];
    for (size_t i = index + 1; i < this->_size; ++i)
        array[i - 1] = array[i];
    array[this->_size--] = nullptr;
    return old;
}

template <typename T>
std::shared_ptr<T> ArrayList<T>::get(int index)
{
    this->check_range(index);
    return array[index];
}

template <typename T>
std::shared_ptr<T> ArrayList<T>::set(int index, std::shared_ptr<T> element)
{
    this->check_range(index);
    array[index] = element;
    return element;
}

template <typename T>
void ArrayList<T>::clear()
{
    for (size_t i = 0; i < _capacity; ++i)
        array[i] = nullptr;
    this->_size = 0;
}

template <typename T>
void ArrayList<T>::expand_capacity()
{
    _capacity <<= 1;
    auto temp = new std::shared_ptr<T>[_capacity];
    for (size_t i = 0; i < this->_size; ++i)
        temp[i] = array[i];
    delete[] array;
    array = temp;
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
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    std::cout << "size=" << list->size() << ", capacity=" << list->capacity() << std::endl;
    for (size_t i = 0; i < list->size(); ++i)
        std::cout << *list->get(i);

    std::cout << "----------Test clear()----------\n";
    list->clear();
    std::cout << "size=" << list->size() << ", capacity=" << list->capacity() << std::endl;
    std::getchar();
    return 0;
}

/*
2022年3月28日 08:44:51
输出:
----------Test add()----------
Add: 0xee1790[20, Alice0]
Add: 0xee17d0[21, Alice1]
Add: 0xee1810[22, Alice2]
Add: 0xee1850[23, Alice3]
Add: 0xee1890[24, Alice4]
Add: 0xee18d0[25, Alice5]
Add: 0xee1910[26, Alice6]
Add: 0xee1950[27, Alice7]
size=8, capacity=8
0xee1790[20, Alice0]
0xee17d0[21, Alice1]
0xee1810[22, Alice2]
0xee1850[23, Alice3]
0xee1890[24, Alice4]
0xee18d0[25, Alice5]
0xee1910[26, Alice6]
0xee1950[27, Alice7]
----------Test insert()----------
Insert: 0xee1990[30, Bob0]
Insert: delete 0xee1700[35, Bob1]
index = 15 out of range for add: [0, 9].
size=9, capacity=16
0xee1790[20, Alice0]
0xee17d0[21, Alice1]
0xee1810[22, Alice2]
0xee1850[23, Alice3]
0xee1890[24, Alice4]
0xee1990[30, Bob0]
0xee18d0[25, Alice5]
0xee1910[26, Alice6]
0xee1950[27, Alice7]
----------Test contains() & index_of()----------
delete 0xee1700[30, Bob0]
Bob0 at index=5
delete 0xee1700[30, Bob0]
----------Test set()----------
Set: delete 0xee1990[30, Bob0]
0xee1700[25, Jack]
size=9, capacity=16
0xee1790[20, Alice0]
0xee17d0[21, Alice1]
0xee1810[22, Alice2]
0xee1850[23, Alice3]
0xee1890[24, Alice4]
0xee1700[25, Jack]
0xee18d0[25, Alice5]
0xee1910[26, Alice6]
0xee1950[27, Alice7]
----------Test remove()----------
Remove: 0xee1700[25, Jack]
delete 0xee1700[25, Jack]
Remove: index = -1 out of range: [0, 7].
size=8, capacity=16
0xee1790[20, Alice0]
0xee17d0[21, Alice1]
0xee1810[22, Alice2]
0xee1850[23, Alice3]
0xee1890[24, Alice4]
0xee18d0[25, Alice5]
0xee1910[26, Alice6]
0xee1950[27, Alice7]
----------Test clear()----------
delete 0xee1790[20, Alice0]
delete 0xee17d0[21, Alice1]
delete 0xee1810[22, Alice2]
delete 0xee1850[23, Alice3]
delete 0xee1890[24, Alice4]
delete 0xee18d0[25, Alice5]
delete 0xee1910[26, Alice6]
delete 0xee1950[27, Alice7]
size=0, capacity=16
*/