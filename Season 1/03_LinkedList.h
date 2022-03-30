#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "./03_IList.h"
// 泛型双向循环链表
template <typename T>
class LinkedList : public IList<T>
{
private:
    template <typename U>
    struct Node
    {
        std::shared_ptr<T> _data = nullptr;
        Node<U> *_prev = nullptr, *_next = nullptr;
        Node<U> &operator=(const Node<U> &node);
        Node<U> &operator=(Node<U> &&node) noexcept;
        Node(std::shared_ptr<T> data, Node<U> *prev = nullptr, Node<U> *next = nullptr);
        Node(const Node<U> &node) { *this = node; }
        Node(Node<U> &&node) noexcept { *this = std::move(node); }
        ~Node();
        std::shared_ptr<T> disconnect();
    };
    Node<T> *get_node(int index);

public:
    Node<T> *_head = nullptr;
    LinkedList<T> &operator=(const LinkedList<T> &list);
    LinkedList<T> &operator=(LinkedList<T> &&list) noexcept;
    LinkedList();
    LinkedList(const LinkedList<T> &list) { *this = list; }
    LinkedList(LinkedList<T> &&list) noexcept { *this = std::move(list); }
    ~LinkedList();
    int index_of(std::shared_ptr<T> element) override;
    std::shared_ptr<T> insert(int index, std::shared_ptr<T> element) override;
    std::shared_ptr<T> remove(int index) override;
    std::shared_ptr<T> get(int index) override;
    std::shared_ptr<T> set(int index, std::shared_ptr<T> element) override;
    void clear() override;
};

#endif

/*
2022年3月28日 20:59:21
输出:
----------Test add()----------
Add: 0xeb1720[20, Alice0]
Add: 0xeb1790[21, Alice1]
Add: 0xeb1800[22, Alice2]
Add: 0xeb1870[23, Alice3]
Add: 0xeb18e0[24, Alice4]
Add: 0xeb1950[25, Alice5]
Add: 0xeb19c0[26, Alice6]
Add: 0xeb1a30[27, Alice7]
size=8
0xeb1720[20, Alice0]
0xeb1790[21, Alice1]
0xeb1800[22, Alice2]
0xeb1870[23, Alice3]
0xeb18e0[24, Alice4]
0xeb1950[25, Alice5]
0xeb19c0[26, Alice6]
0xeb1a30[27, Alice7]
----------Test insert()----------
Insert: 0xeb1aa0[30, Bob0]
Insert: delete 0xeb1b10[35, Bob1]
index = 15 out of range for add: [0, 9].
size=9
0xeb1720[20, Alice0]
0xeb1790[21, Alice1]
0xeb1800[22, Alice2]
0xeb1870[23, Alice3]
0xeb18e0[24, Alice4]
0xeb1aa0[30, Bob0]
0xeb1950[25, Alice5]
0xeb19c0[26, Alice6]
0xeb1a30[27, Alice7]
----------Test contains() & index_of()----------
delete 0xeb1c30[30, Bob0]
Bob0 at index=5
delete 0xeb1c30[30, Bob0]
----------Test set()----------
Set: delete 0xeb1aa0[30, Bob0]
0xeb1c30[25, Jack]
size=9
0xeb1720[20, Alice0]
0xeb1790[21, Alice1]
0xeb1800[22, Alice2]
0xeb1870[23, Alice3]
0xeb18e0[24, Alice4]
0xeb1c30[25, Jack]
0xeb1950[25, Alice5]
0xeb19c0[26, Alice6]
0xeb1a30[27, Alice7]
----------Test remove()----------
Remove: 0xeb1c30[25, Jack]
delete 0xeb1c30[25, Jack]
Remove: index = -1 out of range: [0, 7].
size=8
0xeb1720[20, Alice0]
0xeb1790[21, Alice1]
0xeb1800[22, Alice2]
0xeb1870[23, Alice3]
0xeb18e0[24, Alice4]
0xeb1950[25, Alice5]
0xeb19c0[26, Alice6]
0xeb1a30[27, Alice7]
----------Test clear()----------
delete 0xeb1a30[27, Alice7]
delete 0xeb19c0[26, Alice6]
delete 0xeb1950[25, Alice5]
delete 0xeb18e0[24, Alice4]
delete 0xeb1870[23, Alice3]
delete 0xeb1800[22, Alice2]
delete 0xeb1790[21, Alice1]
delete 0xeb1720[20, Alice0]
size=0
*/