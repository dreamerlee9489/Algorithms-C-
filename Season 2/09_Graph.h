#ifndef GRAPH_H
#define GRAPH_H
#include "./09_IGraph.h"
#include "./10_MinHeap.h"
#include "./08_DisjointSet.h"

namespace app
{
	template <typename V>
	struct Edge;
	template <typename V>
	struct Vertex
	{
		friend std::ostream& operator<<(std::ostream& out, const Vertex& vertex) { return out << *vertex._value; }
		friend bool operator==(const Vertex& lhs, const Vertex& rhs) { return *lhs._value == *rhs._value; }
		friend bool operator!=(const Vertex& lhs, const Vertex& rhs) { return !(lhs == rhs); }
		friend bool operator<(const Vertex& lhs, const Vertex& rhs) { return *lhs._value < *rhs._value; }
		friend bool operator>(const Vertex& lhs, const Vertex& rhs) { return *lhs._value > *rhs._value; }
		V* _value = nullptr;
		std::unordered_set<Edge<V>> in_degree, out_degree;
		Vertex(V* value) { _value = value; }
		Vertex(const Vertex& vertex) { _value = vertex._value; }
		~Vertex() = default;
	};
	template <typename V>
	struct Edge
	{
		friend std::ostream& operator<<(std::ostream& out, const Edge& edge) { return out << "Edge [" << *edge._from << ", " << *edge._to << ", " << edge._weight << "]"; }
		friend bool operator==(const Edge& lhs, const Edge& rhs) { return *lhs._from == *rhs._from && *lhs._to == *rhs._to; }
		friend bool operator!=(const Edge& lhs, const Edge& rhs) { return !(lhs == rhs); }
		friend bool operator<(const Edge& lhs, const Edge& rhs) { return lhs._weight < rhs._weight; }
		friend bool operator>(const Edge& lhs, const Edge& rhs) { return lhs._weight > rhs._weight; }
		Vertex<V>* _from = nullptr, * _to = nullptr;
		double _weight = 0;
		Edge(Vertex<V>* from, Vertex<V>* to, double weight = 0)
		{
			_from = from;
			_to = to;
			_weight = weight;
		}
		~Edge() = default;
		EdgeInfo<V>* get_info() { return new EdgeInfo<V>(_from->_value, _to->_value, _weight); }
	};
	/**
	 * @brief 图
	 * @date 2022-05-09
	 * @tparam V
	 */
	template <typename V>
	class Graph : public IGraph<V>
	{
		std::unordered_map<V, Vertex<V>> vertex_map;
		std::unordered_set<Edge<V>> edge_set;
		void relaxation(Edge<V>* edge, PathInfo<V>* from_path, std::unordered_map<Vertex<V>, PathInfo<V>>* path_map)
		{
			double weight = from_path->_weight + edge->_weight;
			typename std::unordered_map<Vertex<V>, PathInfo<V>>::iterator iter = path_map->find(*edge->_to);
			PathInfo<V>* path = iter == path_map->end() ? nullptr : &iter->second;
			if (path != nullptr && weight >= path->_weight)
				return;
			if (path != nullptr)
				path->_edge_infos.clear();
			else
			{
				path = new PathInfo<V>();
				path_map->emplace(std::make_pair(*edge->_to, *path));
			}
			path->_weight = weight;
			for (EdgeInfo<V> p : from_path->_edge_infos)
				path->_edge_infos.emplace_back(p);
			path->_edge_infos.emplace_back(*edge->get_info());
		}
		typename std::unordered_map<Vertex<V>, PathInfo<V>>::iterator get_min_path(std::unordered_map<Vertex<V>, PathInfo<V>>* path_map)
		{
			typename std::unordered_map<Vertex<V>, PathInfo<V>>::iterator min_iter = path_map->begin();
			for (typename std::unordered_map<Vertex<V>, PathInfo<V>>::iterator iter = path_map->begin(); iter != path_map->end(); ++iter)
				if (iter->second._weight < min_iter->second._weight)
					min_iter = iter;
			return min_iter;
		}

