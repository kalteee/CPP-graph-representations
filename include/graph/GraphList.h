#ifndef GRAPH_LIST_H
#define GRAPH_LIST_H

#include "IGraph.h"

#include <utility>
#include <vector>
#include <memory>

class GraphList : public IGraph {
private:
    int n;
    std::vector<std::vector<int>> adj;
    std::vector<int> indegree;
    std::vector<int> outdegree;
    std::vector<std::pair<int,int>> edges;

public:
    GraphList();
    explicit GraphList(int n);

    int size() const override;

    bool has_edge(int u, int v) const override;

    void add_edge(int u, int v) override;
    void remove_edge(int u, int v) override;

    std::vector<int> neighbors(int u) const override;
    
    std::unique_ptr<IGraph> clone() const override; // clone implementálása

    void resize(int n);

    int sources() const;

    const std::vector<std::vector<int>>& adjlist() const;
    const std::vector<int>& indegrees() const;
    const std::vector<int>& outdegrees() const;
    const std::vector<std::pair<int,int>>& get_edges() const;

    static GraphList from_matrix(const class GraphMatrix& G);
};

#endif
