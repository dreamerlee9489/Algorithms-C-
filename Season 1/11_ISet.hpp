#ifndef ISET_HPP
#define ISET_HPP

#include <memory>

using namespace std;

namespace app {
	/**
	 * @brief 集合基类
	 * @date 2022-04-17
	 * @tparam K
	 */
	template <typename K> class ISet {
	protected:
		using Comparator = int (*)(shared_ptr<K> a, shared_ptr<K> b);
		using TraverseFunc = bool (*)(shared_ptr<K> key, shared_ptr<bool> value);

	protected:
		ISet() = default;

		virtual ~ISet() = default;

		virtual size_t size() = 0;

		virtual bool is_empty() = 0;

		virtual bool contains(shared_ptr<K> data) = 0;

		virtual void add(shared_ptr<K> data) = 0;

		virtual void remove(shared_ptr<K> data) = 0;

		virtual void clear() = 0;
	};
} // namespace app

#endif /* ISET_HPP */
