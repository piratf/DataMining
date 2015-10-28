#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <algorithm>
#include "general.h"
#include "kmediods.h"

std::vector<Group> KMediods(Group& v, unsigned k, std::vector<Group> centroid, bool display) {
    if (display) {
        puts("Start KMediods:");
        puts("=====================================");
    }
    std::vector<Node> preCenters(k);
    unsigned testlen = v.nodes.size();

    if (display) {
        printf("Print initial center id:\n");
        for (unsigned i = 0; i < k; ++i) {
            printf("%d\n", centroid[i].center.id);
        }
        puts("=====================================");
    }

    double dis = 0, mdis = 0, mid = 0;

    // 指派每个剩余样本点给最近中心点代表的簇
    // 外层循环遍历点
    for (unsigned i = 0; i < testlen; ++i) {
        mdis = DINF;
        // 内层循环遍历簇
        for (unsigned j = 0; j < k; ++j) {
            dis = sqrt(Distance::QuadraticEuclideanDistance(v.nodes[i], centroid[j].center));  // 计算欧氏距离
            if (dis < mdis) {
                mdis = dis;
                mid = j;
            }   // 找到最小值，最近簇id
        }
        // cout << mid << endl;
        if (!centroid[mid].idConflict(v.nodes[i].id)) {
            centroid[mid].nodes.push_back(v.nodes[i]);    // 在最近簇中加入节点i
        }
    }

    // get SSE of centroid itself
    double sumSSE = evaluation(centroid), preSSE = 0, curSSE = 0, testSSE = 0;
    Node ORandom;
    srand((unsigned)time(NULL));
    while (sumSSE - preSSE != 0) {
        preSSE = sumSSE;
        sumSSE = 0;
        // 找到点ORandom
        for (unsigned i = 0; i < k; ++i) {
            unsigned clen = centroid[i].nodes.size();
            // 随机找一个点
            ORandom = centroid[i].center;
            while (ORandom.id == centroid[i].center.id) {
                if (clen == 1) {
                    break;
                }
                ORandom = centroid[i].nodes[rand() % (clen)];
            }
            curSSE = centroid[i].getSumOfEuclideanDistance();
            testSSE = centroid[i].getEuclideanDistanceWithOtherCenter(ORandom);
            if (testSSE < curSSE) {
                curSSE = testSSE;
                centroid[i].center = ORandom;
            }
            sumSSE += curSSE;
        }
        // printf("%lf : %lf\n", sumSSE, preSSE);
    }

    if (display) {
        printCentroidInfo(centroid, true);
        evaluation(centroid, true);
        puts("End Of KMediods:");
        puts("=====================================\n");
    }
    return centroid;
}