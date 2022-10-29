#include <iostream>
#include <mutex>
#include <thread>

int value = 0;
std::mutex mutex;

void Test() {
  std::lock_guard<std::mutex> guard(mutex);
  value++;
  std::cout << "value = " << value << "\n";
}

int main(int argc, char const *argv[]) {
  std::thread th1(Test);
  std::thread th2(Test);
  th1.join();
  th2.join();
  return 0;
}
