#include <cassert>
#include <iostream>
#include <string>

using namespace std;

/**
 * @brief 暴力字符串匹配
 * @date 2022-07-17
 * @param text
 * @param pattern
 * @return int
 */
int bruteForce1(string text, string pattern) {
    if (text.empty() || pattern.empty())
        return -1;
    size_t tLen = text.size();
    size_t pLen = pattern.size();
    if (tLen < pLen)
        return -1;
    size_t pi = 0, ti = 0;
    while (pi < pLen && ti < tLen) {
        if (text[ti] == pattern[pi]) {
            ti++;
            pi++;
        } else {
            ti -= pi - 1;
            pi = 0;
        }
    }
    return pi == pLen ? (ti - pi) : -1;
}

/**
 * @brief 暴力字符串匹配优化
 * @date 2022-07-17
 * @param text
 * @param pattern
 * @return int
 */
int bruteForce2(string text, string pattern) {
    if (text.empty() || pattern.empty())
        return -1;
    size_t tLen = text.size();
    size_t pLen = pattern.size();
    if (tLen < pLen)
        return -1;
    int tMax = tLen - pLen;
    for (int ti = 0; ti <= tMax; ti++) {
        int pi = 0;
        for (; pi < pLen; pi++) {
            if (text[ti + pi] != pattern[pi])
                break;
        }
        if (pi == pLen)
            return ti;
    }
    return -1;
}

int main(int argc, char const *argv[]) {
    assert(bruteForce1("Hello World", "H") == 0);
    assert(bruteForce1("Hello World", "d") == 10);
    assert(bruteForce1("Hello World", "or") == 7);
    assert(bruteForce1("Hello World", "abc") == -1);
    assert(bruteForce2("Hello World", "H") == 0);
    assert(bruteForce2("Hello World", "d") == 10);
    assert(bruteForce2("Hello World", "or") == 7);
    assert(bruteForce2("Hello World", "abc") == -1);
    cout << "Execution continues past all asserts.";
    return 0;
}