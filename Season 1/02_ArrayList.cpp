#include "./02_ArrayList.h"

template <typename T>
ArrayList<T>::ArrayList()
{
    size = 0;
    capacity = DEFAULT_CAPACITY;
    array = new std::shared_ptr<T>[capacity];
}

template <typename T>
ArrayList<T>::~ArrayList()
{
    size = 0;
    capacity = 0;
    delete[] array;
    array = nullptr;
}

template <typename T>
void ArrayList<T>::add(std::shared_ptr<T> element)
{
    if (size >= capacity)
        expand_capacity();
    array[size++] = element;
}

template <typename T>
void ArrayList<T>::insert(int index, std::shared_ptr<T> element)
{
    if (index < 0 || index > size)
    {
        throw std::out_of_range("Index out of range: [0, " + std::to_string(size) + "].");
        return;
    }
    if (size >= capacity)
        expand_capacity();
    for (size_t i = size - 1; i >= index; --i)
        array[i + 1] = array[i];
    array[index] = element;
    size++;
}

template <typename T>
std::shared_ptr<T> ArrayList<T>::remove(int index)
{
    if (index < 0 || index >= size)
    {
        throw std::out_of_range("Index out of range: [0, " + std::to_string(size - 1) + "].");
        return nullptr;
    }
    auto old = array[index];
    for (size_t i = index + 1; i < size; ++i)
        array[i - 1] = array[i];
    array[size] = nullptr;
    size--;
    return old;
}

template <typename T>
size_t ArrayList<T>::index_of(std::shared_ptr<T> element)
{
    for (size_t i = 0; i < size; ++i)
        if (*array[i] == *element)
            return i;
    return -1;
}

template <typename T>
std::shared_ptr<T> ArrayList<T>::get(int index)
{
    if (index < 0 || index >= size)
    {
        throw std::out_of_range("Index out of range: [0, " + std::to_string(size - 1) + "].");
        return nullptr;
    }
    return array[index];
}

template <typename T>
void ArrayList<T>::set(int index, std::shared_ptr<T> element)
{
    if (index < 0 || index >= size)
    {
        throw std::out_of_range("Index out of range: [0, " + std::to_string(size - 1) + "].");
        return;
    }
    array[index] = element;
}

template <typename T>
bool ArrayList<T>::contains(std::shared_ptr<T> element)
{
    for (size_t i = 0; i < size; ++i)
        if (*array[i] == *element)
            return true;
    return false;
}

template <typename T>
void ArrayList<T>::clear()
{
    for (size_t i = 0; i < size; ++i)
        array[i] = nullptr;
    size = 0;
}

template <typename T>
void ArrayList<T>::expand_capacity()
{
    capacity = capacity << 1;
    auto temp = new std::shared_ptr<T>[capacity];
    for (size_t i = 0; i < size; ++i)
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
    std::cout << "size=" << list->get_size() << ", capacity=" << list->get_capacity() << std::endl;
    for (size_t i = 0; i < list->get_size(); ++i)
        std::cout << list->get(i)->to_string();

    std::cout << "----------Test insert()----------\n";
    list->insert(5, std::make_shared<Person>(30, "Bob0"));
    std::cout << "size=" << list->get_size() << ", capacity=" << list->get_capacity() << std::endl;
    for (size_t i = 0; i < list->get_size(); ++i)
        std::cout << list->get(i)->to_string();

    std::cout << "----------Test contains() & index_of()----------\n";
    if (list->contains(std::make_shared<Person>(30, "Bob0")))
        std::cout << "index=" << list->index_of(std::make_shared<Person>(30, "Bob0")) << std::endl;

    std::cout << "----------Test set()----------\n";
    list->set(5, std::make_shared<Person>(15, "Jack"));
    std::cout << "size=" << list->get_size() << ", capacity=" << list->get_capacity() << std::endl;
    for (size_t i = 0; i < list->get_size(); ++i)
        std::cout << list->get(i)->to_string();

    std::cout << "----------Test remove()----------\n";
    std::cout << "Remove: " << list->remove(5)->to_string();
    std::cout << "size=" << list->get_size() << ", capacity=" << list->get_capacity() << std::endl;
    for (size_t i = 0; i < list->get_size(); ++i)
        std::cout << list->get(i)->to_string();

    std::cout << "----------Test clear()----------\n";
    list->clear();
    std::cout << "size=" << list->get_size() << ", capacity=" << list->get_capacity() << std::endl;
    return 0;
}

/*
2022年3月26日 12:59:27
输出:
----------Test add()----------
size=8, capacity=8
[20, Alice0]
[21, Alice1]
[22, Alice2]
[23, Alice3]
[24, Alice4]
[25, Alice5]
[26, Alice6]
[27, Alice7]
----------Test insert()----------
size=9, capacity=16
[20, Alice0]
[21, Alice1]
[22, Alice2]
[23, Alice3]
[24, Alice4]
[30, Bob0]
[25, Alice5]
[26, Alice6]
[27, Alice7]
----------Test contains() & index_of()----------
delete 0x632250[30, Bob0]
index=5
delete 0x632250[30, Bob0]
----------Test set()----------
delete 0x6324e0[30, Bob0]
size=9, capacity=16
[20, Alice0]
[21, Alice1]
[22, Alice2]
[23, Alice3]
[24, Alice4]
[15, Jack]
[25, Alice5]
[26, Alice6]
[27, Alice7]
----------Test remove()----------
Remove: [15, Jack]
delete 0x632250[15, Jack]
size=8, capacity=16
[20, Alice0]
[21, Alice1]
[22, Alice2]
[23, Alice3]
[24, Alice4]
[25, Alice5]
[26, Alice6]
[27, Alice7]
----------Test clear()----------
delete 0x6322e0[20, Alice0]
delete 0x632320[21, Alice1]
delete 0x632360[22, Alice2]
delete 0x6323a0[23, Alice3]
delete 0x6323e0[24, Alice4]
delete 0x632420[25, Alice5]
delete 0x632460[26, Alice6]
size=0, capacity=16
delete 0x6324a0[27, Alice7]
*/