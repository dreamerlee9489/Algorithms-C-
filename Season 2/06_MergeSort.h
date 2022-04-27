#ifndef MERGE_SORT_H
#define MERGE_SORT_H
#include "./01_ISort.h"
/**
 * @brief 归并排序
 * @date 2022-04-27 
 * @tparam T 
 */
template <typename T>
class MergeSort : public ISort<T>
{
    T *_left_array = nullptr;
    void merge(size_t beg, size_t mid, size_t end)
    {
        size_t li = 0, le = mid - beg;
        size_t ri = mid, re = end;
        size_t ai = beg;
        for(size_t i = li; i < le; ++i)
            _left_array[i] = this->_array[beg + i];
        while (li < le)
        {
            if(ri < re && this->compare(this->_array[ri], _left_array[li]) < 0)
                this->_array[ai++] = this->_array[ri++];
            else
                this->_array[ai++] = _left_array[li++];
        }
    }
    void divide(size_t beg, size_t end)
    {
        if(end - beg > 1)
        {
            int mid = (beg + end) >> 1;
            divide(beg, mid);
            divide(mid, end);
            merge(beg, mid, end);
        }
    }
    void sort_algorithm() override
    {
        _left_array = new T[this->_size >> 1];
        divide(0, this->_size);
    }

public:
    MergeSort() = default;
    ~MergeSort() = default;
};


#endif /* MERGE_SORT_H */
