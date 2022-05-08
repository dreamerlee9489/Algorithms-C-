#ifndef IGRAPH_H
#define IGRAPH_H
#define STD_ std::
#include <set>
#include <map>
#include <vector>
#include <string>
#include <iostream>

namespace app
{
    template <typename V>
    class IGraph
    {
    protected:
        using TraverseFunc = bool (*)(V *v);
        template <typename _V>
        struct EdgeInfo
        {
            friend STD_ ostream &operator<<(STD_ ostream &out, EdgeInfo &edge) { return out << "EdgeInfo [" << *edge._from << ", " << *edge._to << ", " << edge._weight << "]"; }
            _V *_from = nullptr, *_to = nullptr;
            double _weight = 0;
            EdgeInfo(_V *from, _V *to, double weight = 0)
            {
                _from = from;
                _to = to;
                _weight = weight;
            }
            ~EdgeInfo() { delete _from, _to; }
        };
        template <typename _V>
        struct PathInfo
        {
            friend STD_ ostream &operator<<(STD_ ostream &out, PathInfo &path) { return out << "PathInfo [" << path._weight << "\t" << path.traverse(out); }
            double _weight;
            STD_ vector<EdgeInfo<_V> *> _edge_infos;
            PathInfo(double weight = 0) { _weight = weight; }
            STD_ ostream &traverse(STD_ ostream &out)
            {
                for (size_t i = 0; i < _edge_infos.size(); ++i)
                    out << *_edge_infos[i] << " ";
                return out;
            }
            ~PathInfo() = default;
        };
        bool _is_directed = false;
        IGraph(bool is_directed = false) { _is_directed = is_directed; }
        virtual ~IGraph() = default;
        virtual size_t vertices_size() = 0;
        virtual size_t edges_size() = 0;
        virtual void add_vertex(V *v) = 0;
        virtual void add_edge(V *from, V *to, double weight = 0) = 0;
        virtual void remove_vertex(V *v) = 0;
        virtual void remove_edge(V *from, V *to) = 0;
        virtual void bfs(V *begin, TraverseFunc func) = 0;
        virtual void dfs(V *begin, TraverseFunc func) = 0;
        virtual STD_ vector<V *> topo_sort() = 0;
        virtual STD_ set<EdgeInfo<V>> mst() = 0;
        virtual STD_ map<V, PathInfo<V> *> dijkstra() = 0;
    };
} // namespace app

#endif // IGRAPH_H