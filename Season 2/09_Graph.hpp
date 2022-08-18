#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "./08_DisjointSet.hpp"
#include "./09_IGraph.hpp"
#include "./10_MinHeap.hpp"

namespace app {
    template<typename V>
    struct Edge;

    template<typename V>
    struct Vertex {
        V *_value = nullptr;
        unordered_set<Edge<V>> _inDegree, _outDegree;

        friend ostream &operator<<(ostream &out, const Vertex &vertex) {
            return out << *vertex._value;
        }

        friend bool operator==(const Vertex &lhs, const Vertex &rhs) {
            return *lhs._value == *rhs._value;
        }

        friend bool operator!=(const Vertex &lhs, const Vertex &rhs) {
            return !(lhs == rhs);
        }

        friend bool operator<(const Vertex &lhs, const Vertex &rhs) {
            return *lhs._value < *rhs._value;
        }

        friend bool operator>(const Vertex &lhs, const Vertex &rhs) {
            return *lhs._value > *rhs._value;
        }

        Vertex(V *value) { _value = value; }

        Vertex(const Vertex &vertex) { _value = vertex._value; }

        ~Vertex() = default;
    };

    template<typename V>
    struct Edge {
        Vertex<V> *_from = nullptr, *_to = nullptr;
        double _weight = 0;

        friend ostream &operator<<(ostream &out, const Edge &edge) {
            return out << "Edge [" << *edge._from << ", " << *edge._to << ", "
                       << edge._weight << "]";
        }

        friend bool operator==(const Edge &lhs, const Edge &rhs) {
            return *lhs._from == *rhs._from && *lhs._to == *rhs._to;
        }

        friend bool operator!=(const Edge &lhs, const Edge &rhs) {
            return !(lhs == rhs);
        }

        friend bool operator<(const Edge &lhs, const Edge &rhs) {
            return lhs._weight < rhs._weight;
        }

        friend bool operator>(const Edge &lhs, const Edge &rhs) {
            return lhs._weight > rhs._weight;
        }

        Edge(Vertex<V> *from, Vertex<V> *to, double weight = 0) {
            _from = from;
            _to = to;
            _weight = weight;
        }

        ~Edge() = default;

        EdgeInfo<V> *get_info() {
            return new EdgeInfo<V>(_from->_value, _to->_value, _weight);
        }
    };

/**
 * @brief 图
 * @date 2022-05-09
 * @tparam V
 */
    template<typename V>
    class Graph : public IGraph<V> {
        unordered_map<V, Vertex<V>> _vertexMap;
        unordered_set<Edge<V>> _edgeSet;

        void relaxation(Edge<V> *edge, PathInfo<V> *fromPath,
                        unordered_map<Vertex<V>, PathInfo<V>> *pathMap) {
            double weight = fromPath->_weight + edge->_weight;
            typename unordered_map<Vertex<V>, PathInfo<V>>::iterator iter =
                    pathMap->find(*edge->_to);
            PathInfo<V> *path = iter == pathMap->end() ? nullptr : &iter->second;
            if (path != nullptr && weight >= path->_weight)
                return;
            if (path != nullptr)
                path->_edgeInfos.clear();
            else {
                path = new PathInfo<V>();
                pathMap->emplace(make_pair(*edge->_to, *path));
            }
            path->_weight = weight;
            for (EdgeInfo<V> p: fromPath->_edgeInfos)
                path->_edgeInfos.emplace_back(p);
            path->_edgeInfos.emplace_back(*edge->get_info());
        }

        typename unordered_map<Vertex<V>, PathInfo<V>>::iterator
        get_min_path(unordered_map<Vertex<V>, PathInfo<V>> *pathMap) {
            typename unordered_map<Vertex<V>, PathInfo<V>>::iterator minIter =
                    pathMap->begin();
            for (typename unordered_map<Vertex<V>, PathInfo<V>>::iterator iter =
                    pathMap->begin();
                 iter != pathMap->end(); ++iter)
                if (iter->second._weight < minIter->second._weight)
                    minIter = iter;
            return minIter;
        }

    public:
        Graph(bool is_directed = false, size_t size = 0,
              tuple<V *, V *, double> *data = nullptr) {
            for (size_t i = 0; i < size; ++i) {
                this->add_edge(get<0>(data[i]), get<1>(data[i]), get<2>(data[i]));
                if (!is_directed)
                    this->add_edge(get<1>(data[i]), get<0>(data[i]), get<2>(data[i]));
            }
        }

        ~Graph() = default;

