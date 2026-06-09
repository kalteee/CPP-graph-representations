#ifndef BFS_H
#define BFS_H

#include "../graph/Graph.h"
#include <queue>

class Bfs {
public:
    template<typename Discover, typename Finish>
    static void run(
        const Graph& g,
        int start,
        Discover discover,
        Finish finish);
};

#include "BFS.tpp"

#endif
