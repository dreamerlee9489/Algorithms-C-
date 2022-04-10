#ifndef C991C500_A127_4A7E_8C56_E5651F9215B0
#define C991C500_A127_4A7E_8C56_E5651F9215B0
#include <iostream>

template <typename T>
class NodeA
{
public:
    template <typename U>
    struct NodeB
    {
        int num = 123;
        NodeB() { num = 666; }
    };
    int id = 10;
    NodeA() = default;
    ~NodeA() = default;

private:
};

template <typename T>
class Test : public NodeA<T>
{
public:
    Test() = default;
    ~Test() = default;
    typename Test::template NodeB<T> *print()
    {
        std::cout << "haha hihi\n";
        typename Test::template NodeB<T> *node = new typename Test::template NodeB<T>();
        std::cout << node->num << "\n";
        return node;
    }
};

#endif /* C991C500_A127_4A7E_8C56_E5651F9215B0 */
