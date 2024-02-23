/**
 * @file powx-n.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 50. Pow(x, n)
 * @version 0.1
 * @date 2022-07-24
 * @link https://leetcode.cn/problems/powx-n/
 * @copyright Copyright (c) 2022
 *
 */

 /**
  * 解题技巧总结：
  * 要实现幂函数pow(x, n)，最直接的方法是进行n次乘法，但这种方法的时间复杂度是O(n)，效率低下。更高效的方法是使用“快速幂”算法，也称为“二分幂”算法，其核心思想是利用幂的性质来减少计算量。
  * 以下是实现快速幂算法的几个重要步骤：
  * 递归实现：快速幂算法可以使用递归来实现。当我们要计算x^n时，可以根据n的奇偶性进行分治处理。如果n是偶数，那么x^n = (x^(n/2))^2；如果n是奇数，则x^n = x * (x^(n/2))^2。
  * 迭代实现：虽然递归实现较为直观，但递归深度可能会很大，导致栈溢出。因此，使用迭代的方式也是一个不错的选择。迭代实现可以借助位运算来优化。
  * 处理负幂：如果n是负数，可以先计算正幂，然后取其倒数。
  * 注意边界情况：需要考虑n为0或x为0等边界情况。
  * 时间复杂度：快速幂算法的时间复杂度为O(log n)，因为每次都将问题规模缩小一半。
  *
  */
class Solution {
public:
	double myPow(double x, int n) {
		// 处理n为负数的情况
		long long N = n;
		if (N < 0) {
			x = 1 / x;
			N = -N;
		}
		double ans = 1;
		double current_product = x;
		for (long long i = N; i; i /= 2) {
			if (i % 2 == 1) {
				ans = ans * current_product;
			}
			current_product = current_product * current_product;
		}
		return ans;
	}
};
