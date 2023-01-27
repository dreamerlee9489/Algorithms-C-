#include <vector>
#include <iostream>

class Test
{
public:
    Test &operator=(const Test &test)
    {
        std::cout << "operator=(const Test &test)";
        return *this;
    }

    Test &operator=(Test &&test) noexcept
    {
        std::cout << "operator=(Test &&test)";
        return *this;
    }

    Test(int i)
    {
        std::cout << "default\n";
    }

    Test(const Test &test)
    {
        std::cout << "copy\n";
    }

    Test(Test &&test) noexcept
    {
        std::cout << "move\n";
    }

    ~Test() = default;
};

int main()
{
    std::vector<Test> vec;
    Test test = Test(10);
    vec.push_back(test);
    std::cout << "移动构造函数必须和noexcept配套使用!\n";
    vec.emplace_back(10);
    std::cout << "******************\n";
    vec.emplace_back(std::move(test));
    return 0;
}