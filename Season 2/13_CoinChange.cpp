#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

/**
 * @brief 零钱兑换
 * @remark 贪心策略
 * @date 2022-07-08 
 * @param faces
 * @param money
 */
void coinChange(vector<int> faces, int money)
{
    sort(faces.begin(), faces.end());
    int coins = 0, index = faces.size() - 1;
    while (index >= 0)
    {
        while (money >= faces[index])
        {
            cout << faces[index] << "\t";
            money -= faces[index];
            coins++;
        }
        index--;
    }
    cout << "\n------------------------------\n"
         << coins;
}

int main(int argc, char const *argv[])
{
    coinChange(vector<int>({25, 20, 5, 1}), 41);
    return 0;
}

/*
25      5       5       5       1
------------------------------
5
*/
