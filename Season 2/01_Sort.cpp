#include <initializer_list>
#include "./02_BubbleSort.h"
#include "./03_SelectSort.h"
#include "./04_InsertSort.h"
#include "./05_HeapSort.h"
#include "./06_MergeSort.h"
#include "./07_QuickSort.h"

void test_sort(int *array, size_t size, initializer_list<ISort<int> *> list)
{
    for (ISort<int> *const *beg = list.begin(); beg != list.end(); ++beg)
    {
        int *copy = new int[size];
        for(size_t i = 0; i < size; ++i)
            copy[i] = array[i];
        (*beg)->sort(copy, 8);
        std::cout << typeid(**beg).name() << ":\t";
        for (size_t i = 0; i < 8; ++i)
            std::cout << copy[i] << "\t";
        std::cout << "\n";
    }
}

int main(int argc, char const *argv[])
{
    int array[] = {7, 3, 5, 8, 6, 7, 4, 5};
    test_sort(array, 8, 
    {
        new BubbleSort<int>(),
        new SelectSort<int>(),
        new InsertSort<int>(),
        new HeapSort<int>(),
        new MergeSort<int>(),
        new QuickSort<int>()
    });
    
    return 0;
}
