#include <iostream>
#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <cstdlib>
#include <ctime>
#include "general.h"
#include "kmeans.h"

std::vector<Group> KMeans(std::vector<Node>& v, unsigned k, bool plus) {
    const char* name = plus ? "KMeans++" : "KMeans";
    printf("Start %s:\n", name);
    puts("=====================================");

    std::vector<Node> preCenters(k);
    unsigned testlen = v.size();

    std::vector<Group> centroid =
        plus ? buildInitialPointPlus(k, v) : buildInitialPoint(k, v);
    // std::vector<Group> centroid(k);
    // for (int i = 0; i < k; ++i) {
    //     centroid[i].nodes.push_back(v[i]);
    //     centroid[i].center = v[i];
    //     preCenters.push_back(centroid[i].center);
    // }   // 初始化各簇，设置质心

    // std::vector<Group> centroid = buildInitialPoint(k, v);

    printf("Print initial center id:\n");
    for (unsigned i = 0; i < k; ++i) {
        printf("%d\n", centroid[i].center.id);
    }
    puts("=====================================");

    double dis = 0, mdis = 0, mid = 0;
    unsigned times = 0;

    while (checkProcess(k, centroid, preCenters, times++)) {

        for (unsigned i = 0; i < testlen; ++i) {
            mdis = DINF;
            for (unsigned j = 0; j < k; ++j) {
                dis = sqrt(Distance::QuadraticEuclideanDistance(v[i], centroid[j].center));  // 计算欧氏距离
                if (dis < mdis) {
                    mdis = dis;
                    mid = j;
                }   // 找到最小值，最近簇id
            }
            // cout << mid << endl;
            if (!centroid[mid].idConflict(v[i].id)) {
                centroid[mid].nodes.push_back(v[i]);    // 在最近簇中加入节点i
            }
        }
        for (unsigned i = 0; i < k; ++i) {
            centroid[i].reCalCenter();
        }
    }

    evaluation(centroid, true);
    printf("End Of %s.\n", name);
    puts("=====================================\n");
    return centroid;
}