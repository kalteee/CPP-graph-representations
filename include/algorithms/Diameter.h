#ifndef DIAMETER_H
#define DIAMETER_H

#include "../graph/IGraph.h"

class Diameter {
public:
    static int compute(const IGraph& g);
};

#endif
