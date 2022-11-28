#include <iostream>
#include <mutex>
#include <thread>

int value = 0;
std::mutex mutex;

void Test() {
  // mutex.lock();
  std::lock_guard<std::mutex> guard(mutex);
  value++;
  // std::cout << "value = " << value << "\n";
  // mutex.unlock();
}

int main(int argc, char const *argv[]) {
  // std::thread th1(Test);
  // std::thread th2(Test);
  // th1.join();
  // th2.join();
  std::cout << "id = " << std::this_thread::get_id() << "\n";
  std::thread ths[4096];
  for (int i = 0; i < 4096; i++) {
    ths[i] = std::thread(Test);
  }
  for (int i = 0; i < 4096; i++) {
    std::cout << "id = " << ths[i].get_id() << "  ";
    ths[i].join();
  }
  std::cout << "\nvalue = " << value << "\n";

  return 0;
}
