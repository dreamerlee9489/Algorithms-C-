#ifndef IHEAP_HPP
#define IHEAP_HPP

#include <cmath>
#include <queue>
#include <memory>
#include <iostream>

using namespace std;

namespace app {
    /**
     * @brief 堆基类
     * @date 2022-04-21
     * @tparam T
     */
    template<typename T>
    class IHeap {
    protected:
        using Comparator = int (*)(shared_ptr<T> a, shared_ptr<T> b);
        using TraverseFunc = bool (*)(shared_ptr<T> data);
        size_t mSize = 0;
        Comparator mComparator = nullptr;

        int compare(shared_ptr<T> a, shared_ptr<T> b);

    public:
        IHeap(Comparator comparator = nullptr) { mComparator = comparator; }

        virtual ~IHeap() = default;

        size_t size() const { return mSize; }

        bool is_empty() const { return mSize == 0; }

        virtual void add(shared_ptr<T> data) = 0;

        virtual shared_ptr<T> get() const = 0;

        virtual shared_ptr<T> remove() = 0;

        virtual shared_ptr<T> replace(shared_ptr<T> data) = 0;

        virtual void clear() = 0;

        virtual void traverse(TraverseFunc func = nullptr) const = 0;
    };

    template<typename T>
    inline int IHeap<T>::compare(shared_ptr<T> a, shared_ptr<T> b) {
        if (mComparator != nullptr)
            return mComparator(a, b);
        else {
            if (*a < *b)
                return -1;
            else if (*a > *b)
                return 1;
            return 0;
        }
    }
} // namespace app

#endif /* IHEAP_HPP */
