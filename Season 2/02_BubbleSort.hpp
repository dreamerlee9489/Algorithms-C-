#ifndef BUBBLE_SORT_HPP
#define BUBBLE_SORT_HPP
#include "./01_ISort.hpp"

namespace app
{
    /**
     * @brief 冒泡排序
     * @date 2022-04-27
     * @tparam T
     */
    template <typename T>
    class BubbleSort : public ISort<T>
    {
        void sort_algorithm() override
        {
            for (size_t end = this->_size - 1; end > 0; --end)
            {
                size_t sorted_index = 1;
                for (size_t beg = 1; beg <= end; ++beg)
                {
                    if (this->compare(beg, beg - 1) < 0)
                    {
                        this->swap(beg, beg - 1);
                        sorted_index = beg;
                    }
                }
                end = sorted_index;
            }
        }

    public:
        BubbleSort() = default;
        ~BubbleSort() = default;
    };
} // namespace app

#endif /* BUBBLE_SORT_HPP */
