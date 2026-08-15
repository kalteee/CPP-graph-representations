#ifndef DFS_H
#define DFS_H

#include "../graph/Graph.h"

class Dfs{
public:
	template<typename Discover, typename Finish, typename Backedge>
	static void run(const Graph&g, int start,vector<int>& state,  Discover discover, Finish finish, Backedge back) {
		int n = g.size();
		stack<pair<int,int>> st;
		st.push({start,0});
		state[start] = 1;
		discover(start);
		const auto& adj = g.adjlist();
		vector<int> parent(n,-1);
		while(!st.empty()){
			auto &cur = st.top();
			st.pop();
			int u = cur.first;
			int idx = cur.second;
			if(idx >= (int)adj[u].size()){
				finish(u);
				state[u] = 2;
				continue;
			}
			st.push({u, idx+1});
			int v = adj[u][idx];
			if(state[v] == 0){
				state[v] = 1;
				parent[v] = u;
				discover(v);
				st.push({v,0});
			}else if(state[v] == 1){
				 back(u,v);
				}
		}
	}

};


#endif
