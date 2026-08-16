#ifndef MAKEACYCLIC_H
#define MAKEACYCLIC_H

#include "../graph/IGraph.h"
#include <vector>
#include <utility>

class MakeAcyclic {
public:
    static std::vector<std::pair<int,int>>
        cycleremoval(const IGraph&);

    static std::vector<std::pair<int,int>>
        dfsmethod(const IGraph&);

    static std::vector<std::pair<int,int>>
        buildacyclic(
            const IGraph&,
            const std::vector<std::pair<int,int>>&);

    static std::vector<std::pair<int,int>>
        partition(const IGraph&);

private:
    static bool reach(
        const IGraph&,
        int,
        int);

    static std::vector<std::pair<int,int>>
        dfs_dir(const IGraph&);
};

#endif
