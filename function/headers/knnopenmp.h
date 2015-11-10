#ifndef KNNOPENMP_H
#define KNNOPENMP_H

#include "Node.h"
#include "Group.h"
#include <knn.h>
#include <vector>

struct resultSort
{
    unsigned id, label;

    friend bool operator < (const resultSort &lhs, const resultSort &rhs) {
        return lhs.id < rhs.id;
    }
};

void knnopenmp(const Group &train, const Group &test);

/**
 * knn algorithm with openmp multithreading
 * @author piratf
 */
void knnopenmpRoundTest(const int nRound, const Group &train, const Group &test);

/**
 * knn algorithm with openmp multithreading
 * @author piratf
 */
void knnopenmpRoundTest2(const int nRound, const Group &train, const Group &test);

/**
 * compare result label to rawData, round by round
 * @author piratf
 * @param  round   No. round
 * @param  rawData total data
 */
void compare(const int i, const int head, Group &rawData);

#endif