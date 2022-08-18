#include <algorithm>
#include <array>
#include <iostream>

using namespace std;

/**
 * @brief 最优装载问题
 * @remark 贪心策略
 * @date 2022-07-08
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char const *argv[]) {
    int capacity = 30, weight = 0, count = 0;
    array<int, 8> weights = {3, 5, 4, 10, 7, 14, 2, 11};
    sort(weights.begin(), weights.end());

    for (size_t i = 0; i < weights.size() && weight < capacity; i++) {
        int newWeight = weight + weights[i];
        if (newWeight <= capacity) {
            weight = newWeight;
            count++;
            cout << weights[i] << "\t";
        }
    }
    cout << "\n一共选了" << count << "件古董";
    return 0;
}

/*
2       3       4       5       7
一共选了5件古董
*/