#ifndef KNNOPENMP_H
#define KNNOPENMP_H

#include "Node.h"
#include "Group.h"
#include <knn.h>
#include <vector>

void knnopenmp(const Group &train, const Group &test);

#endif