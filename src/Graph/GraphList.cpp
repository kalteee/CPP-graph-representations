#include "../../include/graph/GraphList.h"
#include "../../include/graph/GraphMatrix.h"
#include <algorithm>
#include <iostream>

// Constructors
GraphList::GraphList() : n(0) {}

GraphList::GraphList(int n_) {
    resize(n_);
}

// IGraph 
int GraphList::size() const {
    return n;
}

bool GraphList::has_edge(int u, int v) const {
    if (u < 0 || u >= n || v < 0 || v >= n)
        return false;

    for (int w : adj[u])
        if (w == v)
            return true;

    return false;
}

void GraphList::add_edge(int u, int v) {
    if (!has_edge(u, v)) {
        adj[u].push_back(v);
        indegree[v]++;
        outdegree[u]++;
        edges.push_back({u, v});
    }
}

void GraphList::remove_edge(int u, int v) {
    if (u < 0 || u >= (int)adj.size()) return;
    
    auto it = std::find(adj[u].begin(), adj[u].end(), v);
    if (it != adj[u].end()) {
        adj[u].erase(it);
        indegree[v]--;
        outdegree[u]--;
    } else {
        return;
    }

    auto it2 = std::find(edges.begin(), edges.end(), std::make_pair(u, v));
    if (it2 != edges.end()) edges.erase(it2);
}

std::vector<int> GraphList::neighbors(int u) const {
    if (u < 0 || u >= n) return {};
    return adj[u];
}

std::unique_ptr<IGraph> GraphList::clone() const {
    return std::make_unique<GraphList>(*this);
}

// GraphList specifikus metódusok
void GraphList::resize(int n_) {
    n = n_;
    adj.assign(n, {});
    indegree.assign(n, 0);
    outdegree.assign(n, 0);
    edges.clear();
}

int GraphList::sources() const {
    int res = 0;
    for (int i = 0; i < (int)indegree.size(); i++) {
        if (indegree[i] == 0) res++;
    }
    return res;
}

const std::vector<std::vector<int>>& GraphList::adjlist() const {
    return adj;
}

const std::vector<int>& GraphList::indegrees() const {
    return indegree;
}

const std::vector<int>& GraphList::outdegrees() const {
    return outdegree;
}

const std::vector<std::pair<int, int>>& GraphList::get_edges() const {
    return edges;
}

// Conversion
GraphList GraphList::from_matrix(const GraphMatrix& G) {
    GraphList H;
    H.resize(G.size());

    for (int i = 0; i < G.size(); i++) {
        for (int j = 0; j < G.size(); j++) {
            if (G.has_edge(i, j)) {
                H.add_edge(i, j);
            }
        }
    }

    return H;
}
