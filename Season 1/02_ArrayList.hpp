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
        size_t mCapacity = 0;
        shared_ptr<T> *pArray = nullptr;

        void ensuremCapacity();

    public:
        ArrayList<T> &operator=(const ArrayList<T> &list);

        ArrayList<T> &operator=(ArrayList<T> &&list) noexcept;

        ArrayList();

        ArrayList(const ArrayList<T> &list) { *this = list; }

        ArrayList(ArrayList<T> &&list) noexcept { *this = move(list); }

        ~ArrayList() { delete[] pArray; }

        size_t capacity() const { return mCapacity; }

        int index_of(shared_ptr<T> data) const override;

        void insert(int index, shared_ptr<T> data) override;

        shared_ptr<T> remove(int index) override;

        shared_ptr<T> get(int index) const override {
            this->check_range(index);
            return pArray[index];
        }

        void set(int index, shared_ptr<T> data) override {
            this->check_range(index);
            pArray[index] = data;
        }

        void clear() override {
            for (size_t i = 0; i < this->mSize; ++i)
                pArray[i] = nullptr;
            this->mSize = 0;
        }
    };

    template<typename U>
    inline ostream &operator<<(ostream &os, const ArrayList<U> &list) {
        for (size_t i = 0; i < list.mSize; ++i)
            if (list.get(i) != nullptr)
                os << *list.get(i) << "\n";
        return os;
    }

    template<typename T>
    inline ArrayList<T> &ArrayList<T>::operator=(const ArrayList<T> &list) {
        clear();
        for (size_t i = 0; i < list.mSize; ++i)
            insert(i, list.get(i));
        return *this;
    }

    template<typename T>
    inline ArrayList<T> &ArrayList<T>::operator=(ArrayList<T> &&list) noexcept {
        clear();
        this->mSize = list.mSize;
        pArray = list.pArray;
        mCapacity = list.mCapacity;
        list.mSize = 0;
        list.pArray = nullptr;
        return *this;
    }

    template<typename T>
    inline ArrayList<T>::ArrayList() {
        this->mSize = 0;
        mCapacity = DEFAULT_CAPACITY;
        pArray = new shared_ptr<T>[mCapacity];
    }

    template<typename T>
    inline int ArrayList<T>::index_of(shared_ptr<T> data) const {
        for (size_t i = 0; i < this->mSize; ++i)
            if (*pArray[i] == *data)
                return i;
        return -1;
    }

    template<typename T>
    inline void ArrayList<T>::insert(int index, shared_ptr<T> data) {
        this->check_range(index, true);
        ensuremCapacity();
        for (size_t i = this->mSize; i > index; --i)
            pArray[i] = pArray[i - 1];
        pArray[index] = data;
        this->mSize++;
    }

    template<typename T>
    inline shared_ptr<T> ArrayList<T>::remove(int index) {
        this->check_range(index);
        auto old = pArray[index];
        for (size_t i = index + 1; i < this->mSize; ++i)
            pArray[i - 1] = pArray[i];
        pArray[--this->mSize] = nullptr;
        return old;
    }

    template<typename T>
    inline void ArrayList<T>::ensuremCapacity() {
        if (this->mSize >= mCapacity) {
            shared_ptr<T> *old = pArray;
            mCapacity <<= 1;
            pArray = new shared_ptr<T>[mCapacity];
            for (size_t i = 0; i < this->mSize; ++i)
                pArray[i] = old[i];
            delete[] old;
        }
    }
} // namespace app

#endif /* ARRAYLIST_HPP */