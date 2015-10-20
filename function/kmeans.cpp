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

std::vector<Group> KMeans(Group &v, unsigned k, bool plus) {
    const char* name = plus ? "KMeans++" : "KMeans";
    printf("Start %s:\n", name);
    puts("=====================================");

    std::vector<Node> preCenters(k);
    unsigned dataSize = v.nodes.size();

    // 建立初始的簇中心
    std::vector<Group> centroid =
        plus ? buildInitialPointPlus(k, v) : buildInitialPoint(k, v);

    printf("Print initial center id:\n");
    for (unsigned i = 0; i < k; ++i) {
        printf("%d\n", centroid[i].center.id);
    }
    puts("=====================================");

    double dis = 0, mdis = 0, mid = 0;
    unsigned times = 0;

    while (checkProcess(k, centroid, preCenters, times++)) {
        for (unsigned i = 0; i < dataSize; ++i) {
            mdis = DINF;
            for (unsigned j = 0; j < k; ++j) {
                dis = sqrt(Distance::QuadraticEuclideanDistance(v.nodes[i], centroid[j].center));  // 计算欧氏距离
                if (dis < mdis) {
                    mdis = dis;
                    mid = j;
                }   // 找到最小值，最近簇id
            }
            // cout << mid << endl;
            if (!centroid[mid].idConflict(v.nodes[i].id)) {
                // 在最近簇中加入节点 i
                // centroid[mid].nodes.push_back(v.nodes[i]);    
                v.nodes[i].gid = mid;
            }
        }
        // 清空簇，重新添加
        for (Group &g : centroid) {
            g.nodes.clear();
        }
        // 根据 id 重新添加簇内容，这一步是为了去重
        for (Node &node : v.nodes) {
            centroid[node.gid].nodes.push_back(node);
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