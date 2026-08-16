#include "../../include/algorithms/Source.h"
#include "../../include/traversal/DFS.h"
#include "../../include/graph/GraphList.h" 
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

int Source::findsource(const IGraph& g){
    int n = g.size();
    vector<int> order;
    vector<int> state(n, 0);
    
    // First DFS for topological sort
    for(int s = 0; s < n; s++){
        if(state[s] != 0) continue;
        Dfs::run(g, s, state,
            [&](int u){},
            [&](int u){ order.push_back(u); },
            [&](int u, int v){}
        );
    }

    // creating the transposed graph
    GraphList gr(n);
    for(int u = 0; u < n; ++u) {
        for(int v : g.neighbors(u)) {
            gr.add_edge(v, u);
        }
    }

    vector<int> comp(n, -1);
    int cid = 0;
    reverse(order.begin(), order.end());
    vector<int> state2(n, 0);
    
    // Second DFS on transposed graph -> Strongly Connected Components
    for(int u : order){
        if(comp[u] != -1) continue;
        vector<int> st;
        Dfs::run(gr, u, state2,
            [&](int v){ st.push_back(v); },
            [&](int v){},
            [&](int x, int y){}
        );

        for(int v : st){
            comp[v] = cid;
        }
        cid++;
    }

    //building Component/Reduced graph
    vector<int> indeg(cid, 0);
    vector<unordered_set<int>> scc_adj(cid);
    
    for(int u = 0; u < n; ++u) {
        for(int v : g.neighbors(u)) {
            int cu = comp[u], cv = comp[v];
            if(cu != cv) scc_adj[cu].insert(cv);
        }
    }
    
    for(int u = 0; u < cid; u++){
        for(int v : scc_adj[u]) indeg[v]++;
    }
    
    int src = -1;
    int cnt = 0;
    
    // Finding a 0 indegree node in the reduced graph
    for(int i = 0; i < cid; i++){
        if(indeg[i] == 0){
            src = i;
            cnt++;
        }
    }
    
    // In the case the source is not unique
    if(cnt != 1){
        return -1;
    } else {
        int best = n;
        for(int i = 0; i < n; i++){
            if(comp[i] == src){
                best = min(best, i);
            }
        }
        return best;
    }
}
