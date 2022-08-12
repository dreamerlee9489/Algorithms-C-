#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "./09_IGraph.hpp"
#include "./10_MinHeap.hpp"
#include "./08_DisjointSet.hpp"

namespace app {
    template<typename V>
    struct Edge;

    template<typename V>
    struct Vertex {
        friend ostream &operator<<(ostream &out, const Vertex &vertex) { return out << *vertex.mValue; }

        friend bool operator==(const Vertex &lhs, const Vertex &rhs) { return *lhs.mValue == *rhs.mValue; }

        friend bool operator!=(const Vertex &lhs, const Vertex &rhs) { return !(lhs == rhs); }

        friend bool operator<(const Vertex &lhs, const Vertex &rhs) { return *lhs.mValue < *rhs.mValue; }

        friend bool operator>(const Vertex &lhs, const Vertex &rhs) { return *lhs.mValue > *rhs.mValue; }

        V *mValue = nullptr;
        unordered_set<Edge<V>> mInDegrees, mOutDegrees;

        Vertex(V *value) { mValue = value; }

        Vertex(const Vertex &vertex) { mValue = vertex.mValue; }

        ~Vertex() = default;
    };

    template<typename V>
    struct Edge {
        friend ostream &operator<<(ostream &out, const Edge &edge) {
            return out << "Edge [" << *edge.pFrom << ", " << *edge.pTo << ", " << edge.mWeight << "]";
        }

        friend bool operator==(const Edge &lhs, const Edge &rhs) {
            return *lhs.pFrom == *rhs.pFrom && *lhs.pTo == *rhs.pTo;
        }

        friend bool operator!=(const Edge &lhs, const Edge &rhs) { return !(lhs == rhs); }

        friend bool operator<(const Edge &lhs, const Edge &rhs) { return lhs.mWeight < rhs.mWeight; }

        friend bool operator>(const Edge &lhs, const Edge &rhs) { return lhs.mWeight > rhs.mWeight; }

        Vertex<V> *pFrom = nullptr, *pTo = nullptr;
        double mWeight = 0;

        Edge(Vertex<V> *from, Vertex<V> *to, double weight = 0) {
            pFrom = from;
            pTo = to;
            mWeight = weight;
        }

        ~Edge() = default;

        EdgeInfo<V> *get_info() { return new EdgeInfo<V>(pFrom->mValue, pTo->mValue, mWeight); }
    };

    /**
     * @brief 图
     * @date 2022-05-09
     * @tparam V
     */
    template<typename V>
    class Graph : public IGraph<V> {
        unordered_map<V, Vertex<V>> vertex_map;
        unordered_set<Edge<V>> edge_set;

        void relaxation(Edge<V> *edge, PathInfo<V> *from_path, unordered_map<Vertex<V>, PathInfo<V>> *path_map) {
            double weight = from_path->mWeight + edge->mWeight;
            typename unordered_map<Vertex<V>, PathInfo<V>>::iterator iter = path_map->find(*edge->pTo);
            PathInfo<V> *path = iter == path_map->end() ? nullptr : &iter->second;
            if (path != nullptr && weight >= path->mWeight)
                return;
            if (path != nullptr)
                path->mEdgeInfos.clear();
            else {
                path = new PathInfo<V>();
                path_map->emplace(make_pair(*edge->pTo, *path));
            }
            path->mWeight = weight;
            for (EdgeInfo<V> p: from_path->mEdgeInfos)
                path->mEdgeInfos.emplace_back(p);
            path->mEdgeInfos.emplace_back(*edge->get_info());
        }

        typename unordered_map<Vertex<V>, PathInfo<V>>::iterator
        get_min_path(unordered_map<Vertex<V>, PathInfo<V>> *path_map) {
            typename unordered_map<Vertex<V>, PathInfo<V>>::iterator min_iter = path_map->begin();
            for (typename unordered_map<Vertex<V>, PathInfo<V>>::iterator iter = path_map->begin();
                 iter != path_map->end(); ++iter)
                if (iter->second.mWeight < min_iter->second.mWeight)
                    min_iter = iter;
            return min_iter;
        }

    public:
        Graph(bool is_directed = false, size_t size = 0, tuple<V *, V *, double> *data = nullptr) {
            for (size_t i = 0; i < size; ++i) {
                this->add_edge(get<0>(data[i]), get<1>(data[i]), get<2>(data[i]));
                if (!is_directed)
                    this->add_edge(get<1>(data[i]), get<0>(data[i]), get<2>(data[i]));
            }
        }

        ~Graph() = default;

        size_t vertex_mapmSize() override { return vertex_map.size(); }

        size_t edge_setmSize() override { return edge_set.size(); }

