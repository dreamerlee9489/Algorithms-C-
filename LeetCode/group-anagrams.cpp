/**
 * @file group-anagrams.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 49. 字母异位词分组
 * @version 0.1
 * @date 2022-08-12
 * @link https://leetcode.cn/problems/group-anagrams/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
  vector<vector<string>> groupAnagrams(vector<string> &strs) {
    vector<vector<string>> _res;
    unordered_multiset<char> _set;
    unordered_map<string, vector<string>> _map;
    for (size_t i = 0; i < strs.size(); i++) {
      string _hash = "";
      for (size_t j = 0; j < strs[i].size(); j++)
        _set.emplace(strs[i][j]);
      // 利用异位词字母数相同生成唯一哈希值
      for (int k = 0; k < 26; k++)
        _hash += '#' + _set.count('a' + k);
      _set.clear();
      _map[_hash].emplace_back(strs[i]);
    }
    for (auto p : _map)
      _res.emplace_back(p.second);
    return _res;
  }
};