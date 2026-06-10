#ifndef GRAPHMTX_H
#define GRAPHMTX_H

#include <vector>

class GraphMatrix {
private:
    int n;
    std::vector<std::vector<int>> mat;

public:
    GraphMatrix();

    void resize(int n);

    void add_edge(int u, int v);
    void remove_edge(int u, int v);

    bool hasedge(int u, int v) const;

    void read_mtx();

    int size() const;

    const std::vector<std::vector<int>>& matrix() const;
};

#endif
