#ifndef IGRAPH_H
#define IGRAPH_H

#include <vector>

class IGraph {
public:
    virtual int size() const = 0;

    virtual bool has_edge(int u, int v) const = 0;

    virtual void add_edge(int u, int v) = 0;

    virtual void remove_edge(int u, int v) = 0;

    virtual std::vector<int> neighbors(int u) const = 0;

    virtual ~IGraph() = default;
};

#endif
