#ifndef ARRAYLIST_H
#define ARRAYLIST_H
#include "./03_IList.h"
// 泛型动态数组
template <typename T>
class ArrayList : public IList<T>
{
private:
	size_t _capacity = 0;
	const size_t DEFAULT_CAPACITY = 8;
	std::shared_ptr<T> *array = nullptr;
	void expand_capacity();

public:
	ArrayList();
	~ArrayList();
	size_t capacity() { return _capacity; }
	int index_of(std::shared_ptr<T> element) override;
	std::shared_ptr<T> insert(int index, std::shared_ptr<T> element) override;
	std::shared_ptr<T> remove(int index) override;
	std::shared_ptr<T> get(int index) override;
	std::shared_ptr<T> set(int index, std::shared_ptr<T> element) override;
	void clear() override;
};

#endif

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
