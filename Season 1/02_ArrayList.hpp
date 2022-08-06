#ifndef ARRAYLIST_HPP
#define ARRAYLIST_HPP

#include "./03_IList.hpp"

namespace app {
    /**
     * @brief 动态数组
     * @date 2022-03-30
     * @tparam T
     */
    template<typename T>
    class ArrayList : public IList<T> {
        template<typename U>
        friend ostream &operator<<(ostream &os, const ArrayList<U> &list);

        const size_t DEFAULT_CAPACITY = 8;
        size_t _capacity = 0;
        shared_ptr<T> *_array = nullptr;

        void ensure_capacity();

    public:
        ArrayList<T> &operator=(const ArrayList<T> &list);

        ArrayList<T> &operator=(ArrayList<T> &&list) noexcept;

        ArrayList();

        ArrayList(const ArrayList<T> &list) { *this = list; }

        ArrayList(ArrayList<T> &&list) noexcept { *this = move(list); }

        ~ArrayList() { delete[] _array; }

        size_t capacity() const { return _capacity; }

        int index_of(shared_ptr<T> data) const override;

        void insert(int index, shared_ptr<T> data) override;

        shared_ptr<T> remove(int index) override;

        shared_ptr<T> get(int index) const override {
            this->check_range(index);
            return _array[index];
        }

        void set(int index, shared_ptr<T> data) override {
            this->check_range(index);
            _array[index] = data;
        }

        void clear() override {
            for (size_t i = 0; i < this->_size; ++i)
                _array[i] = nullptr;
            this->_size = 0;
        }
    };

    template<typename U>
    inline ostream &operator<<(ostream &os, const ArrayList<U> &list) {
        for (size_t i = 0; i < list._size; ++i)
            if (list.get(i) != nullptr)
                os << *list.get(i) << "\n";
        return os;
    }

    template<typename T>
    inline ArrayList<T> &ArrayList<T>::operator=(const ArrayList<T> &list) {
        clear();
        for (size_t i = 0; i < list._size; ++i)
            insert(i, list.get(i));
        return *this;
    }

    template<typename T>
    inline ArrayList<T> &ArrayList<T>::operator=(ArrayList<T> &&list) noexcept {
        clear();
        this->_size = list._size;
        _array = list._array;
        _capacity = list._capacity;
        list._size = 0;
        list._array = nullptr;
        return *this;
    }

    template<typename T>
    inline ArrayList<T>::ArrayList() {
        this->_size = 0;
        _capacity = DEFAULT_CAPACITY;
        _array = new shared_ptr<T>[_capacity];
    }

    template<typename T>
    inline int ArrayList<T>::index_of(shared_ptr<T> data) const {
        for (size_t i = 0; i < this->_size; ++i)
            if (*_array[i] == *data)
                return i;
        return -1;
    }

    template<typename T>
    inline void ArrayList<T>::insert(int index, shared_ptr<T> data) {
        this->check_range(index, true);
        ensure_capacity();
        for (size_t i = this->_size; i > index; --i)
            _array[i] = _array[i - 1];
        _array[index] = data;
        this->_size++;
    }

    template<typename T>
    inline shared_ptr<T> ArrayList<T>::remove(int index) {
        this->check_range(index);
        auto old = _array[index];
        for (size_t i = index + 1; i < this->_size; ++i)
            _array[i - 1] = _array[i];
        _array[--this->_size] = nullptr;
        return old;
    }

    template<typename T>
    inline void ArrayList<T>::ensure_capacity() {
        if (this->_size >= _capacity) {
            shared_ptr<T> *old = _array;
            _capacity <<= 1;
            _array = new shared_ptr<T>[_capacity];
            for (size_t i = 0; i < this->_size; ++i)
                _array[i] = old[i];
            delete[] old;
        }
    }
} // namespace app

#endif /* ARRAYLIST_HPP */