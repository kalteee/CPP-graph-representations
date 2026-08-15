#ifndef MAKEACYCLIC_H
#define MAKEACYCLIC_H

#include "../graph/Graph.h"

class MakeAcyclic {
public:
    static std::vector<std::pair<int,int>>
        cycleremoval(const Graph&);

    static std::vector<std::pair<int,int>>
        dfsmethod(const Graph&);

    static std::vector<std::pair<int,int>>
        buildacyclic(
            const Graph&,
            const std::vector<std::pair<int,int>>&);

    static std::vector<std::pair<int,int>>
        partition(const Graph&);

private:
    static bool reach(
        const Graph&,
        int,
        int);

    static std::vector<std::pair<int,int>>
        dfs_dir(const Graph&);
};

#endif
