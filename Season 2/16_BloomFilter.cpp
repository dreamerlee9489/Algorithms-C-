#include "./16_BloomFilter.hpp"

using namespace app;

int main(int argc, char const *argv[]) {
    BloomFilter<int> bf = BloomFilter<int>(1000000, 0.4);
    for (size_t i = 1; i <= 1000000; i++) {
        bf.add(make_shared<int>(i));
    }
    int count = 0;
    for (size_t i = 1000001; i <= 2000000; i++) {
        if (bf.contains(make_shared<int>(i)))
            count++;
    }
    cout << "count = " << count << endl;
    return 0;
}