        size_t vertex_map_size() override { return _vertexMap.size(); }

        size_t edge_set_size() override { return _edgeSet.size(); }

        void add_vertex(V *v) override {
            _vertexMap.emplace(make_pair(*v, Vertex<V>(v)));
        }

        void add_edge(V *from, V *to, double weight = 0) override {
            typename unordered_map<V, Vertex<V>>::iterator iter =
                    _vertexMap.find(*from);
            Vertex<V> *fromVertex = iter == _vertexMap.end() ? nullptr : &iter->second;
            if (fromVertex == nullptr) {
                fromVertex = new Vertex<V>(from);
                _vertexMap.emplace(make_pair(*from, *fromVertex));
            }
            iter = _vertexMap.find(*to);
            Vertex<V> *toVertex = iter == _vertexMap.end() ? nullptr : &iter->second;
            if (toVertex == nullptr) {
                toVertex = new Vertex<V>(to);
                _vertexMap.emplace(make_pair(*to, *toVertex));
            }
            Edge<V> *edge = new Edge<V>(fromVertex, toVertex, weight);
            if (fromVertex->_outDegree.erase(*edge)) {
                toVertex->_inDegree.erase(*edge);
                _edgeSet.erase(*edge);
            }
            fromVertex->_outDegree.emplace(edge->_from, edge->_to, edge->_weight);
            toVertex->_inDegree.emplace(edge->_from, edge->_to, edge->_weight);
            _edgeSet.emplace(edge->_from, edge->_to, edge->_weight);
        }

        void remove_vertex(V *v) override {
            typename unordered_map<V, Vertex<V>>::iterator iter = _vertexMap.find(*v);
            Vertex<V> *vertex = iter == _vertexMap.end() ? nullptr : &iter->second;
            _vertexMap.erase(*v);
            if (vertex != nullptr) {
                for (typename unordered_set<Edge<V>>::iterator iter =
                        vertex->_outDegree.begin();
                     iter != vertex->_outDegree.end(); ++iter) {
                    iter->_to->_inDegree.erase(*iter);
                    _edgeSet.erase(*iter);
                    vertex->_outDegree.erase(*iter);
                }
                for (typename unordered_set<Edge<V>>::iterator iter =
                        vertex->_inDegree.begin();
                     iter != vertex->_inDegree.end(); ++iter) {
                    iter->_from->_outDegree.erase(*iter);
                    _edgeSet.erase(*iter);
                    vertex->_inDegree.erase(*iter);
                }
            }
        }

        void remove_edge(V *from, V *to) override {
            typename unordered_map<V, Vertex<V>>::iterator iter =
                    _vertexMap.find(*from);
            Vertex<V> *fromVertex = iter == _vertexMap.end() ? nullptr : &iter->second;
            if (fromVertex == nullptr)
                return;
            iter = _vertexMap.find(*to);
            Vertex<V> *toVertex = iter == _vertexMap.end() ? nullptr : &iter->second;
            if (toVertex == nullptr)
                return;
            Edge<V> *edge = new Edge<V>(fromVertex, toVertex);
            if (fromVertex->_outDegree.erase(*edge)) {
                toVertex->_inDegree.erase(*edge);
                _edgeSet.erase(*edge);
            }
        }

        void bfs(V *begin, typename IGraph<V>::TraverseFunc func = nullptr) override {
            typename unordered_map<V, Vertex<V>>::iterator iter =
                    _vertexMap.find(*begin);
            Vertex<V> *beginVertex = iter == _vertexMap.end() ? nullptr : &iter->second;
            if (beginVertex != nullptr) {
                unordered_set<Vertex<V>> visitedVertexSet;
                queue<Vertex<V> *> q;
                q.push(beginVertex);
                visitedVertexSet.emplace(beginVertex->_value);
                while (!q.empty()) {
                    Vertex<V> *vertex = q.front();
                    q.pop();
                    cout << *vertex->_value << "\n";
                    for (Edge<V> edge: vertex->_outDegree) {
                        if (visitedVertexSet.find(*edge._to) == visitedVertexSet.end()) {
                            q.push(edge._to);
                            visitedVertexSet.emplace(beginVertex->_value);
                        }
                    }
                }
            }
        }

