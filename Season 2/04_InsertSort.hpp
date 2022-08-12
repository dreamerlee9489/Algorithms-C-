#ifndef INSERT_SORT_HPP
#define INSERT_SORT_HPP

#include "./01_ISort.hpp"

namespace app {
    /**
     * @brief 插入排序
     * @date 2022-04-27
     * @tparam T
     */
    template<typename T>
    class InsertSort : public ISort<T> {
        void sort_algorithm() override {
            for (size_t beg = 1; beg < this->mSize; ++beg) {
                size_t cur = beg;
                T val = this->pArray[cur];
                while (cur > 0 && this->compare(val, this->pArray[cur - 1]) < 0)
                    this->pArray[cur--] = this->pArray[cur - 1];
                this->pArray[cur] = val;
            }
        }

    public:
        InsertSort() = default;

        ~InsertSort() = default;
    };

} // namespace app

#endif /* INSERT_SORT_HPP */
