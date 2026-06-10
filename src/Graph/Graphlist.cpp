#include "Graphlist.h"
#include <algorithm>
#include <iostream>

using namespace std;

bool hasedge(int u, int v) const{
		if(u < v || u>=(int)adj.size()) return false;
		for(int w:adj[u]) if(w == v) return true;
		return false;
	}

	void add_edge(int u, int v){
		if(!hasedge(u,v)){
		adj[u].push_back(v);
		indegree[v]++;
		outdegree[u]++;
		edges.push_back({u,v});
		}
	}

	void remove_edge(int u, int v){
		if(u < 0 || u>=(int)adj.size()) return;
		auto it = std::find(adj[u].begin(), adj[u].end(), v);
		if(it != adj[u].end()){
			adj[u].erase(it);
			indegree[v]--;
			outdegree[u]--;
		}
    else{
			return;
		}

		auto it2 = find(edges.begin(), edges.end(),make_pair(u,v));
		if(it2 != edges.end()) edges.erase(it2);
	}

	void read_edges(){
		cin >> n;
		adj.resize(n);
		indegree.assign(n,0);
		outdegree.assign(n,0);
		edges.clear();
		int u,v;
		while(cin >> u >> v){
			add_edge(u,v);

		}
	}

	void read_mtx(){
		cin >> n;
		adj.resize(n);
		indegree.assign(n,0);
		outdegree.assign(n,0);
		edges.clear();
		for(int i = 0; i<n; i++){
			for(int j = 0; j<n; j++){
				int val;
				cin >> val;
				if(val>0){
					add_edge(i,j);
				}
			}
		}
	}
	void resize(int n_){
		n = n_;
		adj.assign(n,{});
		indegree.assign(n,0);
		outdegree.assign(n,0);
		edges.clear();
	}

	int  sources() const{
		int  res = 0;
		for(int i = 0; i<indegree.size(); i++){
			if(indegree[i] == 0) res++;
		}
		return res;
	}

	const vector<vector<int>>&adjlist() const{
		return adj;
	}
	int size() const{
		return n;
	}
	const vector<int>&indegrees() const{
		return indegree;
	}
	const vector<int>&outdegrees() const{
		return outdegree;
	}
	const vector<pair<int,int>>&getedges() const{
		return edges;
	}
