/**
 * @file top-k-frequent-elements.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 347. 前 K 个高频元素
 * @version 0.1
 * @date 2022-08-15
 * @link https://leetcode.cn/problems/top-k-frequent-elements/
 * @copyright Copyright (c) 2022
 *
 */
#include <list>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
	vector<int> topKFrequent(vector<int>& nums, int k) {
		unordered_map<int, int> _map;
		list<pair<int, int>> _list;
		vector<int> _res;
		for (int i = 0; i < nums.size(); i++)
			++_map[nums[i]];
		for (auto& p : _map)
			_list.emplace_back(move(p));
		_list.sort([](pair<int, int>& a, pair<int, int>& b) {
			return a.second > b.second;
			});
		for (int i = 0; i < k; i++) {
			_res.emplace_back(_list.front().first);
			_list.pop_front();
		}
		return _res;
	}
};