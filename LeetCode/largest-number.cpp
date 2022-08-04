/**
 * @file largest-number.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 179. 最大数
 * @version 0.1
 * @date 2022-08-01
 * @link https://leetcode.cn/problems/largest-number/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution
{
public:
    string largestNumber(vector<int>& nums) {
        string res;
        vector<string> strVec;
        for(int n : nums)
        {
            strVec.push_back(to_string(n));
        }
        sort(strVec.begin(), strVec.end(), 
            [](const string& lhs, const string& rhs)
            {
                // 长度相同的整数字符串可以直接比较大小
                return lhs + rhs > rhs + lhs;
            });
        for(string str : strVec)
        {
            res += str;
        }
        if(res[0] == '0')
        {
            // 如果0在字符串头部，则该字符串全为0
            return "0";
        }
        return res;
    }

    string largestNumber_my(vector<int> &nums)
    {
        if (nums[0] == 0 && nums[nums.size() - 1] == 0)
        {
            sort(nums.begin(), nums.end());
            if (nums[0] == 0 && nums[nums.size() - 1] == 0)
                return "0";
        }
        sort(nums.begin(), nums.end(), [](int a, int b)
             {
				if (a == b)
					return false;
				if (a < 10 && b < 10)
					return a > b;
				vector<int> digitsA, digitsB;
				while (a != 0)
				{
					digitsA.emplace_back(a % 10);
					a /= 10;
				}
				while (b != 0)
				{
					digitsB.emplace_back(b % 10);
					b /= 10;
				}
				int diff = 0, idxA = digitsA.size() - 1, idxB = digitsB.size() - 1;
				while (idxA >= 0 && idxB >= 0)
				{
					diff = digitsA[idxA] - digitsB[idxB];
					idxA--, idxB--;
					if (diff != 0)
						return diff > 0;
				}
				if (idxA >= 0)
				{
					idxB = digitsB.size() - 1;
					int step = digitsA.size();
					while (digitsB[idxB] == digitsA[idxA])
					{
						idxB = (idxB - 1 + digitsB.size()) % digitsB.size();
						idxA = (idxA - 1 + digitsA.size()) % digitsA.size();
						if (--step <= 0)
							return false;
					}
					return digitsA[idxA] > digitsB[idxB];
				}
				else if (idxB >= 0)
				{
					idxA = digitsA.size() - 1;
					int step = digitsB.size();
					while (digitsB[idxB] == digitsA[idxA])
					{
						idxB = (idxB - 1 + digitsB.size()) % digitsB.size();
						idxA = (idxA - 1 + digitsA.size()) % digitsA.size();
						if (--step <= 0)
							return false;
					}
					return digitsA[idxA] > digitsB[idxB];
				}
				return false; });
        string res;
        for (int i = 0; i < nums.size(); i++)
            res += to_string(nums[i]);
        return res;
    }
};

int main(int argc, char const *argv[])
{
    vector<int> nums1 = {432, 43243};
    cout << Solution().largestNumber(nums1) << "\n";
    for (size_t i = 0; i < nums1.size(); i++)
        cout << nums1[i] << " ";
    cout << "\n-------------------------\n";
    vector<int> nums2 = {3, 30, 34, 5, 9};
    cout << Solution().largestNumber(nums2) << "\n";
    for (size_t i = 0; i < nums2.size(); i++)
        cout << nums2[i] << " ";
    cout << "\n-------------------------\n";
    vector<int> nums3 = {10, 2};
    cout << Solution().largestNumber(nums3) << "\n";
    for (size_t i = 0; i < nums3.size(); i++)
        cout << nums3[i] << " ";
    cout << "\n-------------------------\n";
    vector<int> nums4 = {8308, 8308, 830};
    cout << Solution().largestNumber(nums4) << "\n";
    for (size_t i = 0; i < nums4.size(); i++)
        cout << nums4[i] << " ";
    cout << "\n-------------------------\n";
    vector<int> nums5 = {111311, 1113};
    cout << Solution().largestNumber(nums5) << "\n";
    for (size_t i = 0; i < nums5.size(); i++)
        cout << nums5[i] << " ";
    cout << "\n-------------------------\n";
    vector<int> nums6 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    cout << Solution().largestNumber(nums6) << "\n";
    for (size_t i = 0; i < nums6.size(); i++)
        cout << nums6[i] << " ";
    cout << "\n-------------------------\n";
    vector<int> nums7 = {0, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    cout << Solution().largestNumber(nums7) << "\n";
    for (size_t i = 0; i < nums7.size(); i++)
        cout << nums7[i] << " ";
    cout << "\n-------------------------\n";
    vector<int> nums8 = {0, 0, 0};
    cout << Solution().largestNumber(nums8) << "\n";
    for (size_t i = 0; i < nums8.size(); i++)
        cout << nums8[i] << " ";
    cout << "\n-------------------------\n";
    vector<int> nums9 = {3, 43, 48, 94, 85, 33, 64, 32, 63, 66};
    cout << Solution().largestNumber(nums9) << "\n";
    for (size_t i = 0; i < nums9.size(); i++)
        cout << nums9[i] << " ";
    cout << "\n-------------------------\n";
    const string a = "111311", b = "1113";
    if((a + b) > (b + a))
        cout << a + b << " > " << b + a << "\n";
    else
        cout << a + b << " < " << b + a << "\n";
    return 0;
}
