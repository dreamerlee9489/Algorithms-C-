/**
 * @file generate-parentheses.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 22. 括号生成
 * @version 0.1
 * @date 2022-07-23
 * @link https://leetcode.cn/problems/generate-parentheses/
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>
#include <string>

 /**
  * 要生成所有有效的括号组合，可以使用回溯法。回溯法是一种通过探索所有可能的候选解来找出所有解的算法。如果一个候选解最终不是一个有效的解，回溯法会丢弃它，并且回溯到之前的步骤，尝试另一种可能的解。
  * 解题技巧总结：
  * 使用递归函数，维护当前字符串current和两个计数器：open表示已放置的左括号数量，close表示已放置的右括号数量。
  * 递归的基本情况是字符串current的长度为2 * n，这时候将current添加到结果集中。
  * 在递归过程中，如果open小于n，可以放置一个左括号。我们添加一个左括号，并增加open的计数，然后继续递归。
  * 如果close小于open，可以放置一个右括号。我们添加一个右括号，并增加close的计数，然后继续递归。
  * 使用深度优先搜索的策略来遍历所有可能的情况。
  *
  */
class Solution {
public:
	std::vector<std::string> generateParenthesis(int n) {
		std::vector<std::string> result;
		backtrack(result, "", 0, 0, n);
		return result;
	}

	void backtrack(std::vector<std::string>& result, std::string current, int open, int close, int max) {
		if (current.length() == max * 2) {
			result.push_back(current);
			return;
		}

		if (open < max) {
			backtrack(result, current + "(", open + 1, close, max);
		}

		if (close < open) {
			backtrack(result, current + ")", open, close + 1, max);
		}
	}
};