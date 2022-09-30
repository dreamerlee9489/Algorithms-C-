#include <iostream>
#include <tuple>

using namespace std;

int main(int argc, char const *argv[]) {
  tuple<int, float, string> tuple = {1, 3.14f, "Hello World!"};
  cout << get<0>(tuple) << endl;
  cout << get<1>(tuple) << endl;
  cout << get<2>(tuple) << endl;
  return 0;
}
