#include "Acyclic.h"
#include "../traversal/BFS.h"
#include "../traversal/DFS.h"

using namespace std;

static vector<pair<int,int>> MakeAcyclic::cycleremoval(const IGraph& g){
	Graph f = g;
	vector<pair<int,int>> removed;
	bool changed = true;
	while(changed){
		changed = false;
		auto edges = f.getedges();
		for(auto [u,v] : edges){
			if(!f.hasedge(u,v)) continue;
			if(reach(f,v,u)){
				f.remove_edge(u,v);
				removed.push_back({u,v});
				changed = true;
				break;
			}
		}
	}
	vector<pair<int,int>> final;
	for(auto it = removed.rbegin(); it != removed.rend(); it++){
		auto e = *it;
		if(!f.hasedge(e.first, e.second)){
			f.add_edge(e.first, e.second);
			if(reach(f, e.second, e.first)){
				f.remove_edge(e.first, e.second);
				final.push_back(e);
			}
		}
	}
	return final;
}

static vector<pair<int,int>> MakeAcyclic::dfsmethod(const Graph& g){
	return dfs_dir(g);
}

static vector<pair<int,int>> MakeAcyclic::buildacyclic(const Graph &g, const vector<pair<int,int>> edges){
	Graph h;
	h.resize(g.size());
	vector<pair<int,int>> remaining;
	for(auto [u,v]:edges){
		h.add_edge(u,v);
		auto cycles = dfs_dir(h);
		if(!cycles.empty()){
		h.remove_edge(u,v);
		remaining.push_back({u,v});
		}
	}
	return remaining;
}
// d feladat: top: topologikus sorrendben levő csúcsok, antitop: topologikussal ellentétes sorrend. A kisebbikből beszúrom az éleket ha tudom.
static vector<pair<int,int>> MakeAcyclic::partition(const Graph& g){
	Graph top;
	Graph antitop;
	top.resize(g.size());
	antitop.resize(g.size());
	vector<pair<int,int>> edges = g.getedges();

	for(auto [u,v]: edges){
		if(u > v){
			top.add_edge(u,v);
		}else{
			antitop.add_edge(u,v);
		}
	}
	vector<pair<int,int>> edgetop = top.getedges();
	vector<pair<int,int>> edgeanti = antitop.getedges();

	int m1 = edgetop.size();
	int m2 = edgeanti.size();

	if(m1>m2){
		for(auto [u,v] : edgeanti){
			top.add_edge(u,v);
			auto cycles = dfs_dir(top);
			if(!cycles.empty()){
				top.remove_edge(u,v);
			}else{
				antitop.remove_edge(u,v);
			}
		}
	return antitop.getedges();
	}else{
		for(auto [u,v] : edgetop){
			antitop.add_edge(u,v);
			auto cycles = dfs_dir(antitop);
			if(!cycles.empty()){
				antitop.remove_edge(u,v);
			}else{
				top.remove_edge(u,v);
			}
		}
	return top.getedges();
	}
}

static vector<pair<int,int>> MakeAcyclic::dfs_dir(const Graph&g){
	int n = g.size();
	vector<int> state(n,0);
	vector<pair<int,int>> back_edge;

	for(int s = 0; s<n; s++){
		if(state[s] != 0) continue;
		Dfs::run(g,s,state,
			[&](int u){state[u] = 1;},
			[&](int u){},
			[&](int u,int v){ back_edge.push_back({u,v});
			});
	}
	
	return back_edge;
}
static bool MakeAcyclic::reach(const Graph&g, int src, int dst){
	bool found = false;
	Bfs::run(g,src,
		[&](int u, int parent, int d){
			if( u == dst) found = true;
		},
		[&](int u){});
	return found;
}