	public:
		Graph(bool is_directed = false, size_t size = 0, std::tuple<V*, V*, double>* data = nullptr)
		{
			for (size_t i = 0; i < size; ++i)
			{
				this->add_edge(get<0>(data[i]), get<1>(data[i]), get<2>(data[i]));
				if (!is_directed)
					this->add_edge(get<1>(data[i]), get<0>(data[i]), get<2>(data[i]));
			}
		}
		~Graph() = default;
		size_t vertex_map_size() override { return vertex_map.size(); }
		size_t edge_set_size() override { return edge_set.size(); }
		void add_vertex(V* v) override { vertex_map.emplace(std::make_pair(*v, Vertex<V>(v))); }
		void add_edge(V* from, V* to, double weight = 0) override
		{
			typename std::unordered_map<V, Vertex<V>>::iterator iter = vertex_map.find(*from);
			Vertex<V>* from_vertex = iter == vertex_map.end() ? nullptr : &iter->second;
			if (from_vertex == nullptr)
			{
				from_vertex = new Vertex<V>(from);
				vertex_map.emplace(std::make_pair(*from, *from_vertex));
			}
			iter = vertex_map.find(*to);
			Vertex<V>* to_vertex = iter == vertex_map.end() ? nullptr : &iter->second;
			if (to_vertex == nullptr)
			{
				to_vertex = new Vertex<V>(to);
				vertex_map.emplace(std::make_pair(*to, *to_vertex));
			}
			Edge<V>* edge = new Edge<V>(from_vertex, to_vertex, weight);
			if (from_vertex->out_degree.erase(*edge))
			{
				to_vertex->in_degree.erase(*edge);
				edge_set.erase(*edge);
			}
			from_vertex->out_degree.emplace(edge->_from, edge->_to, edge->_weight);
			to_vertex->in_degree.emplace(edge->_from, edge->_to, edge->_weight);
			edge_set.emplace(edge->_from, edge->_to, edge->_weight);
		}
		void remove_vertex(V* v) override
		{
			typename std::unordered_map<V, Vertex<V>>::iterator iter = vertex_map.find(*v);
			Vertex<V>* vertex = iter == vertex_map.end() ? nullptr : &iter->second;
			vertex_map.erase(*v);
			if (vertex != nullptr)
			{
				for (typename std::unordered_set<Edge<V>>::iterator iter = vertex->out_degree.begin(); iter != vertex->out_degree.end(); ++iter)
				{
					iter->_to->in_degree.erase(*iter);
					edge_set.erase(*iter);
					vertex->out_degree.erase(*iter);
				}
				for (typename std::unordered_set<Edge<V>>::iterator iter = vertex->in_degree.begin(); iter != vertex->in_degree.end(); ++iter)
				{
					iter->_from->out_degree.erase(*iter);
					edge_set.erase(*iter);
					vertex->in_degree.erase(*iter);
				}
			}
		}
		void remove_edge(V* from, V* to) override
		{
			typename std::unordered_map<V, Vertex<V>>::iterator iter = vertex_map.find(*from);
			Vertex<V>* from_vertex = iter == vertex_map.end() ? nullptr : &iter->second;
			if (from_vertex == nullptr)
				return;
			iter = vertex_map.find(*to);
			Vertex<V>* to_vertex = iter == vertex_map.end() ? nullptr : &iter->second;
			if (to_vertex == nullptr)
				return;
			Edge<V>* edge = new Edge<V>(from_vertex, to_vertex);
			if (from_vertex->out_degree.erase(*edge))
			{
				to_vertex->in_degree.erase(*edge);
				edge_set.erase(*edge);
			}
		}
		void bfs(V* begin, typename IGraph<V>::TraverseFunc func = nullptr) override
		{
			typename std::unordered_map<V, Vertex<V>>::iterator iter = vertex_map.find(*begin);
			Vertex<V>* begin_vertex = iter == vertex_map.end() ? nullptr : &iter->second;
			if (begin_vertex != nullptr)
			{
				std::unordered_set<Vertex<V>> visited_vertex_set;
				std::queue<Vertex<V>*> q;
				q.push(begin_vertex);
				visited_vertex_set.emplace(begin_vertex->_value);
				while (!q.empty())
				{
					Vertex<V>* vertex = q.front();
					q.pop();
					std::cout << *vertex->_value << "\n";
					for (Edge<V> edge : vertex->out_degree)
					{
						if (visited_vertex_set.find(*edge._to) == visited_vertex_set.end())
						{
							q.push(edge._to);
							visited_vertex_set.emplace(begin_vertex->_value);
						}
					}
				}
			}
		}
		void dfs(V* begin, typename IGraph<V>::TraverseFunc func = nullptr) override
		{
			typename std::unordered_map<V, Vertex<V>>::iterator iter = vertex_map.find(*begin);
			Vertex<V>* begin_vertex = iter == vertex_map.end() ? nullptr : &iter->second;
			if (begin_vertex != nullptr)
			{
				std::unordered_set<Vertex<V>> visited_vertex_set;
				std::stack<Vertex<V>*> s;
				s.push(begin_vertex);
				visited_vertex_set.emplace(begin_vertex->_value);
				std::cout << *begin << "\n";
				while (!s.empty())
				{
					Vertex<V>* vertex = s.top();
					s.pop();
					for (Edge<V> edge : vertex->out_degree)
					{
						if (visited_vertex_set.find(*edge._to) == visited_vertex_set.end())
						{
							s.push(edge._from);
							s.push(edge._to);
							visited_vertex_set.emplace(begin_vertex->_value);
							std::cout << *edge._to->_value << "\n";
							break;
						}
					}
				}
			}
		}
		std::vector<V>* topo_sort() override
		{
			std::vector<V>* v = new vector<V>();
			std::queue<Vertex<V>*> q;
			std::unordered_map<Vertex<V>, size_t> in_map;
			for (typename std::unordered_map<V, Vertex<V>>::iterator iter = vertex_map.begin(); iter != vertex_map.end(); ++iter)
			{
				size_t in = iter->second.out_degree.size();
				if (in == 0)
					q.push(&iter->second);
				else
					in_map.emplace(std::make_pair(iter->second, in));
			}
			while (!q.empty())
			{
				Vertex<V>* vertex = q.front();
				q.pop();
				v->emplace_back(*vertex->_value);
				for (Edge<V> edge : vertex->out_degree)
				{
					size_t to_in = in_map.find(*edge._to)->second;
					if (to_in == 0)
						q.push(edge._to);
					else
						in_map.emplace(std::make_pair(*edge._to, to_in));
				}
			}
			return v;
		}
		std::unordered_set<EdgeInfo<V>>* kruskal() override
		{
			size_t edge_size = vertex_map.size();
			if (edge_size > 0)
			{
				unordered_set<EdgeInfo<V>>* edge_info_set = new unordered_set<EdgeInfo<V>>();
				MinHeap<Edge<V>>* heap = new MinHeap<Edge<V>>();
				DisjointSet<Vertex<V>>* dj_set = new DisjointSet<Vertex<V>>();
				for (Edge<V> edge : edge_set)
					heap->add(&edge);
				for (std::pair<V, Vertex<V>> p : vertex_map)
					dj_set->add(&p.second);
				while (!heap->is_empty() && edge_info_set->size() < edge_size)
				{
					Edge<V>* edge = heap->remove();
					if (!dj_set->is_same(edge->_from, edge->_to))
					{
						edge_info_set->emplace(*edge->get_info());
						dj_set->union_set(edge->_from, edge->_to);
					}
				}
				return edge_info_set;
			}
			return nullptr;
		}
		std::unordered_map<V, PathInfo<V>>* dijkstra(V* begin) override
		{
			typename std::unordered_map<V, Vertex<V>>::iterator iter = vertex_map.find(*begin);
			Vertex<V>* begin_vertex = iter == vertex_map.end() ? nullptr : &iter->second;
			if (begin_vertex != nullptr)
			{
				unordered_map<V, PathInfo<V>>* selected_path_map = new unordered_map<V, PathInfo<V>>();
				unordered_map<Vertex<V>, PathInfo<V>>* path_map = new unordered_map<Vertex<V>, PathInfo<V>>();
				path_map->emplace(make_pair(*begin_vertex, PathInfo<V>()));
				while (!path_map->empty())
				{
					typename unordered_map<Vertex<V>, PathInfo<V>>::iterator min_iter = get_min_path(path_map);
					Vertex<V> min_vertex = min_iter->first;
					PathInfo<V> min_path = min_iter->second;
					selected_path_map->emplace(make_pair(*min_vertex._value, min_path));
					path_map->erase(min_vertex);
					for (Edge<V> edge : min_vertex.out_degree)
					{
						if (selected_path_map->find(*edge._to->_value) == selected_path_map->end())
							relaxation(&edge, &min_path, path_map);
					}
				}
				selected_path_map->erase(*begin);
				return selected_path_map;
			}
			return nullptr;
		}
		void print()
		{
			cout << "vertex_map\n";
			for (std::pair<V, Vertex<V>> p : vertex_map)
			{
				cout << p.first << "\n";
			}
			cout << "edge_set\n";
			for (Edge<V> edge : edge_set)
			{
				cout << edge << "\n";
			}
		}
	};
} // namespace app

template <typename V>
struct std::hash<app::Vertex<V>>
{
	size_t operator()(const app::Vertex<V>& vertex) const { return std::hash<V>()(*vertex._value); }
};

template <typename V>
struct std::hash<app::Edge<V>>
{
	size_t operator()(const app::Edge<V>& edge) const { return std::hash<app::Vertex<V>>()(*edge._from) ^ std::hash<app::Vertex<V>>()(*edge._to); }
};

#endif // GRAPH_H