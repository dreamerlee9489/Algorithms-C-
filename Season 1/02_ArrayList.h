#ifndef ARRAYLIST_H
#define ARRAYLIST_H
#include "./03_IList.h"
// 泛型动态数组(智能指针版)
template <typename T>
class ArrayList : public IList<T>
{
	template <typename U>
	friend std::ostream &operator<<(std::ostream &os, const ArrayList<U> &list);

private:
	const size_t DEFAULT_CAPACITY = 8;
	size_t _capacity = 0;
	std::shared_ptr<T> *_array = nullptr;
	void ensure_capacity();

public:
	ArrayList<T> &operator=(const ArrayList<T> &list);
	ArrayList<T> &operator=(ArrayList<T> &&list) noexcept;
	ArrayList();
	~ArrayList();
	ArrayList(const ArrayList<T> &list) { *this = list; }
	ArrayList(ArrayList<T> &&list) noexcept { *this = std::move(list); }
	size_t capacity() const { return _capacity; }
	int index_of(std::shared_ptr<T> data) const override;
	std::shared_ptr<T> insert(int index, std::shared_ptr<T> data) override;
	std::shared_ptr<T> remove(int index) override;
	std::shared_ptr<T> get(int index) const override;
	std::shared_ptr<T> set(int index, std::shared_ptr<T> data) override;
	void clear() override;
};

template <typename T>
ArrayList<T> &ArrayList<T>::operator=(const ArrayList<T> &list)
{
	clear();
	this->_size = 0;
	_capacity = DEFAULT_CAPACITY;
	_array = new std::shared_ptr<T>[_capacity];
	for (size_t i = 0; i < list._size; ++i)
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
ArrayList<T>::~ArrayList()
{
	clear();
	delete[] _array;
}

template <typename T>
int ArrayList<T>::index_of(std::shared_ptr<T> data) const
{
	for (size_t i = 0; i < this->_size; ++i)
		if (*_array[i] == *data)
			return i;
	return -1;
}

template <typename T>
std::shared_ptr<T> ArrayList<T>::insert(int index, std::shared_ptr<T> data)
{
	this->check_range(index, true);
	ensure_capacity();
	for (size_t i = this->_size; i > index; --i)
		_array[i] = _array[i - 1];
	_array[index] = data;
	this->_size++;
	return data;
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
std::shared_ptr<T> ArrayList<T>::get(int index) const
{
	this->check_range(index);
	return _array[index];
}

template <typename T>
std::shared_ptr<T> ArrayList<T>::set(int index, std::shared_ptr<T> data)
{
	this->check_range(index);
	_array[index] = data;
	return data;
}

template <typename T>
void ArrayList<T>::clear()
{
	for (size_t i = 0; i < _capacity; ++i)
		_array[i] = nullptr;
	this->_size = 0;
}

template <typename T>
void ArrayList<T>::ensure_capacity()
{
	if (this->_size >= _capacity)
	{
		_capacity <<= 1;
		auto temp = new std::shared_ptr<T>[_capacity];
		for (size_t i = 0; i < this->_size; ++i)
			temp[i] = _array[i];
		_array = temp;
	}
}

template <typename U>
std::ostream &operator<<(std::ostream &os, const ArrayList<U> &list)
{
	for (size_t i = 0; i < list._size; ++i)
		if (list.get(i) != nullptr)
			os << *list.get(i);
	return os;
}

#endif