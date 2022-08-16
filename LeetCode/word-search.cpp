/**
 * @file word-search.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 79. 单词搜索
 * @version 0.1
 * @date 2022-08-07
 * @link https://leetcode.cn/problems/word-search/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
  bool check(int r, int c, int k, vector<vector<bool>> &visited,
             vector<vector<char>> &board, string &word) {
    if (board[r][c] != word[k])
      return false;
    if (k == word.size() - 1)
      return true;
    visited[r][c] = true;
    bool res = false;
    vector<pair<int, int>> dirs = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    for (int i = 0; i < dirs.size(); i++) {
      int newR = r + dirs[i].first;
      int newC = c + dirs[i].second;
      if (newR >= 0 && newR < board.size() && newC >= 0 &&
          newC < board[0].size())
        if (!visited[newR][newC])
          if ((res = check(newR, newC, k + 1, visited, board, word)))
            break;
    }
    visited[r][c] = false;
    return res;
  }

public:
  bool exist(vector<vector<char>> &board, string word) {
    vector<vector<bool>> visited =
        vector<vector<bool>>(board.size(), vector<bool>(board[0].size()));
    for (int r = 0; r < board.size(); r++)
      for (int c = 0; c < board[0].size(); c++)
        if (check(r, c, 0, visited, board, word))
          return true;
    return false;
  }
};

int main(int argc, char const *argv[]) {
  vector<vector<char>> board = {
      {'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
  cout << Solution().exist(board, "ABCCED");
  return 0;
}
