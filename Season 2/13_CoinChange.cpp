#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/**
 * @brief 零钱兑换
 * @remark 贪心策略
 * @date 2022-07-08
 * @param faces
 * @param money
 */
void coinChange(vector<int> coins, int amount) {
	sort(coins.begin(), coins.end());
	int count = 0, index = coins.size() - 1;
	while (index >= 0) {
		while (amount >= coins[index]) {
			cout << coins[index] << "\t";
			amount -= coins[index];
			count++;
		}
		index--;
	}
	cout << "\n------------------------------\n" << count;
}

int main(int argc, char const* argv[]) {
	coinChange(vector<int>({ 25, 20, 5, 1 }), 41);
	return 0;
}

/*
25      5       5       5       1
------------------------------
5
*/
