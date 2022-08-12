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
        friend ostream &operator<<(ostream &out, const Vertex &vertex) { return out << *vertex.pValue; }

        friend bool operator==(const Vertex &lhs, const Vertex &rhs) { return *lhs.pValue == *rhs.pValue; }

        friend bool operator!=(const Vertex &lhs, const Vertex &rhs) { return !(lhs == rhs); }

        friend bool operator<(const Vertex &lhs, const Vertex &rhs) { return *lhs.pValue < *rhs.pValue; }

        friend bool operator>(const Vertex &lhs, const Vertex &rhs) { return *lhs.pValue > *rhs.pValue; }

        V *pValue = nullptr;
        unordered_set<Edge<V>> mInDegree, mOutDegree;

        Vertex(V *value) { pValue = value; }

        Vertex(const Vertex &vertex) { pValue = vertex.pValue; }

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

        EdgeInfo<V> *get_info() { return new EdgeInfo<V>(pFrom->pValue, pTo->pValue, mWeight); }
    };

    /**
     * @brief 图
     * @date 2022-05-09
     * @tparam V
     */
    template<typename V>
    class Graph : public IGraph<V> {
        unordered_map<V, Vertex<V>> vertexMap;
        unordered_set<Edge<V>> edgeSet;

        void relaxation(Edge<V> *edge, PathInfo<V> *fromPath, unordered_map<Vertex<V>, PathInfo<V>> *pathMap) {
            double weight = fromPath->mWeight + edge->mWeight;
            typename unordered_map<Vertex<V>, PathInfo<V>>::iterator iter = pathMap->find(*edge->pTo);
            PathInfo<V> *path = iter == pathMap->end() ? nullptr : &iter->second;
            if (path != nullptr && weight >= path->mWeight)
                return;
            if (path != nullptr)
                path->mEdgeInfos.clear();
            else {
                path = new PathInfo<V>();
                pathMap->emplace(make_pair(*edge->pTo, *path));
            }
            path->mWeight = weight;
            for (EdgeInfo<V> p: fromPath->mEdgeInfos)
                path->mEdgeInfos.emplace_back(p);
            path->mEdgeInfos.emplace_back(*edge->get_info());
        }

        typename unordered_map<Vertex<V>, PathInfo<V>>::iterator
        get_min_path(unordered_map<Vertex<V>, PathInfo<V>> *pathMap) {
            typename unordered_map<Vertex<V>, PathInfo<V>>::iterator minIter = pathMap->begin();
            for (typename unordered_map<Vertex<V>, PathInfo<V>>::iterator iter = pathMap->begin();
                 iter != pathMap->end(); ++iter)
                if (iter->second.mWeight < minIter->second.mWeight)
                    minIter = iter;
            return minIter;
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

        size_t vertex_mapmSize() override { return vertexMap.size(); }

        size_t edge_setmSize() override { return edgeSet.size(); }

        void add_vertex(V *v) override { vertexMap.emplace(make_pair(*v, Vertex<V>(v))); }

        void add_edge(V *from, V *to, double weight = 0) override {
            typename unordered_map<V, Vertex<V>>::iterator iter = vertexMap.find(*from);
            Vertex<V> *fromVertex = iter == vertexMap.end() ? nullptr : &iter->second;
            if (fromVertex == nullptr) {
                fromVertex = new Vertex<V>(from);
                vertexMap.emplace(make_pair(*from, *fromVertex));
            }
            iter = vertexMap.find(*to);
            Vertex<V> *toVertex = iter == vertexMap.end() ? nullptr : &iter->second;
            if (toVertex == nullptr) {
                toVertex = new Vertex<V>(to);
                vertexMap.emplace(make_pair(*to, *toVertex));
            }
            Edge<V> *edge = new Edge<V>(fromVertex, toVertex, weight);
            if (fromVertex->mOutDegree.erase(*edge)) {
                toVertex->mInDegree.erase(*edge);
                edgeSet.erase(*edge);
            }
            fromVertex->mOutDegree.emplace(edge->pFrom, edge->pTo, edge->mWeight);
            toVertex->mInDegree.emplace(edge->pFrom, edge->pTo, edge->mWeight);
            edgeSet.emplace(edge->pFrom, edge->pTo, edge->mWeight);
        }

        void remove_vertex(V *v) override {
            typename unordered_map<V, Vertex<V>>::iterator iter = vertexMap.find(*v);
            Vertex<V> *vertex = iter == vertexMap.end() ? nullptr : &iter->second;
            vertexMap.erase(*v);
            if (vertex != nullptr) {
                for (typename unordered_set<Edge<V>>::iterator iter = vertex->mOutDegree.begin();
                     iter != vertex->mOutDegree.end(); ++iter) {
                    iter->pTo->mInDegrees.erase(*iter);
                    edgeSet.erase(*iter);
                    vertex->mOutDegree.erase(*iter);
                }
                for (typename unordered_set<Edge<V>>::iterator iter = vertex->mInDegree.begin();
                     iter != vertex->mInDegree.end(); ++iter) {
                    iter->pFrom->mOutDegrees.erase(*iter);
                    edgeSet.erase(*iter);
                    vertex->mInDegree.erase(*iter);
                }
            }
        }

        void remove_edge(V *from, V *to) override {
            typename unordered_map<V, Vertex<V>>::iterator iter = vertexMap.find(*from);
            Vertex<V> *fromVertex = iter == vertexMap.end() ? nullptr : &iter->second;
            if (fromVertex == nullptr)
                return;
            iter = vertexMap.find(*to);
            Vertex<V> *toVertex = iter == vertexMap.end() ? nullptr : &iter->second;
            if (toVertex == nullptr)
                return;
            Edge<V> *edge = new Edge<V>(fromVertex, toVertex);
            if (fromVertex->mOutDegree.erase(*edge)) {
                toVertex->mInDegree.erase(*edge);
                edgeSet.erase(*edge);
            }
        }

        void bfs(V *begin, typename IGraph<V>::TraverseFunc func = nullptr) override {
            typename unordered_map<V, Vertex<V>>::iterator iter = vertexMap.find(*begin);
            Vertex<V> *beginVertex = iter == vertexMap.end() ? nullptr : &iter->second;
            if (beginVertex != nullptr) {
                unordered_set<Vertex<V>> visitedVertexSet;
                queue<Vertex<V> *> q;
                q.push(beginVertex);
                visitedVertexSet.emplace(beginVertex->pValue);
                while (!q.empty()) {
                    Vertex<V> *vertex = q.front();
                    q.pop();
                    cout << *vertex->pValue << "\n";
                    for (Edge<V> edge: vertex->mOutDegree) {
                        if (visitedVertexSet.find(*edge.pTo) == visitedVertexSet.end()) {
                            q.push(edge.pTo);
                            visitedVertexSet.emplace(beginVertex->pValue);
                        }
                    }
                }
            }
        }

        void dfs(V *begin, typename IGraph<V>::TraverseFunc func = nullptr) override {
            typename unordered_map<V, Vertex<V>>::iterator iter = vertexMap.find(*begin);
            Vertex<V> *beginVertex = iter == vertexMap.end() ? nullptr : &iter->second;
            if (beginVertex != nullptr) {
                unordered_set<Vertex<V>> visitedVertexSet;
                stack<Vertex<V> *> s;
                s.push(beginVertex);
                visitedVertexSet.emplace(beginVertex->pValue);
                cout << *begin << "\n";
                while (!s.empty()) {
                    Vertex<V> *vertex = s.top();
                    s.pop();
                    for (Edge<V> edge: vertex->mOutDegree) {
                        if (visitedVertexSet.find(*edge.pTo) == visitedVertexSet.end()) {
                            s.push(edge.pFrom);
                            s.push(edge.pTo);
                            visitedVertexSet.emplace(beginVertex->pValue);
                            cout << *edge.pTo->pValue << "\n";
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
            for (typename unordered_map<V, Vertex<V>>::iterator iter = vertexMap.begin();
                 iter != vertexMap.end(); ++iter) {
                size_t in = iter->second.mOutDegrees.size();
                if (in == 0)
                    q.push(&iter->second);
                else
                    in_map.emplace(make_pair(iter->second, in));
            }
            while (!q.empty()) {
                Vertex<V> *vertex = q.front();
                q.pop();
                v->emplace_back(*vertex->pValue);
                for (Edge<V> edge: vertex->mOutDegree) {
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
            size_t edgemSize = vertexMap.size();
            if (edgemSize > 0) {
                unordered_set<EdgeInfo<V>> *edgeInfoSet = new unordered_set<EdgeInfo<V>>();
                MinHeap<Edge<V>> *heap = new MinHeap<Edge<V>>();
                DisjointSet<Vertex<V>> *djSet = new DisjointSet<Vertex<V>>();
                for (Edge<V> edge: edgeSet)
                    heap->add(&edge);
                for (pair<V, Vertex<V>> p: vertexMap)
                    djSet->add(&p.second);
                while (!heap->is_empty() && edgeInfoSet->size() < edgemSize) {
                    Edge<V> *edge = heap->remove();
                    if (!djSet->is_same(edge->pFrom, edge->pTo)) {
                        edgeInfoSet->emplace(*edge->get_info());
                        djSet->union_set(edge->pFrom, edge->pTo);
                    }
                }
                return edgeInfoSet;
            }
            return nullptr;
        }

        unordered_map<V, PathInfo<V>> *dijkstra(V *begin) override {
            typename unordered_map<V, Vertex<V>>::iterator iter = vertexMap.find(*begin);
            Vertex<V> *beginVertex = iter == vertexMap.end() ? nullptr : &iter->second;
            if (beginVertex != nullptr) {
                unordered_map<V, PathInfo<V>> *selectedPathMap = new unordered_map<V, PathInfo<V>>();
                unordered_map<Vertex<V>, PathInfo<V>> *pathMap = new unordered_map<Vertex<V>, PathInfo<V>>();
                pathMap->emplace(make_pair(*beginVertex, PathInfo<V>()));
                while (!pathMap->empty()) {
                    typename unordered_map<Vertex<V>, PathInfo<V>>::iterator minIter = get_min_path(pathMap);
                    Vertex<V> minVertex = minIter->first;
                    PathInfo<V> minPath = minIter->second;
                    selectedPathMap->emplace(make_pair(*minVertex.pValue, minPath));
                    pathMap->erase(minVertex);
                    for (Edge<V> edge: minVertex.mOutDegree) {
                        if (selectedPathMap->find(*edge.pTo->pValue) == selectedPathMap->end())
                            relaxation(&edge, &minPath, pathMap);
                    }
                }
                selectedPathMap->erase(*begin);
                return selectedPathMap;
            }
            return nullptr;
        }

        void print() {
            cout << "----------vertex_map----------\n";
            for (pair<V, Vertex<V>> p: vertexMap)
                cout << p.first << "\n";
            cout << "----------edge_set----------\n";
            for (Edge<V> edge: edgeSet)
                cout << edge << "\n";
        }
    };
} // namespace app

template<typename V>
struct hash<app::Vertex<V>> {
    size_t operator()(const app::Vertex<V> &vertex) const { return hash<V>()(*vertex.pValue); }
};

template<typename V>
struct hash<app::Edge<V>> {
    size_t operator()(const app::Edge<V> &edge) const {
        return hash<app::Vertex<V>>()(*edge.pFrom) ^ hash<app::Vertex<V>>()(*edge.pTo);
    }
};

#endif /* GRAPH_HPP */