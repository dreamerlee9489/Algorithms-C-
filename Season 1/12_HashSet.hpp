#ifndef HASH_SET_HPP
#define HASH_SET_HPP

#include "./11_ISet.hpp"
#include "./15_HashMap.hpp"

namespace app {
/**
 * @brief 哈希集合
 * @date 2022-04-21
 * @tparam K
 */
template <typename K> class HashSet : public ISet<K> {
  HashMap<K, bool> *_map = nullptr;

public:
  HashSet(typename ISet<K>::Comparator comparator = nullptr) {
    _map = new HashMap<K, bool>(comparator);
  }

  ~HashSet() { delete _map; }

  size_t size() override { return _map->size(); }

  bool is_empty() override { return _map->is_empty(); }

  bool contains(shared_ptr<K> data) override {
    return _map->contains_key(data);
  }

  void add(shared_ptr<K> data) override {
    _map->add(data, make_shared<bool>(true));
  }

  void remove(shared_ptr<K> data) override { _map->remove(data); }

  void traverse(typename ISet<K>::TraverseFunc func = nullptr) {
    _map->traverse(func);
  }

  void clear() override { _map->clear(); }
};
} // namespace app

#endif /* HASH_SET_HPP */
