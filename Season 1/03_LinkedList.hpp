#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include "./03_IList.hpp"

namespace app {
    /**
     * @brief 双向循环链表
     * @date 2022-03-30
     * @tparam T
     */
    template<typename T>
    class LinkedList : public IList<T> {
        template<typename U>
        friend ostream &operator<<(ostream &os, const LinkedList<U> &list);

        template<typename U>
        struct Node {
            shared_ptr<T> mData = nullptr;
            Node<U> *pPrev = nullptr, *pNext = nullptr;

            Node<U> &operator=(const Node<U> &node);

            Node<U> &operator=(Node<U> &&node) noexcept;

            Node(shared_ptr<T> data, Node<U> *prev = nullptr, Node<U> *next = nullptr);

            Node(const Node<U> &node) { *this = node; }

            Node(Node<U> &&node) noexcept { *this = move(node); }

            ~Node() { mData = nullptr; }

            shared_ptr<T> disconnect();
        };

        Node<T> *get_node(int index) const;

    public:
        Node<T> *mHead = nullptr;

        LinkedList<T> &operator=(const LinkedList<T> &list);

        LinkedList<T> &operator=(LinkedList<T> &&list) noexcept;

        LinkedList() {
            mHead = new Node<T>(nullptr);
            mHead->pPrev = mHead->pNext = mHead;
        }

        LinkedList(const LinkedList<T> &list) { *this = list; }

        LinkedList(LinkedList<T> &&list) noexcept { *this = move(list); }

        ~LinkedList() {
            clear();
            delete mHead;
        }

        int index_of(shared_ptr<T> data) const override;

        void insert(int index, shared_ptr<T> data) override;

        shared_ptr<T> remove(int index) override;

        shared_ptr<T> get(int index) const override;

        void set(int index, shared_ptr<T> data) override;

        void clear() override;
    };

    template<typename T>
    template<typename U>
    inline LinkedList<T>::Node<U>::Node(shared_ptr<T> data, Node<U> *prev, Node<U> *next) {
        mData = data;
        pPrev = prev;
        pNext = next;
    }

    template<typename T>
    template<typename U>
    inline LinkedList<T>::Node<U> &LinkedList<T>::Node<U>::operator=(const Node<U> &node) {
        mData = node.mData;
        pPrev = node.pPrev;
        pNext = node.pNext;
        return *this;
    }

    template<typename T>
    template<typename U>
    inline LinkedList<T>::Node<U> &LinkedList<T>::Node<U>::operator=(Node<U> &&node) noexcept {
        mData = nullptr;
        this = &node;
        return *this;
    }

    template<typename T>
    template<typename U>
    inline shared_ptr<T> LinkedList<T>::Node<U>::disconnect() {
        auto old = mData;
        mData = nullptr;
        pPrev = pNext = nullptr;
        return old;
    }

    template<typename U>
    inline ostream &operator<<(ostream &os, const LinkedList<U> &list) {
        for (size_t i = 0; i < list.mSize; ++i)
            if (list.get(i) != nullptr)
                os << *list.get(i) << "\n";
        return os;
    }

    template<typename T>
    inline LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &list) {
        clear();
        if (mHead == nullptr) {
            mHead = new Node<T>(nullptr);
            mHead->pPrev = mHead->pNext = mHead;
        }
        for (size_t i = 0; i < list.mSize; ++i)
            insert(i, list.get(i));
        return *this;
    }

    template<typename T>
    inline LinkedList<T> &LinkedList<T>::operator=(LinkedList<T> &&list) noexcept {
        clear();
        if (mHead == nullptr) {
            mHead = new Node<T>(nullptr);
            mHead->pPrev = mHead->pNext = mHead;
        }
        if (list.mSize > 0) {
            this->mSize = list.mSize;
            mHead->pNext = list.mHead->pNext;
            mHead->pPrev = list.mHead->pPrev;
            list.mHead->pNext->pPrev = mHead;
            list.mSize = 0;
            list.mHead = nullptr;
        }
        return *this;
    }

    template<typename T>
    inline int LinkedList<T>::index_of(shared_ptr<T> data) const {
        Node<T> *p = mHead;
        for (size_t i = 0; i < this->mSize; ++i) {
            p = p->pNext;
            if (*p->mData == *data)
                return i;
        }
        return -1;
    }

    template<typename T>
    inline void LinkedList<T>::insert(int index, shared_ptr<T> data) {
        this->check_range(index, true);
        Node<T> *prev = get_node(index - 1);
        Node<T> *next = prev->pNext;
        Node<T> *temp = new Node<T>(data, prev, next);
        if (next != mHead) {
            prev->pNext = temp;
            next->pPrev = temp;
        } else {
            prev->pNext = temp;
            temp->pNext = mHead;
            mHead->pPrev = temp;
        }
        this->mSize++;
    }

    template<typename T>
    inline shared_ptr<T> LinkedList<T>::remove(int index) {
        this->check_range(index);
        Node<T> *old = mHead->pNext;
        for (size_t i = 0; i < index; ++i)
            old = old->pNext;
        if (index == 0) {
            mHead->pNext = mHead->pNext->pNext;
            mHead->pNext->pPrev = mHead;
        } else if (index == this->mSize - 1) {
            mHead->pPrev = mHead->pPrev->pPrev;
            mHead->pPrev->pNext = mHead;
        } else {
            old->pPrev->pNext = old->pNext;
            old->pNext->pPrev = old->pPrev;
        }
        this->mSize--;
        return old->disconnect();
    }

    template<typename T>
    inline shared_ptr<T> LinkedList<T>::get(int index) const {
        this->check_range(index);
        Node<T> *p = mHead->pNext;
        for (size_t i = 0; i < index; ++i)
            p = p->pNext;
        return p->mData;
    }

    template<typename T>
    inline void LinkedList<T>::set(int index, shared_ptr<T> data) {
        this->check_range(index);
        Node<T> *p = mHead->pNext;
        for (size_t i = 0; i < index; ++i)
            p = p->pNext;
        p->mData = data;
    }

    template<typename T>
    inline void LinkedList<T>::clear() {
        if (this->mSize > 0) {
            Node<T> *p = mHead->pPrev;
            while (p != mHead) {
                p = p->pPrev;
                delete p->pNext;
            }
            mHead->pNext = mHead;
            mHead->pPrev = mHead;
            this->mSize = 0;
        }
    }

    template<typename T>
    inline LinkedList<T>::Node<T> *LinkedList<T>::get_node(int index) const {
        if (index == -1)
            return mHead;
        if (index == this->mSize - 1)
            return mHead->pPrev;
        Node<T> *p = mHead;
        for (size_t i = 0; i < index; ++i)
            p = p->pNext;
        return p->pNext;
    }
} // namespace app

#endif /* LINKEDLIST_HPP */