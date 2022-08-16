#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int *getNext2(string pattern) {
  int *pNext = new int[pattern.size()]{-1};
  int i = 0, n = -1, iMax = pattern.size() - 1;
  while (i < iMax) {
    if (n < 0 || pattern[i] == pattern[n]) {
      ++i;
      ++n;
      if (pattern[i] == pattern[n])
        pNext[i] = pNext[n];
      else
        pNext[i] = n;
    } else
      n = pNext[n];
  }
  return pNext;
}

int *getNext1(string pattern) {
  int *pNext = new int[pattern.size()]{-1};
  int i = 0, n = -1, iMax = pattern.size() - 1;
  while (i < iMax) {
    if (n < 0 || pattern[i] == pattern[n])
      pNext[++i] = ++n;
    else
      n = pNext[n];
  }
  return pNext;
}

/**
 * @brief KMP字符串匹配
 * @date 2022-07-17
 * @param text
 * @param pattern
 * @return int
 */
int kmp(string text, string pattern) {
  if (text.empty() || pattern.empty())
    return -1;
  int tLen = text.size();
  int pLen = pattern.size();
  if (tLen < pLen)
    return -1;
  int *pNext = getNext2(pattern);
  int pi = 0, ti = 0, delta = tLen - pLen;
  while (pi < pLen && ti - pi <= delta) {
    if (pi < 0 || text[ti] == pattern[pi]) {
      ti++;
      pi++;
    } else {
      pi = pNext[pi];
    }
  }
  delete pNext;
  return pi == pLen ? (ti - pi) : -1;
}

int main(int argc, char const *argv[]) {
  assert(kmp("Hello World", "H") == 0);
  assert(kmp("Hello World", "d") == 10);
  assert(kmp("Hello World", "or") == 7);
  assert(kmp("Hello World", "abc") == -1);
  cout << "Execution continues past all asserts.";
  return 0;
}
