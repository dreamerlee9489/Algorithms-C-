/**
 * @file design-tic-tac-toe.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 348. 设计井字棋
 * @version 0.1
 * @date 2022-08-15
 * @link https://leetcode.cn/problems/design-tic-tac-toe/
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>

using namespace std;

class TicTacToe {
	vector<vector<char>> board;

	bool checkWin(int row, int col) {
		char ch = board[row][col];
		bool res1 = true, res2 = true;
		int res3 = -1;
		for (int r = 0; r < board.size(); r++) {
			if (board[r][col] != ch) {
				res1 = false;
				break;
			}
		}
		for (int c = 0; c < board.size(); c++) {
			if (board[row][c] != ch) {
				res2 = false;
				break;
			}
		}
		if (row == col) {
			res3 = 1;
			for (int r = 0; r < board.size(); r++) {
				if (board[r][r] != ch) {
					res3 = 0;
					break;
				}
			}
		}
		if (row + col + 1 == board.size()) {
			res3 = 1;
			for (int r = 0; r < board.size(); r++) {
				if (board[r][board.size() - r - 1] != ch) {
					res3 = 0;
					break;
				}
			}
		}
		return res1 || res2 || (res3 == -1 ? 0 : res3);
	}

public:
	TicTacToe(int n) { board = vector<vector<char>>(n, vector<char>(n, '#')); }

	int move(int row, int col, int player) {
		if (board[row][col] == '#') {
			board[row][col] = player == 1 ? 'X' : 'O';
			if (checkWin(row, col))
				return player;
		}
		return 0;
	}
};
