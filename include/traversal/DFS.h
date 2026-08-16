#ifndef DFS_H
#define DFS_H

#include "../graph/IGraph.h"
#include <vector>
#include <stack>
#include <utility>

class Dfs {
public:
    template<typename Discover, typename Finish, typename Backedge>
    static void run(const IGraph& g, int start, std::vector<int>& state, Discover discover, Finish finish, Backedge back) {
        int n = g.size();
        std::stack<std::pair<int,int>> st;
        st.push({start, 0});
        state[start] = 1;
        discover(start);
        
        std::vector<int> parent(n, -1);
        
        while(!st.empty()) {
            auto &cur = st.top();
            int u = cur.first;
            int idx = cur.second;
            
            // Lekérjük a szomszédokat az absztrakt interfészen keresztül
            std::vector<int> szomszedok = g.neighbors(u);
            
            if(idx >= (int)szomszedok.size()){
                finish(u);
                state[u] = 2;
                st.pop();
                continue;
            }
            
            // Index növelése a verem tetején lévő elemhez
            st.top().second++;
            
            int v = szomszedok[idx];
            
            if(state[v] == 0) {
                state[v] = 1;
                parent[v] = u;
                discover(v);
                st.push({v, 0});
            } else if(state[v] == 1) {
                back(u, v);
            }
        }
    }
};

#endif