        void add_vertex(V *v) override { vertex_map.emplace(make_pair(*v, Vertex<V>(v))); }

        void add_edge(V *from, V *to, double weight = 0) override {
            typename unordered_map<V, Vertex<V>>::iterator iter = vertex_map.find(*from);
            Vertex<V> *from_vertex = iter == vertex_map.end() ? nullptr : &iter->second;
            if (from_vertex == nullptr) {
                from_vertex = new Vertex<V>(from);
                vertex_map.emplace(make_pair(*from, *from_vertex));
            }
            iter = vertex_map.find(*to);
            Vertex<V> *to_vertex = iter == vertex_map.end() ? nullptr : &iter->second;
            if (to_vertex == nullptr) {
                to_vertex = new Vertex<V>(to);
                vertex_map.emplace(make_pair(*to, *to_vertex));
            }
            Edge<V> *edge = new Edge<V>(from_vertex, to_vertex, weight);
            if (from_vertex->mOutDegrees.erase(*edge)) {
                to_vertex->mInDegrees.erase(*edge);
                edge_set.erase(*edge);
            }
            from_vertex->mOutDegrees.emplace(edge->pFrom, edge->pTo, edge->mWeight);
            to_vertex->mInDegrees.emplace(edge->pFrom, edge->pTo, edge->mWeight);
            edge_set.emplace(edge->pFrom, edge->pTo, edge->mWeight);
        }

        void remove_vertex(V *v) override {
            typename unordered_map<V, Vertex<V>>::iterator iter = vertex_map.find(*v);
            Vertex<V> *vertex = iter == vertex_map.end() ? nullptr : &iter->second;
            vertex_map.erase(*v);
            if (vertex != nullptr) {
                for (typename unordered_set<Edge<V>>::iterator iter = vertex->mOutDegrees.begin();
                     iter != vertex->mOutDegrees.end(); ++iter) {
                    iter->pTo->mInDegrees.erase(*iter);
                    edge_set.erase(*iter);
                    vertex->mOutDegrees.erase(*iter);
                }
                for (typename unordered_set<Edge<V>>::iterator iter = vertex->mInDegrees.begin();
                     iter != vertex->mInDegrees.end(); ++iter) {
                    iter->pFrom->mOutDegrees.erase(*iter);
                    edge_set.erase(*iter);
                    vertex->mInDegrees.erase(*iter);
                }
            }
        }

        void remove_edge(V *from, V *to) override {
            typename unordered_map<V, Vertex<V>>::iterator iter = vertex_map.find(*from);
            Vertex<V> *from_vertex = iter == vertex_map.end() ? nullptr : &iter->second;
            if (from_vertex == nullptr)
                return;
            iter = vertex_map.find(*to);
            Vertex<V> *to_vertex = iter == vertex_map.end() ? nullptr : &iter->second;
            if (to_vertex == nullptr)
                return;
            Edge<V> *edge = new Edge<V>(from_vertex, to_vertex);
            if (from_vertex->mOutDegrees.erase(*edge)) {
                to_vertex->mInDegrees.erase(*edge);
                edge_set.erase(*edge);
            }
        }

        void bfs(V *begin, typename IGraph<V>::TraverseFunc func = nullptr) override {
            typename unordered_map<V, Vertex<V>>::iterator iter = vertex_map.find(*begin);
            Vertex<V> *begin_vertex = iter == vertex_map.end() ? nullptr : &iter->second;
            if (begin_vertex != nullptr) {
                unordered_set<Vertex<V>> visited_vertex_set;
                queue<Vertex<V> *> q;
                q.push(begin_vertex);
                visited_vertex_set.emplace(begin_vertex->mValue);
                while (!q.empty()) {
                    Vertex<V> *vertex = q.front();
                    q.pop();
                    cout << *vertex->mValue << "\n";
                    for (Edge<V> edge: vertex->mOutDegrees) {
                        if (visited_vertex_set.find(*edge.pTo) == visited_vertex_set.end()) {
                            q.push(edge.pTo);
                            visited_vertex_set.emplace(begin_vertex->mValue);
                        }
                    }
                }
            }
        }

        void dfs(V *begin, typename IGraph<V>::TraverseFunc func = nullptr) override {
            typename unordered_map<V, Vertex<V>>::iterator iter = vertex_map.find(*begin);
            Vertex<V> *begin_vertex = iter == vertex_map.end() ? nullptr : &iter->second;
            if (begin_vertex != nullptr) {
                unordered_set<Vertex<V>> visited_vertex_set;
                stack<Vertex<V> *> s;
                s.push(begin_vertex);
                visited_vertex_set.emplace(begin_vertex->mValue);
                cout << *begin << "\n";
                while (!s.empty()) {
                    Vertex<V> *vertex = s.top();
                    s.pop();
                    for (Edge<V> edge: vertex->mOutDegrees) {
                        if (visited_vertex_set.find(*edge.pTo) == visited_vertex_set.end()) {
                            s.push(edge.pFrom);
                            s.push(edge.pTo);
                            visited_vertex_set.emplace(begin_vertex->mValue);
                            cout << *edge.pTo->mValue << "\n";
                            break;
                        }
                    }
                }
            }
        }

