#ifndef DISJOINT_SET_HPP
#define DISJOINT_SET_HPP

#include <iostream>
#include <unordered_map>

using namespace std;

namespace app {
	/**
	 * @brief 并查集
	 * @date 2022-04-29
	 * @tparam K
	 */
	template <typename K> class DisjointSet {
		template <typename _K> struct Node {
			_K* _key = nullptr;
			Node<_K>* _parent = this;
			size_t _rank = 1;

			Node(_K* key) { _key = key; }

			~Node() { delete _key; }
		};

		unordered_map<K, Node<K>*>* _map = nullptr;

		/**
		 * @brief 返回key所在集合的根节点
		 * @param key
		 * @return Node<K>*
		 * @remark 路径减半: 路径上每隔一个结点指向其祖父结点, 降低树高
		 */
		Node<K>* find_root(K* key) {
			typename unordered_map<K, Node<K>*>::iterator iter = _map->find(*key);
			if (iter == _map->end())
				return nullptr;
			while (*iter->second->_key != *iter->second->_parent->_key) {
				iter->second->_parent = iter->second->_parent->_parent;
				iter->second = iter->second->_parent;
			}
			return iter->second;
		}

	public:
		DisjointSet() { _map = new unordered_map<K, Node<K>*>(); }

		~DisjointSet() { delete _map; }

		void add(K* key) { _map->emplace(*key, new Node<K>(key)); }

		K* root_key(K* key) {
			Node<K>* root = find_root(key);
			return root != nullptr ? root->_key : nullptr;
		}

		/**
		 * @brief fromKey的根结点指向toKey的根结点
		 * @param fromKey
		 * @param toKey
		 */
		void union_set(K* fromKey, K* toKey) {
			Node<K>* fromRoot = find_root(fromKey);
			Node<K>* toRoot = find_root(toKey);
			if (fromRoot != nullptr && toRoot != nullptr) {
				// 矮树嫁接到高树, 平衡高度
				if (*fromRoot->_key != *toRoot->_key) {
					if (fromRoot->_rank < toRoot->_rank)
						fromRoot->_parent = toRoot;
					else if (fromRoot->_rank > toRoot->_rank)
						toRoot->_parent = fromRoot;
					else {
						fromRoot->_parent = toRoot;
						toRoot->_rank += 1;
					}
				}
			}
		}

		bool is_same(K* key1, K* key2) { return *root_key(key1) == *root_key(key2); }
	};
} // namespace app

#endif /* DISJOINT_SET_HPP */
