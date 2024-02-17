/**
 * @file open-the-lock.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 752. 打开转盘锁
 * @version 0.1
 * @date 2024-02-17
 * @link https://leetcode.cn/problems/open-the-lock/description/
 * @copyright Copyright (c) 2024
 *
 */
#include <vector>
#include <string>
#include <queue>
#include <unordered_set>
using namespace std;

class Solution {
public:
	int openLock(vector<string>& deadends, string target) {
		string start = "0000";
		queue<string> q({ start });
		unordered_set<string> vistied({ start });
		unordered_set<string> dead(deadends.begin(), deadends.end());
		if (dead.count(start)) return -1;
		if (start == target) return 0;

		int steps = 0;
		while (!q.empty()) {
			++steps;
			int n = q.size();
			for (int i = 0; i < n; i++) {	//处理当前层的所有元素
				string curr = q.front();
				q.pop();
				for (int j = 0; j < 4; j++) {
					for (int k = -1; k < 2; k += 2) {
						string next = curr;
						next[j] = (next[j] - '0' + k + 10) % 10 + '0';
						if (next == target) return steps;
						if (!dead.count(next) && !vistied.count(next)) {
							q.push(next);
							vistied.insert(next);
						}
					}
				}
			}
		}
		return -1;
	}
};