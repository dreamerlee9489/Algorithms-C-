/**
 * @file merge-intervals.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 56. 合并区间
 * @version 0.1
 * @date 2022-08-05
 * @link https://leetcode.cn/problems/merge-intervals/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

class Solution {
  struct Cmp {
    bool operator()(vector<int> &a, vector<int> &b) const {
      return a[0] < b[0];
    }
  };

public:
  vector<vector<int>> merge(vector<vector<int>> &intervals) {
    vector<vector<int>> res;
    sort(intervals.begin(), intervals.end(),
         [](vector<int> &a, vector<int> &b) { return a[0] < b[0]; });
    priority_queue<vector<int>, vector<vector<int>>, Cmp> que;
    que.push(intervals[0]);
    for (int i = 1; i < intervals.size(); i++) {
      vector<int> top = que.top();
      if (intervals[i][0] > top[1])
        que.push({intervals[i][0], intervals[i][1]});
      else {
        que.pop();
        que.push({top[0], max(top[1], intervals[i][1])});
      }
    }
    while (!que.empty()) {
      res.emplace_back(que.top());
      que.pop();
    }
    reverse(res.begin(), res.end());
    return res;
  }
};

int main(int argc, char const *argv[]) {
  vector<vector<int>> intervals1 = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};
  auto res1 = Solution().merge(intervals1);
  vector<vector<int>> intervals2 = {{1, 4}, {4, 5}};
  auto res2 = Solution().merge(intervals2);
  vector<vector<int>> intervals3 = {{1, 9},   {2, 5}, {19, 20}, {10, 11},
                                    {12, 20}, {0, 3}, {0, 1},   {0, 2}};
  auto res3 = Solution().merge(intervals3);
  return 0;
}
