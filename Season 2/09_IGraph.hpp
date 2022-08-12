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
            return out << "EdgeInfo <" << *edge.pFrom << ", " << *edge.pTo << ", " << edge.mWeight << ">";
        }

        friend bool operator==(const EdgeInfo &lhs, const EdgeInfo &rhs) {
            return *lhs.pFrom == *rhs.pFrom && *lhs.pTo == *rhs.pTo && lhs.mWeight == rhs.mWeight;
        }

        friend bool operator!=(const EdgeInfo &lhs, const EdgeInfo &rhs) { return !(lhs == rhs); }

        V *pFrom = nullptr, *pTo = nullptr;
        double mWeight = 0;

        EdgeInfo(V *from, V *to, double weight = 0) {
            pFrom = from;
            pTo = to;
            mWeight = weight;
        }

        EdgeInfo(const EdgeInfo &edge) {
            pFrom = edge.pFrom;
            pTo = edge.pTo;
            mWeight = edge.mWeight;
        }

        ~EdgeInfo() { delete pFrom, pTo; }
    };

    template<typename V>
    struct PathInfo {
        friend std::ostream &operator<<(std::ostream &out, const PathInfo &path) { return path.traverse(); }

        double mWeight;
        std::vector<EdgeInfo<V>> mEdgeInfos;

        PathInfo(double weight = 0) { mWeight = weight; }

        PathInfo(const PathInfo &path) {
            mWeight = path.mWeight;
            mEdgeInfos = path.mEdgeInfos;
        }

        ~PathInfo() = default;

        std::ostream &traverse() const {
            std::cout << "PathInfo <weight =" << mWeight << "\n";
            for (size_t i = 0; i < mEdgeInfos.size(); ++i)
                std::cout << mEdgeInfos[i] << "\n";
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

        virtual size_t vertex_mapmSize() = 0;

        virtual size_t edge_setmSize() = 0;

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
        return hash<V>()(*edge.pFrom) ^ hash<V>()(*edge.pTo) ^ hash<double>()(edge.mWeight);
    }
};

#endif /* IGRAPH_HPP */