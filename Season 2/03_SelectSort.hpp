#ifndef SELECT_SORT_HPP
#define SELECT_SORT_HPP

#include "./01_ISort.hpp"

namespace app {
	/**
	 * @brief 选择排序
	 * @date 2022-04-27
	 * @tparam T
	 */
	template <typename T> class SelectSort : public ISort<T> {
		void sort_algorithm() override {
			for (size_t end = this->_size - 1; end > 0; --end) {
				size_t max = 0;
				for (size_t beg = 1; beg <= end; ++beg)
					if (this->compare(max, beg) < 0)
						max = beg;
				this->swap(max, end);
			}
		}

	public:
		SelectSort() = default;

		~SelectSort() = default;
	};
} // namespace app

#endif /* SELECT_SORT_HPP */
