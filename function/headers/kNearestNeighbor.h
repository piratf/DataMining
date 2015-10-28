#ifndef KNERESTNEIGHBOR_H
#define KNERESTNEIGHBOR_H

#include "Node.h"
#include "Group.h"
#include <vector>

const unsigned CLASSCOUNT = 10;

struct KNNDistance
{
    unsigned id;
    double distance;

    friend bool operator < (const KNNDistance &lhs, const KNNDistance &rhs) {
        return lhs.distance < rhs.distance;
    }
};

struct TestDistances
{
    std::vector<KNNDistance> disWithTrainElements;
};

void knn(Group &train, Group &test);

#endif