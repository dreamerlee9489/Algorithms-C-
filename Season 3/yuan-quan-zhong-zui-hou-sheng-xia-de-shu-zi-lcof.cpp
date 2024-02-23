/**
 * @file yuan-quan-zhong-zui-hou-sheng-xia-de-shu-zi-lcof.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 剑指 Offer 62. 圆圈中最后剩下的数字
 * @version 0.1
 * @date 2022-07-24
 * @link https://leetcode.cn/problems/yuan-quan-zhong-zui-hou-sheng-xia-de-shu-zi-lcof/
 * @copyright Copyright (c) 2022
 *
 */

 /**
  * 解题技巧总结：
  * 这个问题是经典的约瑟夫问题（Josephus Problem）的一个变体。为了找到最后留下的成员编号，我们可以采用递归或迭代的方法来解决它。关键在于理解这个问题的递推性质：
  * 当我们从num个人中移除一个人后，我们就剩下了一个新的问题规模——num-1个人的约瑟夫问题。
  * 但是新问题的起始编号会发生改变，因为我们是从下一个成员开始计数的。
  * 这个问题的递推公式是：f(n, m) = (f(n - 1, m) + m) % n，其中f(n, m)为n个人报数到m时的胜者编号，f(1, m) = 0，因为当只有一个人时，他就是胜者。
  * 递推的理解方法是：考虑n-1个人时的情况，那时的胜者是f(n - 1, m)，当我们再加入之前被移除的那个人时，因为每次报数是从下一个人开始的，所以胜者实际上会向后移动m个位置，但是因为总人数是n，所以我们对n取模，得到了n个人时的胜者编号。
  *
  */
class Solution {
public:
	int iceBreakingGame(int num, int target) {
		int lastPerson = 0; // 当只有1个人时，胜者的编号是0
		for (int i = 2; i <= num; ++i) {
			lastPerson = (lastPerson + target) % i;
		}
		// 因为编号从0开始，所以不需要加1
		return lastPerson;
	}
};