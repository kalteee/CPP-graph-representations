#ifndef GRAPHLIST_H
#define GRAPHLIST_H

#include <vector>
#include <utility>

class Graph {
private:
    int n;
    std::vector<std::vector<int>> adj;
    std::vector<int> indegree;
    std::vector<int> outdegree;
    std::vector<std::pair<int,int>> edges;

public:
    Graph();

    bool hasedge(int u,int v) const;
    void add_edge(int u,int v);
    void remove_edge(int u,int v);

    void read_edges();
    void read_mtx();
    void resize(int n);

    int sources() const;
    int size() const;

    static GraphList fromMatrix(const GraphMatrix& G);

    const std::vector<std::vector<int>>& adjlist() const;
    const std::vector<int>& indegrees() const;
    const std::vector<int>& outdegrees() const;
    const std::vector<std::pair<int,int>>& getedges() const;
};

#endif