        vector<V> *topo_sort() override {
            vector<V> *v = new vector<V>();
            queue<Vertex<V> *> q;
            unordered_map<Vertex<V>, size_t> in_map;
            for (typename unordered_map<V, Vertex<V>>::iterator iter = vertex_map.begin();
                 iter != vertex_map.end(); ++iter) {
                size_t in = iter->second.mOutDegrees.size();
                if (in == 0)
                    q.push(&iter->second);
                else
                    in_map.emplace(make_pair(iter->second, in));
            }
            while (!q.empty()) {
                Vertex<V> *vertex = q.front();
                q.pop();
                v->emplace_back(*vertex->mValue);
                for (Edge<V> edge: vertex->mOutDegrees) {
                    size_t to_in = in_map.find(*edge.pTo)->second;
                    if (to_in == 0)
                        q.push(edge.pTo);
                    else
                        in_map.emplace(make_pair(*edge.pTo, to_in));
                }
            }
            return v;
        }

        unordered_set<EdgeInfo<V>> *kruskal() override {
            size_t edgemSize = vertex_map.size();
            if (edgemSize > 0) {
                unordered_set<EdgeInfo<V>> *edge_info_set = new unordered_set<EdgeInfo<V>>();
                MinHeap<Edge<V>> *heap = new MinHeap<Edge<V>>();
                DisjointSet<Vertex<V>> *dj_set = new DisjointSet<Vertex<V>>();
                for (Edge<V> edge: edge_set)
                    heap->add(&edge);
                for (pair<V, Vertex<V>> p: vertex_map)
                    dj_set->add(&p.second);
                while (!heap->is_empty() && edge_info_set->size() < edgemSize) {
                    Edge<V> *edge = heap->remove();
                    if (!dj_set->is_same(edge->pFrom, edge->pTo)) {
                        edge_info_set->emplace(*edge->get_info());
                        dj_set->union_set(edge->pFrom, edge->pTo);
                    }
                }
                return edge_info_set;
            }
            return nullptr;
        }

        unordered_map<V, PathInfo<V>> *dijkstra(V *begin) override {
            typename unordered_map<V, Vertex<V>>::iterator iter = vertex_map.find(*begin);
            Vertex<V> *begin_vertex = iter == vertex_map.end() ? nullptr : &iter->second;
            if (begin_vertex != nullptr) {
                unordered_map<V, PathInfo<V>> *selected_path_map = new unordered_map<V, PathInfo<V>>();
                unordered_map<Vertex<V>, PathInfo<V>> *path_map = new unordered_map<Vertex<V>, PathInfo<V>>();
                path_map->emplace(make_pair(*begin_vertex, PathInfo<V>()));
                while (!path_map->empty()) {
                    typename unordered_map<Vertex<V>, PathInfo<V>>::iterator min_iter = get_min_path(path_map);
                    Vertex<V> min_vertex = min_iter->first;
                    PathInfo<V> min_path = min_iter->second;
                    selected_path_map->emplace(make_pair(*min_vertex.mValue, min_path));
                    path_map->erase(min_vertex);
                    for (Edge<V> edge: min_vertex.mOutDegrees) {
                        if (selected_path_map->find(*edge.pTo->mValue) == selected_path_map->end())
                            relaxation(&edge, &min_path, path_map);
                    }
                }
                selected_path_map->erase(*begin);
                return selected_path_map;
            }
            return nullptr;
        }

        void print() {
            cout << "----------vertex_map----------\n";
            for (pair<V, Vertex<V>> p: vertex_map)
                cout << p.first << "\n";
            cout << "----------edge_set----------\n";
            for (Edge<V> edge: edge_set)
                cout << edge << "\n";
        }
    };
} // namespace app

template<typename V>
struct hash<app::Vertex<V>> {
    size_t operator()(const app::Vertex<V> &vertex) const { return hash<V>()(*vertex.mValue); }
};

template<typename V>
struct hash<app::Edge<V>> {
    size_t operator()(const app::Edge<V> &edge) const {
        return hash<app::Vertex<V>>()(*edge.pFrom) ^ hash<app::Vertex<V>>()(*edge.pTo);
    }
};

#endif /* GRAPH_HPP */