#ifndef GRAPH_MATRIX_H
#define GRAPH_MATRIX_H

#include "IGraph.h"

#include <vector>

class GraphMatrix : public IGraph {
private:
    int n;
    std::vector<std::vector<int>> mat;

public:
    GraphMatrix();
    explicit GraphMatrix(int n);

    int size() const override;

    bool has_edge(int u, int v) const override;

    void add_edge(int u, int v) override;
    void remove_edge(int u, int v) override;

    std::vector<int> neighbors(int u) const override;

    void resize(int n);

    const std::vector<std::vector<int>>& matrix() const;

    static GraphMatrix from_list(const class GraphList& G);
};

#endif
    static Graphmtx fromList(const GraphList& G);
};

#endif
