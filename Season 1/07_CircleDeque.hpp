#ifndef CIRCLE_DEQUE_HPP
#define CIRCLE_DEQUE_HPP

#include <iostream>
#include <memory>

using namespace std;

namespace app {
    /**
     * @brief 循环双端队列
     * @date 2022-04-08
     * @tparam T
     */
    template<typename T>
    class CircleDeque {
        template<typename U>
        friend ostream &operator<<(ostream &os, const CircleDeque<U> &deque);

        const size_t DEFAULT_CAPACITY = 8;
        size_t mCapacity = 0, mSize = 0, mFront = 0;
        shared_ptr<T> *pArray = nullptr;

        int true_index(int index) const;

        void ensuremCapacity();

    public:
        CircleDeque<T> &operator=(const CircleDeque<T> &deque);

        CircleDeque<T> &operator=(CircleDeque<T> &&deque) noexcept;

        CircleDeque();

        CircleDeque(const CircleDeque<T> &deque) { *this = deque; }

        CircleDeque(CircleDeque<T> &&deque) noexcept { *this = move(deque); }

        ~CircleDeque();

        size_t size() const { return mSize; }

        size_t capacity() const { return mCapacity; }

        bool is_empty() const { return mSize == 0; }

        void push(shared_ptr<T> data);

        shared_ptr<T> pop();

        void push_front(shared_ptr<T> data);

        shared_ptr<T> pop_rear();

        shared_ptr<T> front() const { return pArray[mFront]; }

        shared_ptr<T> rear() const { return pArray[true_index(mSize - 1)]; }

        void clear();
    };

    template<typename U>
    inline ostream &operator<<(ostream &os, const CircleDeque<U> &deque) {
        for (size_t i = 0; i < deque.mCapacity; ++i) {
            if (deque.pArray[i] != nullptr)
                os << *deque.pArray[i] << "\n";
            else
                os << "nullptr\n";
        }
        return os;
    }

    template<typename T>
    inline CircleDeque<T> &CircleDeque<T>::operator=(const CircleDeque<T> &deque) {
        delete[] pArray;
        pArray = new shared_ptr<T>[deque.mCapacity];
        mCapacity = deque.mCapacity;
        mSize = deque.mSize;
        mFront = deque.mFront;
        for (size_t i = 0; i < deque.mCapacity; ++i)
            pArray[i] = deque.pArray[i];
        return *this;
    }

    template<typename T>
    inline CircleDeque<T> &CircleDeque<T>::operator=(CircleDeque<T> &&deque) noexcept {
        pArray = deque.pArray;
        mCapacity = deque.mCapacity;
        mSize = deque.mSize;
        mFront = deque.mFront;
        deque.mSize = 0;
        deque.mFront = 0;
        return *this;
    }

    template<typename T>
    inline CircleDeque<T>::CircleDeque() {
        mSize = 0;
        mFront = 0;
        mCapacity = DEFAULT_CAPACITY;
        pArray = new shared_ptr<T>[mCapacity];
    }

    template<typename T>
    inline CircleDeque<T>::~CircleDeque() {
        clear();
        delete[] pArray;
    }

    template<typename T>
    inline void CircleDeque<T>::push(shared_ptr<T> data) {
        ensuremCapacity();
        pArray[true_index(mSize)] = data;
        mSize++;
    }

    template<typename T>
    inline shared_ptr<T> CircleDeque<T>::pop() {
        shared_ptr<T> old = pArray[mFront];
        pArray[mFront] = nullptr;
        mFront = true_index(1);
        mSize--;
        return old;
    }

    template<typename T>
    inline void CircleDeque<T>::push_front(shared_ptr<T> data) {
        ensuremCapacity();
        mFront = true_index(-1);
        pArray[mFront] = data;
        mSize++;
    }

    template<typename T>
    inline shared_ptr<T> CircleDeque<T>::pop_rear() {
        int rear = true_index(mSize - 1);
        shared_ptr<T> old = pArray[rear];
        pArray[rear] = nullptr;
        mSize--;
        return old;
    }

    template<typename T>
    inline void CircleDeque<T>::clear() {
        for (size_t i = 0; i < mCapacity; ++i)
            pArray[i] = nullptr;
        mFront = 0;
        mSize = 0;
    }

    template<typename T>
    inline int CircleDeque<T>::true_index(int index) const {
        index += mFront;
        if (index < 0)
            return index + mCapacity;
        return index % mCapacity;
    }

    template<typename T>
    inline void CircleDeque<T>::ensuremCapacity() {
        if (mSize >= mCapacity) {
            shared_ptr<T> *old = pArray;
            size_t new_cap = mCapacity << 1;
            pArray = new shared_ptr<T>[new_cap];
            for (size_t i = 0; i < mSize; ++i)
                pArray[i] = old[true_index(i)];
            mFront = 0;
            mCapacity = new_cap;
            delete[] old;
        }
    }
} // namespace app

#endif /* CIRCLE_DEQUE_HPP */
