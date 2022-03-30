#ifndef ARRAYLIST_H
#define ARRAYLIST_H
#include "./03_IList.h"
// 泛型动态数组(智能指针版)
template <typename T>
class ArrayList : public IList<T>
{
private:
	const size_t DEFAULT_CAPACITY = 8;
	size_t _capacity = 0;
	std::shared_ptr<T> *_array = nullptr;
	void expand_capacity();

public:
	ArrayList<T>& operator=(const ArrayList<T>& list);
	ArrayList<T>& operator=(ArrayList<T>&& list);
	ArrayList();
	~ArrayList();
	ArrayList(const ArrayList<T> &list);
	ArrayList(ArrayList<T> &&list);
	size_t capacity() { return _capacity; }
	int index_of(std::shared_ptr<T> element) override;
	std::shared_ptr<T> insert(int index, std::shared_ptr<T> element) override;
	std::shared_ptr<T> remove(int index) override;
	std::shared_ptr<T> get(int index) override;
	std::shared_ptr<T> get(int index) const override;
	std::shared_ptr<T> set(int index, std::shared_ptr<T> element) override;
	void clear() override;
};

#endif