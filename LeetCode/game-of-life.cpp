/**
 * @file game-of-life.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 289. 生命游戏
 * @version 0.1
 * @date 2022-08-06
 * @link https://leetcode.cn/problems/game-of-life/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>

using namespace std;

class Solution {
	int changeState(int row, int col, vector<vector<int>>& board) {
		int live = 0;
		for (int r = row - 1; r <= row + 1; r++) {
			for (int c = col - 1; c <= col + 1; c++) {
				if (r < 0 || r >= board.size())
					continue;
				if (c < 0 || c >= board[0].size())
					continue;
				if (r == row && c == col)
					continue;
				if (board[r][c] == 1)
					if (++live > 3)
						break;
			}
		}
		if (board[row][col] == 0)
			return live == 3 ? 1 : 0;
		else
			return (live < 2 || live > 3) ? 0 : 1;
	}

public:
	void gameOfLife(vector<vector<int>>& board) {
		vector<vector<int>> temp(board);
		for (int r = 0; r < board.size(); r++)
			for (int c = 0; c < board[0].size(); c++)
				temp[r][c] = changeState(r, c, board);
		board = move(temp);
	}
};

int main(int argc, char const* argv[]) {
	vector<vector<int>> board = { {0, 1, 0}, {0, 0, 1}, {1, 1, 1}, {0, 0, 0} };
	Solution().gameOfLife(board);
	return 0;
}
