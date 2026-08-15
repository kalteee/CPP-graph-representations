#include "GraphMatrix.h"

GraphMatrix::GraphMatrix() : n(0) {}

GraphMatrix::GraphMatrix(int n_) {
    resize(n_);
}

void GraphMatrix::resize(int n_) {
    n = n_;
    mat.assign(n, std::vector<int>(n, 0));
}

int GraphMatrix::size() const {
    return n;
}

bool GraphMatrix::has_edge(int u, int v) const {
    if (u < 0 || u >= n || v < 0 || v >= n)
        return false;

    return mat[u][v] != 0;
}

void GraphMatrix::add_edge(int u, int v) {
    if (u < 0 || u >= n || v < 0 || v >= n)
        return;

    mat[u][v] = 1;
}

void GraphMatrix::remove_edge(int u, int v) {
    if (u < 0 || u >= n || v < 0 || v >= n)
        return;

    mat[u][v] = 0;
}

std::vector<int> GraphMatrix::neighbors(int u) const {
    std::vector<int> result;

    if (u < 0 || u >= n)
        return result;

    for (int v = 0; v < n; ++v) {
        if (mat[u][v])
            result.push_back(v);
    }

    return result;
}

const std::vector<std::vector<int>>&
GraphMatrix::matrix() const {
    return mat;
}
