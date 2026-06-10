#ifndef IGRAPH_H
#define IGRAPH_H

#include <vector>

class IGraph {
public:
    virtual int size() const = 0;

    virtual std::vector<int>
    neighbors(int u) const = 0;

    virtual ~IGraph() = default;
};
