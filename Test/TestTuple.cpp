#include <iostream>
#include <tuple>

using namespace std;

int main(int argc, char const *argv[]) {
    tuple<int, int, int> tuple1 = {1, 2, 3};
    cout << get<1>(tuple1) << endl;
    return 0;
}
