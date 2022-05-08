#ifndef GRAPH_H
#define GRAPH_H
#include "./09_IGraph.h"

namespace app
{
    template <typename V>
    class Graph : public IGraph<V>
    {
    private:
        template <typename _V>
        struct Edge;
        template <typename _V>
        struct Vertex
        {
            friend STD_ ostream &operator<<(STD_ ostream &out, const Vertex &vertex) { return out << *vertex._value; }
            friend bool operator==(const Vertex &lhs, const Vertex &rhs) { return *lhs._value == *rhs._value; }
            _V *_value = nullptr;
            STD_ set<Edge<V>> in_degree, out_degree;
            Vertex(V *value) { _value = value; }
            ~Vertex() { delete _value; }
        };
        template <typename _V>
        struct Edge
        {
            friend STD_ ostream &operator<<(STD_ ostream &out, const Edge &edge) { return out << "Edge [" << *edge._from << ", " << *edge._to << ", " << edge._weight << "]"; }
            friend bool operator==(const Edge &lhs, const Edge &rhs) { return *lhs._from == *rhs._from && *lhs._to == *rhs._to; }
            friend bool operator<(const Edge &lhs, const Edge & rhs) { return lhs._weight < rhs._weight; }
            Vertex<_V> *_from = nullptr, *_to = nullptr;
            double _weight = 0;
            Edge(Vertex<_V> *from, Vertex<_V> *to)
            {
                _from = from;
                _to = to;
            }
            ~Edge() { delete _from, _to; }
            typename IGraph<V>::template EdgeInfo<V> get_info() { return typename IGraph<V>::template EdgeInfo<V>(_from->_value, _to->_value, _weight); }
        };
        STD_ map<V, Vertex<V> *> vertex_map;
        STD_ set<Edge<V>> edge_set;

    public:
        Graph(bool is_directed = false) { this->_is_directed = is_directed; }
        ~Graph() = default;
        void print() { STD_ cout << this->vertices_size() << " - " << this->edges_size(); }
        size_t vertices_size() { return vertex_map.size(); }
        size_t edges_size() { return edge_set.size(); }
        void add_vertex(V *v) { vertex_map.emplace(STD_ make_pair(*v, new Vertex<V>(v))); }
        void add_edge(V *from, V *to, double weight = 0)
        {
            Vertex<V> *from_vertex = vertex_map.find(*from)->second;
            if (from_vertex == nullptr)
            {
                from_vertex = new Vertex<V>(from);
                vertex_map.emplace(STD_ make_pair(*from, from_vertex));
            }
            Vertex<V> *to_vertex = vertex_map.find(*to)->second;
            if (to_vertex == nullptr)
            {
                to_vertex = new Vertex<V>(to);
                vertex_map.emplace(STD_ make_pair(*to, to_vertex));
            }
            Edge<V> *edge = new Edge<V>(from_vertex, to_vertex);
            edge->_weight = weight;
            if (from_vertex->out_degree.erase(*edge))
            {
                to_vertex->in_degree.erase(*edge);
                edge_set.erase(*edge);
            }
            from_vertex->out_degree.emplace(edge->_from, edge->_to);
            to_vertex->in_degree.emplace(edge->_from, edge->_to);
            edge_set.emplace(edge->_from, edge->_to);
        }
        void remove_vertex(V *v)
        {
            Vertex<V> *vertex = vertex_map.find(*v)->second;
            vertex_map.erase(*v);
            if (vertex == nullptr)
                return;
            for (typename STD_ set<Edge<V>>::iterator iter = vertex->out_degree.begin(); iter != vertex->out_degree.end(); ++iter)
            {
                auto edge = iter;
                edge->_to->in_degree.erase(*edge);
                edge_set.erase(*edge);
                vertex->out_degree.erase(*iter);
            }
            for (typename STD_ set<Edge<V>>::iterator iter = vertex->in_degree.begin(); iter != vertex->in_degree.end(); ++iter)
            {
                auto edge = iter;
                edge->_from->out_degree.erase(*edge);
                edge_set.erase(*edge);
                vertex->in_degree.erase(*iter);
            }
        }
        void remove_edge(V *from, V *to)
        {
            Vertex<V> *from_vertex = vertex_map.find(*from)->second;
            if (from_vertex == nullptr)
                return;
            Vertex<V> *to_vertex = vertex_map.find(*to)->second;
            if (to_vertex == nullptr)
                return;
            Edge<V> *edge = new Edge<V>(from_vertex, to_vertex);
            if (from_vertex->out_degree.erase(*edge))
            {
                to_vertex->in_degree.erase(*edge);
                edge_set.erase(*edge);
            }
        }
        void bfs(V *begin, typename IGraph<V>::TraverseFunc func) {}
        void dfs(V *begin, typename IGraph<V>::TraverseFunc func) {}
        STD_ vector<V *> topo_sort() { return STD_ vector<V *>(); }
        STD_ set<typename IGraph<V>::template EdgeInfo<V>> mst() { return STD_ set<typename IGraph<V>::template EdgeInfo<V>>(); }
        STD_ map<V, typename IGraph<V>::template PathInfo<V> *> dijkstra() { return STD_ map<V, typename IGraph<V>::template PathInfo<V> *>(); }
    };
} // namespace app

template <typename V>
struct STD_ hash<typename app::Graph<V>::template Vertex<V>>
{
    size_t operator()(const typename app::Graph<V>::template Vertex<V> &vertex) const
    {
        return STD_ hash<V>()(*vertex._value);
    }
};

template <typename V>
struct STD_ hash<typename app::Graph<V>::template Edge<V>>
{
    size_t operator()(const typename app::Graph<V>::template Edge<V> &edge) const
    {
        return STD_ hash<typename app::Graph<V>::template Vertex<V>>()(*edge._from) ^ STD_ hash<typename app::Graph<V>::template Vertex<V>>()(*edge._to);
    }
};

#endif // GRAPH_H