#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

#include "./17_BinaryHeap.hpp"

namespace app {
	/**
	 * @brief 优先级队列
	 * @date 2022-04-22
	 * @tparam T
	 */
	template <typename T> class PriorityQueue {
		using Comparator = int (*)(shared_ptr<T> a, shared_ptr<T> b);

		BinaryHeap<T>* _heap = nullptr;

	public:
		PriorityQueue(Comparator comparator = nullptr) {
			_heap = new BinaryHeap<T>(comparator);
		}

		~PriorityQueue() { delete _heap; }

		size_t size() const { return _heap->size(); }

		bool is_empty() const { return _heap->is_empty(); }

		void clear() { _heap->clear(); }

		void push(shared_ptr<T> data) { _heap->add(data); }

		shared_ptr<T> pop() { return _heap->remove(); }

		shared_ptr<T> front() const { return _heap->get(); }
	};
} // namespace app

#endif /* PRIORITY_QUEUE_HPP */
