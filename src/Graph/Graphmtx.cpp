#include "Graphmtx.h"

Graphmtx::Graphmtx() : n(0) {}

void Graphmtx::resize(int n_) {
    n = n_;
    mat.assign(n, std::vector<int>(n,0));
}

void Graphmtx::add_edge(int u,int v){
    mat[u][v] = 1;
}

bool Graphmtx::hasedge(int u,int v) const{
    return mat[u][v];
}
