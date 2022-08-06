#ifndef IGRAPH_HPP
#define IGRAPH_HPP

#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <queue>
#include <stack>
#include <tuple>
#include <string>
#include <iostream>

namespace app {
    template<typename V>
    struct EdgeInfo {
        friend std::ostream &operator<<(std::ostream &out, const EdgeInfo &edge) {
            return out << "EdgeInfo <" << *edge._from << ", " << *edge._to << ", " << edge._weight << ">";
        }

        friend bool operator==(const EdgeInfo &lhs, const EdgeInfo &rhs) {
            return *lhs._from == *rhs._from && *lhs._to == *rhs._to && lhs._weight == rhs._weight;
        }

        friend bool operator!=(const EdgeInfo &lhs, const EdgeInfo &rhs) { return !(lhs == rhs); }

        V *_from = nullptr, *_to = nullptr;
        double _weight = 0;

        EdgeInfo(V *from, V *to, double weight = 0) {
            _from = from;
            _to = to;
            _weight = weight;
        }

        EdgeInfo(const EdgeInfo &edge) {
            _from = edge._from;
            _to = edge._to;
            _weight = edge._weight;
        }

        ~EdgeInfo() { delete _from, _to; }
    };

    template<typename V>
    struct PathInfo {
        friend std::ostream &operator<<(std::ostream &out, const PathInfo &path) { return path.traverse(); }

        double _weight;
        std::vector<EdgeInfo<V>> _edge_infos;

        PathInfo(double weight = 0) { _weight = weight; }

        PathInfo(const PathInfo &path) {
            _weight = path._weight;
            _edge_infos = path._edge_infos;
        }

        ~PathInfo() = default;

        std::ostream &traverse() const {
            std::cout << "PathInfo <weight =" << _weight << "\n";
            for (size_t i = 0; i < _edge_infos.size(); ++i)
                std::cout << _edge_infos[i] << "\n";
            return std::cout << ">\n";
        }
    };

    /**
     * @brief 图基类
     * @date 2022-05-09
     */
    template<typename V>
    class IGraph {
    protected:
        using TraverseFunc = bool (*)(V *v);

        IGraph() = default;

        virtual ~IGraph() = default;

        virtual size_t vertex_map_size() = 0;

        virtual size_t edge_set_size() = 0;

        virtual void add_vertex(V *v) = 0;

        virtual void add_edge(V *from, V *to, double weight = 0) = 0;

        virtual void remove_vertex(V *v) = 0;

        virtual void remove_edge(V *from, V *to) = 0;

        virtual void bfs(V *begin, TraverseFunc func = nullptr) = 0;

        virtual void dfs(V *begin, TraverseFunc func = nullptr) = 0;

        virtual std::vector<V> *topo_sort() = 0;

        virtual std::unordered_set<EdgeInfo<V>> *kruskal() = 0;

        virtual std::unordered_map<V, PathInfo<V>> *dijkstra(V *begin) = 0;
    };
} // namespace app

template<typename V>
struct std::hash<app::EdgeInfo<V>> {
    size_t operator()(const app::EdgeInfo<V> &edge) const {
        return hash<V>()(*edge._from) ^ hash<V>()(*edge._to) ^ hash<double>()(edge._weight);
    }
};

#endif /* IGRAPH_HPP */