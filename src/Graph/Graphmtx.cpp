#include "Graphmtx.h"

GraphMatrix::GraphMatrix() : n(0) {}

void GraphMatrix::resize(int n_) {
    n = n_;
    mat.assign(n, std::vector<int>(n,0));
}

void GraphMatrix::add_edge(int u,int v){
    mat[u][v] = 1;
}

bool GraphMatrix::hasedge(int u,int v) const{
    return mat[u][v];
}
