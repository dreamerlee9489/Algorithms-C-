#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

vector<int> test2(vector<int>& a, vector<int>& b)
{
    vector<int> res;
    set<int> s;
    for (int& i : a)
        s.emplace(i);
    for (int& i : b)
    {
        if (s.find(i) != s.end())
        {
            res.emplace_back(i);
            s.erase(i);
        }
    }
    sort(res.begin(), res.end());
    return res;
}

int main()
{
    vector<int> a = { 1, 2, 2, 3, 4, 5 };
    vector<int> b = { 2, 4, 1, 2, 3 };
    auto res = test2(a, b);
    for (int i : res)
        cout << i << " ";
    return 0;
}
