/**
 * @file number-of-islands.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 200. 岛屿数量
 * @version 0.1
 * @date 2022-08-04
 * @link https://leetcode.cn/problems/number-of-islands/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>
#include <vector>

using namespace std;

class Solution {
  void dfs(vector<vector<char>> &grid, int r, int c) {
    grid[r][c] = '0';
    if (r - 1 >= 0 && grid[r - 1][c] == '1')
      dfs(grid, r - 1, c);
    if (r + 1 < grid.size() && grid[r + 1][c] == '1')
      dfs(grid, r + 1, c);
    if (c - 1 >= 0 && grid[r][c - 1] == '1')
      dfs(grid, r, c - 1);
    if (c + 1 < grid[0].size() && grid[r][c + 1] == '1')
      dfs(grid, r, c + 1);
  }

public:
  int numIslands(vector<vector<char>> &grid) {
    if (grid.empty())
      return 0;
    int num = 0;
    for (int r = 0; r < grid.size(); r++) {
      for (int c = 0; c < grid[0].size(); c++) {
        if (grid[r][c] == '1') {
          ++num;
          dfs(grid, r, c);
        }
      }
    }
    return num;
  }
};

int main(int argc, char const *argv[]) {
  vector<vector<char>> grid1 = {{'1', '1', '1', '1', '0'},
                                {'1', '1', '0', '1', '0'},
                                {'1', '1', '0', '0', '0'},
                                {'0', '0', '0', '0', '0'}};
  cout << Solution().numIslands(grid1) << "\n";
  vector<vector<char>> grid2 = {{'1', '1', '0', '0', '0'},
                                {'1', '1', '0', '0', '0'},
                                {'0', '0', '1', '0', '0'},
                                {'0', '0', '0', '1', '1'}};
  cout << Solution().numIslands(grid2) << "\n";
  return 0;
}
