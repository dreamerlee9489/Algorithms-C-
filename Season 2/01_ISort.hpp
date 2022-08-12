#ifndef ISORT_HPP
#define ISORT_HPP

#include <ctime>
#include <memory>
#include <iostream>

using namespace std;

namespace app {
    /**
     * @brief 排序算法基类
     * @date 2022-04-27
     * @tparam T
     */
    template<typename T>
    class ISort {
        size_t mCmpCount = 0, mSwapCount = 0;
        clock_t mTime = 0;

    protected:
        T *pArray = nullptr;
        size_t mSize = 0;

        virtual void sort_algorithm() = 0;

        int compare(size_t index0, size_t index1) {
            mCmpCount++;
            if (pArray[index0] < pArray[index1])
                return -1;
            else if (pArray[index0] > pArray[index1])
                return 1;
            else
                return 0;
        }

        int compare(T data0, T data1) {
            mCmpCount++;
            if (data0 < data1)
                return -1;
            else if (data0 > data1)
                return 1;
            else
                return 0;
        }

        void swap(size_t index0, size_t index1) {
            if (index0 != index1) {
                mSwapCount++;
                T temp = pArray[index0];
                pArray[index0] = pArray[index1];
                pArray[index1] = temp;
            }
        }

    public:
        ISort() = default;

        virtual ~ISort() = default;

        void sort(T *array, size_t size) {
            if (array != nullptr && size >= 2) {
                pArray = array;
                mSize = size;
                clock_t start = clock();
                sort_algorithm();
                mTime = clock() - start;
            }
        }
    };
} // namespace app

#endif /* ISORT_HPP */
