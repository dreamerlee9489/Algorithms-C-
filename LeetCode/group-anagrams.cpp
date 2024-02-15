/**
 * @file group-anagrams.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 49. 字母异位词分组
 * @version 0.1
 * @date 2022-08-12
 * @link https://leetcode.cn/problems/group-anagrams/
 * @copyright Copyright (c) 2022
 *
 */
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
	vector<vector<string>> groupAnagrams(vector<string>& strs) {
		vector<vector<string>> res;
		unordered_map<string, vector<string>> groups;
		for (int i = 0; i < strs.size(); i++) {
			string key = strs[i];
			sort(key.begin(), key.end());
			groups[key].emplace_back(strs[i]);
		}
		for (auto& p : groups)
			res.emplace_back(p.second);
		return res;
	}
};