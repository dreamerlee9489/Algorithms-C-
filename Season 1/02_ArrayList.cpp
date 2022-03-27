#include "./02_ArrayList.h"

template <typename T>
ArrayList<T>::ArrayList()
{
    IList<T>::_size = 0;
    _capacity = DEFAULT_CAPACITY;
    array = new std::shared_ptr<T>[_capacity];
}

template <typename T>
ArrayList<T>::~ArrayList()
{
    IList<T>::_size = 0;
    _capacity = 0;
    delete[] array;
    array = nullptr;
}

template <typename T>
void ArrayList<T>::insert(size_t index, std::shared_ptr<T> element)
{
    IList<T>::check_range_add(index);
    if (IList<T>::_size >= _capacity)
        expand_capacity();
    for (size_t i = IList<T>::_size; i > index; --i)
        array[i] = array[i - 1];
    array[index] = element;
    IList<T>::_size++;
}

template <typename T>
size_t ArrayList<T>::index_of(std::shared_ptr<T> element)
{
    for (size_t i = 0; i < IList<T>::_size; ++i)
        if (*array[i] == *element)
            return i;
    return -1;
}

template <typename T>
std::shared_ptr<T> ArrayList<T>::remove(size_t index)
{
    IList<T>::check_range(index);
    auto old = array[index];
    for (size_t i = index + 1; i < IList<T>::_size; ++i)
        array[i - 1] = array[i];
    array[IList<T>::_size--] = nullptr;
    return old;
}

template <typename T>
std::shared_ptr<T> ArrayList<T>::get(size_t index)
{
    IList<T>::check_range(index);
    return array[index];
}

template <typename T>
void ArrayList<T>::set(size_t index, std::shared_ptr<T> element)
{
    IList<T>::check_range(index);
    array[index] = element;
}

template <typename T>
void ArrayList<T>::clear()
{
    for (size_t i = 0; i < _capacity; ++i)
        array[i] = nullptr;
    IList<T>::_size = 0;
}

template <typename T>
void ArrayList<T>::expand_capacity()
{
    _capacity = _capacity << 1;
    auto temp = new std::shared_ptr<T>[_capacity];
    for (size_t i = 0; i < IList<T>::_size; ++i)
        temp[i] = array[i];
    delete[] array;
    array = temp;
}

int main()
{
    auto list = std::make_shared<ArrayList<Person>>();
    std::cout << "----------Test add()----------\n";
    list->add(std::make_shared<Person>(20, "Alice0"));
    list->add(std::make_shared<Person>(21, "Alice1"));
    list->add(std::make_shared<Person>(22, "Alice2"));
    list->add(std::make_shared<Person>(23, "Alice3"));
    list->add(std::make_shared<Person>(24, "Alice4"));
    list->add(std::make_shared<Person>(25, "Alice5"));
    list->add(std::make_shared<Person>(26, "Alice6"));
    list->add(std::make_shared<Person>(27, "Alice7"));
    std::cout << "size=" << list->size() << ", capacity=" << list->capacity() << std::endl;
    for (size_t i = 0; i < list->size(); ++i)
        std::cout << *list->get(i);

    std::cout << "----------Test insert()----------\n";
    list->insert(5, std::make_shared<Person>(30, "Bob0"));
    std::cout << "size=" << list->size() << ", capacity=" << list->capacity() << std::endl;
    for (size_t i = 0; i < list->size(); ++i)
        std::cout << *list->get(i);

    std::cout << "----------Test contains() & index_of()----------\n";
    if (list->contains(std::make_shared<Person>(30, "Bob0")))
        std::cout << "index=" << list->index_of(std::make_shared<Person>(30, "Bob0")) << std::endl;

    std::cout << "----------Test set()----------\n";
    list->set(5, std::make_shared<Person>(15, "Jack"));
    std::cout << "size=" << list->size() << ", capacity=" << list->capacity() << std::endl;
    for (size_t i = 0; i < list->size(); ++i)
        std::cout << *list->get(i);

    std::cout << "----------Test remove()----------\n";
    std::cout << "Remove: " << *list->remove(5);
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
2022年3月27日 23:53:01
输出:
----------Test add()----------
size=8, capacity=8
0xde1790[20, Alice0]
0xde17d0[21, Alice1]
0xde1810[22, Alice2]
0xde1850[23, Alice3]
0xde1890[24, Alice4]
0xde18d0[25, Alice5]
0xde1910[26, Alice6]
0xde1950[27, Alice7]
----------Test insert()----------
size=9, capacity=16
0xde1790[20, Alice0]
0xde17d0[21, Alice1]
0xde1810[22, Alice2]
0xde1850[23, Alice3]
0xde1890[24, Alice4]
0xde1990[30, Bob0]
0xde18d0[25, Alice5]
0xde1910[26, Alice6]
0xde1950[27, Alice7]
----------Test contains() & index_of()----------
delete 0xde1700[30, Bob0]
index=5
delete 0xde1700[30, Bob0]
----------Test set()----------
delete 0xde1990[30, Bob0]
size=9, capacity=16
0xde1790[20, Alice0]
0xde17d0[21, Alice1]
0xde1810[22, Alice2]
0xde1850[23, Alice3]
0xde1890[24, Alice4]
0xde1700[15, Jack]
0xde18d0[25, Alice5]
0xde1910[26, Alice6]
0xde1950[27, Alice7]
----------Test remove()----------
Remove: 0xde1700[15, Jack]
delete 0xde1700[15, Jack]
size=8, capacity=16
0xde1790[20, Alice0]
0xde17d0[21, Alice1]
0xde1810[22, Alice2]
0xde1850[23, Alice3]
0xde1890[24, Alice4]
0xde18d0[25, Alice5]
0xde1910[26, Alice6]
0xde1950[27, Alice7]
----------Test clear()----------
delete 0xde1790[20, Alice0]
delete 0xde17d0[21, Alice1]
delete 0xde1810[22, Alice2]
delete 0xde1850[23, Alice3]
delete 0xde1890[24, Alice4]
delete 0xde18d0[25, Alice5]
delete 0xde1910[26, Alice6]
delete 0xde1950[27, Alice7]
size=0, capacity=16
*/