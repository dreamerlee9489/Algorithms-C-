#ifndef ILIST_H
#define ILIST_H
#include <iostream>
#include <string>
#include <memory>
using namespace std;

namespace app
{
    /**
     * @brief 线性表基类
     * @date 2022-03-30
     * @tparam T
     */
    template <typename T>
    class IList
    {
    protected:
        size_t _size = 0;
        void check_range(int index, bool isAdd = false) const;

    public:
        IList() = default;
        virtual ~IList() = default;
        virtual int index_of(shared_ptr<T> data) const = 0;
        virtual void insert(int index, shared_ptr<T> data) = 0;
        virtual shared_ptr<T> remove(int index) = 0;
        virtual shared_ptr<T> get(int index) const = 0;
        virtual void set(int index, shared_ptr<T> data) = 0;
        virtual void clear() = 0;
        size_t size() const { return _size; }
        bool is_empty() const { return _size == 0; }
        bool contains(shared_ptr<T> data) const { return index_of(data) >= 0 ? true : false; }
        void add(shared_ptr<T> data) { return insert(_size, data); }
    };

    template <typename T>
    inline void IList<T>::check_range(int index, bool isAdd) const
    {
        if (!isAdd && (index >= _size || index < 0))
            throw out_of_range("index = " + to_string(index) + " out of range: [0, " + to_string(_size - 1) + "].");
        if (index > _size || index < 0)
            throw out_of_range("index = " + to_string(index) + " out of range for add: [0, " + to_string(_size) + "].");
    }
} // namespace app

#endif /* ILIST_H */
