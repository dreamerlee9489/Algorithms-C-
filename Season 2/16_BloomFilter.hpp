#ifndef BLOOM_FILTER_HPP
#define BLOOM_FILTER_HPP

#include <cmath>
#include <iostream>
#include <memory>

using namespace std;

namespace app {
/**
 * @brief 布隆过滤器
 * @date 2022-07-10
 * @tparam T
 */
template <typename T> class BloomFilter {
  size_t _bitSize = 0;   //二进制向量的长度
  size_t _hashSize = 0;  //哈希函数个数
  long *_bits = nullptr; //二进制向量
  bool set(size_t index) {
    long value = _bits[index / sizeof(long)];
    int bitValue = 1 << (index % sizeof(long));
    _bits[index / sizeof(long)] = value | bitValue;
    return (value & bitValue) == 0;
  }

  bool get(int index) {
    long value = _bits[index / sizeof(long)];
    return (value & (1 << (index % sizeof(long)))) != 0;
  }

  void checkNull(shared_ptr<T> value) {
    if (value == nullptr)
      throw invalid_argument("value must not be nullptr.");
  }

public:
  /**
   * @brief Construct a new Bloom Filter object
   * @param n 数据规模
   * @param p 误判率
   */
  BloomFilter(int n, double p) {
    if (n <= 0 || p <= 0 || p >= 1)
      throw domain_error("wrong n or p");
    double ln2 = log(2);
    _bitSize = (int)(-n * log(p) / pow(ln2, 2));
    _hashSize = (int)(_bitSize * ln2 / n);
    _bits = new long[(_bitSize + sizeof(long) - 1) / sizeof(long)]{};
  }

  ~BloomFilter() { delete _bits; }

  bool add(shared_ptr<T> value) {
    checkNull(value);
    size_t hash = std::hash<T>()(*value);
    bool result = false;
    for (size_t i = 0; i < _hashSize; i++) {
      size_t index = hash % _bitSize;
      if (set(index))
        result = true;
    }
    return result;
  }

  bool contains(shared_ptr<T> value) {
    checkNull(value);
    size_t hash = std::hash<T>()(*value);
    for (size_t i = 0; i < _hashSize; i++) {
      size_t index = hash % _bitSize;
      if (!get(index))
        return false;
    }
    return true;
  }
};
} // namespace app

#endif /* BLOOM_FILTER_HPP */
