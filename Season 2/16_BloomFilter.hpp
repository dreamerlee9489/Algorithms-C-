#ifndef BLOOM_FILTER_HPP
#define BLOOM_FILTER_HPP

#include <memory>
#include <cmath>
#include <iostream>

using namespace std;

namespace app {
    /**
     * @brief 布隆过滤器
     * @date 2022-07-10
     * @tparam T
     */
    template<typename T>
    class BloomFilter {
        size_t mBitSize = 0;   //二进制向量的长度
        size_t mHashSize = 0;  //哈希函数个数
        long *pBits = nullptr; //二进制向量
        bool set(size_t index) {
            long value = pBits[index / sizeof(long)];
            int bitValue = 1 << (index % sizeof(long));
            pBits[index / sizeof(long)] = value | bitValue;
            return (value & bitValue) == 0;
        }

        bool get(int index) {
            long value = pBits[index / sizeof(long)];
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
            mBitSize = (int) (-n * log(p) / pow(ln2, 2));
            mHashSize = (int) (mBitSize * ln2 / n);
            pBits = new long[(mBitSize + sizeof(long) - 1) / sizeof(long)]{};
        }

        ~BloomFilter() { delete pBits; }

        bool add(shared_ptr<T> value) {
            checkNull(value);
            size_t hash = std::hash<T>()(*value);
            bool result = false;
            for (size_t i = 0; i < mHashSize; i++) {
                size_t index = hash % mBitSize;
                if (set(index))
                    result = true;
            }
            return result;
        }

        bool contains(shared_ptr<T> value) {
            checkNull(value);
            size_t hash = std::hash<T>()(*value);
            for (size_t i = 0; i < mHashSize; i++) {
                size_t index = hash % mBitSize;
                if (!get(index))
                    return false;
            }
            return true;
        }
    };
} // namespace app

#endif /* BLOOM_FILTER_HPP */
