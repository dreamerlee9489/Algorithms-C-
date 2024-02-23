/**
 * @file letter-combinations-of-a-phone-number.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 17. 电话号码的字母组合
 * @version 0.1
 * @date 2022-07-23
 * @link https://leetcode.cn/problems/letter-combinations-of-a-phone-number/
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

/**
 * 为了解决这个问题，可以使用回溯算法来生成所有可能的字母组合。回溯算法是一种通过尝试分步的方式去解决问题的算法。在某一步选择一个可能的选项后，进入下一步，如果发现当前选择和后续的选择不能达到最终的解答，就回退到上一步重新选择，这个过程可以看作是一个不断在决策树上进行深度优先搜索的过程。
 * 解题技巧总结：
 * 将数字和可能的字母映射存储在哈希表或数组中。
 * 使用回溯算法逐步构建答案。
 * 从输入的数字字符串的第一个数字开始，对应到其可能的字母，然后对每个可能的字母进行搜索，接着进入下一数字对应的所有可能字母。
 * 当递归函数的深度等于输入数字字符串的长度时，说明已经得到了一个完整的字母组合，可以将其添加到结果集中。
 * 在回溯过程中，每当完成一个字母组合的探索，需要撤销最后一个字母的选择，继续尝试当前数字对应的其他字母。
 *
 */
class Solution {
public:
	vector<string> letterCombinations(string digits) {
		vector<string> result;
		if (digits.empty()) return result; // 处理空字符串的特殊情况

		// 建立数字到字母的映射
		unordered_map<char, string> phoneMap = {
			{'2', "abc"},
			{'3', "def"},
			{'4', "ghi"},
			{'5', "jkl"},
			{'6', "mno"},
			{'7', "pqrs"},
			{'8', "tuv"},
			{'9', "wxyz"}
		};

		// 用于存储当前的组合
		string currentCombination;
		backtrack(result, phoneMap, digits, 0, currentCombination);
		return result;
	}

private:
	void backtrack(vector<string>& result, const unordered_map<char, string>& phoneMap,
		const string& digits, int index, string& currentCombination) {
		// 如果当前组合的长度等于输入的数字长度，则添加到结果中
		if (index == digits.length()) {
			result.push_back(currentCombination);
			return;
		}

		// 获取当前数字对应的所有可能字母
		char digit = digits[index];
		const string& letters = phoneMap.at(digit);

		// 遍历这些字母
		for (char letter : letters) {
			currentCombination.push_back(letter); // 选择当前字母
			backtrack(result, phoneMap, digits, index + 1, currentCombination); // 进行下一步搜索
			currentCombination.pop_back(); // 回溯，撤销选择
		}
	}
};