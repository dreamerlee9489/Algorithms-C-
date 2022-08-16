/**
 * @file valid-sudoku.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 36. 有效的数独
 * @version 0.1
 * @date 2022-08-12
 * @link https://leetcode.cn/problems/valid-sudoku/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
  unordered_set<int> _set;

  bool check3X3(int r, int c, vector<vector<char>> &board) {
    int beginRow = 3 * r, beginCol = 3 * c;
    for (int row = beginRow; row < beginRow + 3; row++) {
      for (int col = beginCol; col < beginCol + 3; col++) {
        if (board[row][col] != '.') {
          if (_set.find(board[row][col]) != _set.end())
            return false;
          _set.emplace(board[row][col]);
        }
      }
    }
    _set.clear();
    return true;
  }

public:
  bool isValidSudoku(vector<vector<char>> &board) {
    for (int r = 0; r < 9; r++) {
      for (int c = 0; c < 9; c++) {
        if (board[r][c] != '.') {
          if (_set.find(board[r][c]) != _set.end())
            return false;
          _set.emplace(board[r][c]);
        }
      }
      _set.clear();
    }
    for (int c = 0; c < 9; c++) {
      for (int r = 0; r < 9; r++) {
        if (board[r][c] != '.') {
          if (_set.find(board[r][c]) != _set.end())
            return false;
          _set.emplace(board[r][c]);
        }
      }
      _set.clear();
    }
    for (int r = 0; r < 3; r++) {
      for (int c = 0; c < 3; c++) {
        if (!check3X3(r, c, board))
          return false;
      }
    }
    return true;
  }
};