/**
 * @file course-schedule.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 207. 课程表
 * @version 0.1
 * @date 2022-08-13
 * @link https://leetcode.cn/problems/course-schedule/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Solution {
  vector<vector<int>> edges;
  vector<int> visited;
  bool valid = true;

  void dfs(int index) {
    visited[index] = -1; // 搜索中
    for (int i : edges[index]) {
      if (visited[i] == -1) { // 尚未搜索该结点，继续搜索
        valid = false;
        return;
      } else if (visited[i] == 0) { // 正在搜索该结点，证明有环
        dfs(i);
        if (!valid)
          return;
      }
    }
    visited[index] = 1; // 搜索结束
  }

public:
  bool canFinish(int numCourses, vector<vector<int>> &prerequisites) {
    edges = vector<vector<int>>(numCourses);
    visited = vector<int>(numCourses);
    for (auto &vec : prerequisites)
      edges[vec[1]].emplace_back(vec[0]);
    for (int i = 0; i < numCourses; i++) {
      if (visited[i] == 0)
        dfs(i);
      if (!valid)
        break;
    }
    return valid;
  }
};

int main(int argc, char const *argv[]) {
  vector<vector<int>> prerequisites1 = {{0, 1}, {0, 2}, {1, 2}};
  cout << Solution().canFinish(3, prerequisites1) << "\n";
  vector<vector<int>> prerequisites2 = {{1, 0}, {2, 1}, {3, 2}, {1, 3}};
  cout << Solution().canFinish(4, prerequisites2) << "\n";
  vector<vector<int>> prerequisites3 = {{1, 0}, {0, 3}, {0, 2}, {3, 2},
                                        {2, 5}, {4, 5}, {5, 6}, {2, 4}};
  cout << Solution().canFinish(7, prerequisites3) << "\n";
  return 0;
}
