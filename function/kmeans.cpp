#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <cstdlib>
#include <ctime>
#include "general.h"
#include "kmeans.h"


std::vector<Group> KMeans(Group &v, unsigned k, std::vector<Group> &centroid) {
    std::cout << "Start KMeans" << std::endl;
    puts("=====================================");

    // 用于在 checkProcess 中保存上一次运算的中心点，用于计算两次处理的差值，判断是否结束算法
    std::vector<Group> preCenters(1);
    unsigned dataSize = v.nodes.size();

    for (unsigned i = 0; i < v.nodes[0].attribute.size(); ++i) {
        preCenters[0].nodes.push_back(Node());
    }

    printf("Print initial center id:\n");
    for (unsigned i = 0; i < k; ++i) {
        centroid[i].center.display(false);
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
            // 标记应该加入的簇 id
            v.nodes[i].gid = mid;
        }
        // 清空簇
        for (Group &g : centroid) {
            g.nodes.clear();
        }
        // 根据 id 重新添加簇节点，这一步是为了去重
        for (Node &node : v.nodes) {
            centroid[node.gid].nodes.push_back(node);
        }
        // 重新计算中心点
        for (unsigned i = 0; i < k; ++i) {
            centroid[i].reCalCenter();
        }
    }

    evaluation(centroid, true);
    printCentroidInfo(centroid);

    std::cout << "End Of KMeans" << std::endl;
    puts("=====================================\n");
    return centroid;
}