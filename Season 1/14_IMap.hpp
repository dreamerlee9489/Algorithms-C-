#ifndef IMAP_HPP
#define IMAP_HPP

#include <memory>
#include <queue>
#include <iostream>
#include "./IString.hpp"

using namespace std;

namespace app {
    /**
     * @brief 映射基类
     * @date 2022-04-19
     * @tparam K
     * @tparam V
     */
    template<typename K, typename V>
    class IMap {
    protected:
        using TraverseFunc = bool (*)(shared_ptr <K> key, shared_ptr <V> value);
        using Comparator = int (*)(shared_ptr <K> a, shared_ptr <K> b);

    public:
        IMap() = default;

        virtual ~IMap() = default;

        virtual size_t size() const = 0;

        virtual bool is_empty() const = 0;

        virtual bool containspKey(shared_ptr <K> key) const = 0;

        virtual bool containspValue(shared_ptr <V> value) const = 0;

        virtual shared_ptr <V> getpValue(shared_ptr <K> key) const = 0;

        virtual shared_ptr <V> add(shared_ptr <K> key, shared_ptr <V> value) = 0;

        virtual shared_ptr <V> remove(shared_ptr <K> key) = 0;

        virtual void clear() = 0;
    };
} // namespace app

#endif /* IMAP_HPP */
