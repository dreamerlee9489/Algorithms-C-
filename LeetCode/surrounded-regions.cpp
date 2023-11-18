/**
 * @file surrounded-regions.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 130. 被围绕的区域
 * @version 0.1
 * @date 2022-08-10
 * @link https://leetcode.cn/problems/surrounded-regions/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>

using namespace std;

class Solution {
	void dfs(int r, int c, vector<vector<char>>& board) {
		if (r < 0 || r >= board.size() || c < 0 || c >= board[0].size() ||
			board[r][c] != 'O')
			return;
		board[r][c] = 'A';
		dfs(r - 1, c, board);
		dfs(r + 1, c, board);
		dfs(r, c - 1, board);
		dfs(r, c + 1, board);
	}

public:
	void solve(vector<vector<char>>& board) {
		for (int r = 0; r < board.size(); r++) {
			dfs(r, 0, board);
			dfs(r, board[0].size() - 1, board);
		}
		for (int c = 0; c < board[0].size(); c++) {
			dfs(0, c, board);
			dfs(board.size() - 1, c, board);
		}
		for (int r = 0; r < board.size(); r++) {
			for (int c = 0; c < board[0].size(); c++) {
				if (board[r][c] == 'A')
					board[r][c] = 'O';
				else if (board[r][c] == 'O')
					board[r][c] = 'X';
			}
		}
	}
};