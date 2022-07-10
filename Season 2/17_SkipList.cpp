#include <cassert>
#include "./17_SkipList.hpp"
using namespace app;

template <typename K, typename V>
void test(SkipList<K, V> &list, int count, int delta)
{
    for (size_t i = 0; i < count; i++)
        list.add(new int(i), new int(i + delta));
    for (size_t i = 0; i < count; i++)
        assert(*list.get(new int(i)) == i + delta);
    assert(list.size() == count);
    for (size_t i = 0; i < count; i++)
        assert(*list.remove(new int(i)) == i + delta);
    assert(list.size() == 0);
}

int main(int argc, char const *argv[])
{
    SkipList<int, int> list;
    test(list, 30, 10);
    cout << "Execution continues past all asserts.";
    return 0;
}
