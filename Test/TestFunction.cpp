#include <iostream>
#include <list>

template <typename... Args>
class Event
{
  using Func = void (*)(Args... args);
  std::list<Func> _event;

public:
  Event& operator+=(const Func& func)
  {
    _event.push_back(func);
    return *this;
  }

  Event& operator-=(const Func& func)
  {
    _event.remove(func);
    return *this;
  }

  void operator()(Args... args)
  {
    for (auto& f : _event)
      f(args...);
  }

  Event() = default;

  ~Event() = default;
};

void Add(int a, int b)
{
  std::cout << a << " + " << b << " = " << a + b << "\n";
}

void Sub(int a, int b)
{
  std::cout << a << " - " << b << " = " << a - b << "\n";
}

void Mul(int a, int b)
{
  std::cout << a << " * " << b << " = " << a * b << "\n";
}

void Div(int a, int b)
{
  std::cout << a << " / " << b << " = " << a * 1.0 / b * 1.0 << "\n";
}

int main(int argc, char const* argv[])
{
  Event<int, int> e;
  e += Add;
  e += Sub;
  e += Mul;
  e += Div;
  e(3, 4);
  e -= Add;
  e -= Sub;
  e(5, 6);
  return 0;
}
