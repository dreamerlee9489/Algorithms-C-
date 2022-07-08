#ifndef ISORT_HPP
#define ISORT_HPP
#include <ctime>
#include <memory>
#include <iostream>
using namespace std;

namespace app
{
    /**
     * @brief 排序算法基类
     * @date 2022-04-27
     * @tparam T
     */
    template <typename T>
    class ISort
    {
        size_t _cmp_cnt = 0, _swap_cnt = 0;
        clock_t _time = 0;

    protected:
        T *_array = nullptr;
        size_t _size = 0;
        virtual void sort_algorithm() = 0;
        int compare(size_t index0, size_t index1)
        {
            _cmp_cnt++;
            if (_array[index0] < _array[index1])
                return -1;
            else if (_array[index0] > _array[index1])
                return 1;
            else
                return 0;
        }
        int compare(T data0, T data1)
        {
            _cmp_cnt++;
            if (data0 < data1)
                return -1;
            else if (data0 > data1)
                return 1;
            else
                return 0;
        }
        void swap(size_t index0, size_t index1)
        {
            if (index0 != index1)
            {
                _swap_cnt++;
                T temp = _array[index0];
                _array[index0] = _array[index1];
                _array[index1] = temp;
            }
        }

    public:
        ISort() = default;
        virtual ~ISort() = default;
        void sort(T *array, size_t size)
        {
            if (array != nullptr && size >= 2)
            {
                _array = array;
                _size = size;
                clock_t start = clock();
                sort_algorithm();
                _time = clock() - start;
            }
        }
    };
} // namespace app

#endif /* ISORT_HPP */
