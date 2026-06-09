#ifndef BFS_H
#define BFS_H

#include "../graph/Graph.h"
#include <queue>

class Bfs{
public:
template<typename Discover, typename Finish>
static void run(const Graph& g, int start, Discover discover, Finish finish){
	int n = g.size();
	vector<int> dist(n,-1);
	queue<int> q;
	q.push(start);
	dist[start] = 0;
	discover(start,-1,0);
	const auto &adj = g.adjlist();
	while(!q.empty()){
		int u = q.front(); q.pop();
		for(int v : adj[u]){
			if(dist[v] == -1){
				dist[v] = dist[u] + 1;
				discover(v,u,dist[v]);
				q.push(v);
			}
		}
		finish(u);
	}
}
};


#endif
