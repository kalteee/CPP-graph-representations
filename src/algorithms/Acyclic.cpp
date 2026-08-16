#include "../../include/algorithms/Acyclic.h"
#include "../../include/traversal/BFS.h"
#include "../../include/traversal/DFS.h"
#include "../../include/graph/GraphList.h" 
#include <vector>
#include <utility>
#include <memory>

using namespace std;


static vector<pair<int,int>> get_all_edges(const IGraph& g) {
    vector<pair<int,int>> edges;
    for(int u = 0; u < g.size(); ++u) {
        for(int v : g.neighbors(u)) {
            edges.push_back({u, v});
        }
    }
    return edges;
}

vector<pair<int,int>> MakeAcyclic::cycleremoval(const IGraph& g){
    auto f = g.clone(); //f ~ unique_ptr
    vector<pair<int,int>> removed;
    bool changed = true;
    
    while(changed){
        changed = false;
        auto edges = get_all_edges(*f);
        for(auto [u,v] : edges){
            if(!f->has_edge(u,v)) continue;
            if(reach(*f, v, u)){
                f->remove_edge(u, v);
                removed.push_back({u,v});
                changed = true;
                break;
            }
        }
    }
    
    vector<pair<int,int>> final_edges;
    for(auto it = removed.rbegin(); it != removed.rend(); it++){
        auto e = *it;
        if(!f->has_edge(e.first, e.second)){
            f->add_edge(e.first, e.second);
            if(reach(*f, e.second, e.first)){
                f->remove_edge(e.first, e.second);
                final_edges.push_back(e);
            }
        }
    }
    return final_edges;
}

vector<pair<int,int>> MakeAcyclic::dfsmethod(const IGraph& g){
    return dfs_dir(g);
}

vector<pair<int,int>> MakeAcyclic::buildacyclic(const IGraph &g, const vector<pair<int,int>>& edges){
    GraphList h(g.size());
    vector<pair<int,int>> remaining;
    
    for(auto [u,v] : edges){
        h.add_edge(u,v);
        auto cycles = dfs_dir(h);
        if(!cycles.empty()){
            h.remove_edge(u,v);
            remaining.push_back({u,v});
        }
    }
    return remaining;
}

vector<pair<int,int>> MakeAcyclic::partition(const IGraph& g){
    GraphList top(g.size());
    GraphList antitop(g.size());
    vector<pair<int,int>> edges = get_all_edges(g);

    for(auto [u,v] : edges){
        if(u > v){
            top.add_edge(u,v);
        } else {
            antitop.add_edge(u,v);
        }
    }
    
    vector<pair<int,int>> edgetop = top.get_edges();
    vector<pair<int,int>> edgeanti = antitop.get_edges();

    int m1 = edgetop.size();
    int m2 = edgeanti.size();

    if(m1 > m2){
        for(auto [u,v] : edgeanti){
            top.add_edge(u,v);
            auto cycles = dfs_dir(top);
            if(!cycles.empty()){
                top.remove_edge(u,v);
            } else {
                antitop.remove_edge(u,v);
            }
        }
        return antitop.get_edges();
    } else {
        for(auto [u,v] : edgetop){
            antitop.add_edge(u,v);
            auto cycles = dfs_dir(antitop);
            if(!cycles.empty()){
                antitop.remove_edge(u,v);
            } else {
                top.remove_edge(u,v);
            }
        }
        return top.get_edges();
    }
}

vector<pair<int,int>> MakeAcyclic::dfs_dir(const IGraph& g){
    int n = g.size();
    vector<int> state(n,0);
    vector<pair<int,int>> back_edge;

    for(int s = 0; s < n; s++){
        if(state[s] != 0) continue;
        Dfs::run(g, s, state,
            [&](int u){ state[u] = 1; },
            [&](int u){},
            [&](int u, int v){ back_edge.push_back({u,v}); }
        );
    }
    
    return back_edge;
}

bool MakeAcyclic::reach(const IGraph& g, int src, int dst){
    bool found = false;
    Bfs::run(g, src,
        [&](int u, int parent, int d){
            if(u == dst) found = true;
        },
        [&](int u){}
    );
    return found;
}
