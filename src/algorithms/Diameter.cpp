#include "Diameter.h"
#include "../traversal/BFS.h"

int Diameter::compute(const IGraph& g)
{
    int diam = 0;
		for(int s = 0; s < g.size(); s++){
			vector<int> dist(g.size(),-1);
			Bfs::run(g,s,
			[&](int u, int parent, int d){
				dist[u] = d;
			},
			[&](int u){});

			for(int d: dist){
				if(d == -1) return -1;
				diam = max(d,diam);
			}

		}
		return diam;
}