        void dfs(V *begin, typename IGraph<V>::TraverseFunc func = nullptr) override {
            typename unordered_map<V, Vertex<V>>::iterator iter =
                    _vertexMap.find(*begin);
            Vertex<V> *beginVertex = iter == _vertexMap.end() ? nullptr : &iter->second;
            if (beginVertex != nullptr) {
                unordered_set<Vertex<V>> visitedVertexSet;
                stack<Vertex<V> *> s;
                s.push(beginVertex);
                visitedVertexSet.emplace(beginVertex->_value);
                cout << *begin << "\n";
                while (!s.empty()) {
                    Vertex<V> *vertex = s.top();
                    s.pop();
                    for (Edge<V> edge: vertex->_outDegree) {
                        if (visitedVertexSet.find(*edge._to) == visitedVertexSet.end()) {
                            s.push(edge._from);
                            s.push(edge._to);
                            visitedVertexSet.emplace(beginVertex->_value);
                            cout << *edge._to->_value << "\n";
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
            for (typename unordered_map<V, Vertex<V>>::iterator iter =
                    _vertexMap.begin();
                 iter != _vertexMap.end(); ++iter) {
                size_t in = iter->second._outDegree.size();
                if (in == 0)
                    q.push(&iter->second);
                else
                    in_map.emplace(make_pair(iter->second, in));
            }
            while (!q.empty()) {
                Vertex<V> *vertex = q.front();
                q.pop();
                v->emplace_back(*vertex->_value);
                for (Edge<V> edge: vertex->_outDegree) {
                    size_t to_in = in_map.find(*edge._to)->second;
                    if (to_in == 0)
                        q.push(edge._to);
                    else
                        in_map.emplace(make_pair(*edge._to, to_in));
                }
            }
            return v;
        }

        unordered_set<EdgeInfo<V>> *kruskal() override {
            size_t edgeSize = _vertexMap.size();
            if (edgeSize > 0) {
                unordered_set<EdgeInfo<V>> *edgeInfoSet =
                        new unordered_set<EdgeInfo<V>>();
                MinHeap<Edge<V>> *heap = new MinHeap<Edge<V>>();
                DisjointSet<Vertex<V>> *djSet = new DisjointSet<Vertex<V>>();
                for (Edge<V> edge: _edgeSet)
                    heap->add(&edge);
                for (pair<V, Vertex<V>> p: _vertexMap)
                    djSet->add(&p.second);
                while (!heap->is_empty() && edgeInfoSet->size() < edgeSize) {
                    Edge<V> *edge = heap->remove();
                    if (!djSet->is_same(edge->_from, edge->_to)) {
                        edgeInfoSet->emplace(*edge->get_info());
                        djSet->union_set(edge->_from, edge->_to);
                    }
                }
                return edgeInfoSet;
            }
            return nullptr;
        }

        unordered_map<V, PathInfo<V>> *dijkstra(V *begin) override {
            typename unordered_map<V, Vertex<V>>::iterator iter =
                    _vertexMap.find(*begin);
            Vertex<V> *beginVertex = iter == _vertexMap.end() ? nullptr : &iter->second;
            if (beginVertex != nullptr) {
                unordered_map<V, PathInfo<V>> *selectedPathMap =
                        new unordered_map<V, PathInfo<V>>();
                unordered_map<Vertex<V>, PathInfo<V>> *pathMap =
                        new unordered_map<Vertex<V>, PathInfo<V>>();
                pathMap->emplace(make_pair(*beginVertex, PathInfo<V>()));
                while (!pathMap->empty()) {
                    typename unordered_map<Vertex<V>, PathInfo<V>>::iterator minIter =
                            get_min_path(pathMap);
                    Vertex<V> minVertex = minIter->first;
                    PathInfo<V> minPath = minIter->second;
                    selectedPathMap->emplace(make_pair(*minVertex._value, minPath));
                    pathMap->erase(minVertex);
                    for (Edge<V> edge: minVertex._outDegree) {
                        if (selectedPathMap->find(*edge._to->_value) ==
                            selectedPathMap->end())
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
            for (pair<V, Vertex<V>> p: _vertexMap)
                cout << p.first << "\n";
            cout << "----------edge_set----------\n";
            for (Edge<V> edge: _edgeSet)
                cout << edge << "\n";
        }
    };
} // namespace app

template<typename V>
struct hash<app::Vertex<V>> {
    size_t operator()(const app::Vertex<V> &vertex) const {
        return hash<V>()(*vertex._value);
    }
};

template<typename V>
struct hash<app::Edge<V>> {
    size_t operator()(const app::Edge<V> &edge) const {
        return hash<app::Vertex<V>>()(*edge._from) ^
               hash<app::Vertex<V>>()(*edge._to);
    }
};

#endif /* GRAPH_HPP */